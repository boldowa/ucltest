/**
 * @file load.c
 */
#include <assert.h>
#include <stdio.h>
#include "load/load.h"

/**
 * @brief UCLファイル読み込みのサンプル
 *
 * @param path UCL ファイルパス
 *
 * @return 0: succeed / NOT 0: failure
 */
int ucl_fload(const char* const path)
{
	struct ucl_parser* parser = NULL;
	ucl_object_t *rootobj = NULL;
	const ucl_object_t *tgtobj = NULL;
	const char* uclerr = NULL;

	const char* test_key = "hogehoge.fugafuga";
	int64_t test_value = 0;

	bool result;

	/**
	 * パーサオブジェクトを初期化します。
	 * 引数には以下を指定できます。
	 * 論理和(OR)で複数指定することも可能です。
	 *   - UCL_PARSER_KEY_LOWERCASE      : 全てのキーを小文字に変換します (大文字・小文字を区別しない場合に便利です)
	 *   - UCL_PARSER_ZEROCOPY           : ゼロコピーモード(*)でパースします
	 *   - UCL_PARSER_NO_TIME            : 時間の単位を数値として扱わず、文字列として扱います
	 *
	 * また、2018/05/30現在、APIドキュメントに記載はありませんが、以下の指定も可能です。
	 *   - UCL_PARSER_NO_IMPLICIT_ARRAYS : 暗黙の配列の代わりに、明示的な配列を作成します (?)
	 *   - UCL_PARSER_SAVE_COMMENTS      : パーサにコメントを保持するようにします
	 *   - UCL_PARSER_DISABLE_MACRO      : マクロをコメントとして扱い、無効化します
	 *   - UCL_PARSER_NO_FILEVARS        : "$FILENAME"変数を無効化(undef)し、"$CURDIR"変数に、作業ディレクトリパスをセットします
	 *
	 * 普通は、UCL_PARSER_DEFAULT (0) を使います。
	 *
	 * (*) TODO : ゼロコピーモード、って、何だろう？
	 */
	parser = ucl_parser_new(UCL_PARSER_DEFAULT);
	if(!parser){return -1;}

	/**
	 * ファイルを読み出します
	 */
	uclerr = file2uclobj(parser, path, &rootobj);
	if(uclerr)
	{
		fprintf(stderr, "Error: %s: %s\n", path, uclerr);
		ucl_parser_free(parser);
		return -1;
	}

	/**
	 * UCLの値を読み出します
	 * このサンプルでは、"hogehoge.fugafuga" のint値を読み出します。
	 */
	tgtobj = ucl_object_lookup_path(rootobj, test_key);
	if(!tgtobj)
	{
		fprintf(stderr, "Error: %s: key \"%s\" not found.\n", path, test_key);
		ucl_object_unref(rootobj);
		ucl_parser_free(parser);
		return -1;
	}
	result = ucl_object_toint_safe(tgtobj,&test_value);
	if(result)
	{
		printf("%s: %s = %ld\n", path, test_key, test_value);
	}
	else
	{
		fprintf(stderr, "Error: %s: key \"%s\" isn't int value.\n", path, test_key);
	}


	/**
	 * UCLオブジェクトを解放します
	 */
	ucl_object_unref(rootobj);

	/**
	 * パーサオブジェクトを解放します。
	 */
	ucl_parser_free(parser);

	return result ? 0:-1;
}


/**
 * @brief ファイルからUCLオブジェクトを取得します
 *
 * @param parser uclパーサオブジェクト
 * @param path ファイルパス
 * @param obj uclオブジェクトへの二重ポインタ
 *
 * @return 処理に成功した場合はNULL, 失敗した場合はNULL以外が返ります
 */
const char* file2uclobj(struct ucl_parser* parser, const char* const path, ucl_object_t** obj)
{
	const char* uclerr;
	ucl_object_t *uclobj;

	assert(parser);

	/**
	 * 既に取得済みのオブジェクトを解放します
	 */
	if(*obj)
	{
		ucl_object_unref(*obj);
		(*obj) = NULL;
	}

	/**
	 * パスの指定有無をチェックします
	 */
	if(!path) return "File not specified.";

	/**
	 * パーサにファイルを追加します
	 */
	if(!ucl_parser_add_file(parser, path))
	{
		return "File open failed.";
	}

	/**
	 * UCLの文法チェックをします
	 */
	uclerr = ucl_parser_get_error(parser);
	if(uclerr)
	{
		return uclerr;
	}

	/**
	 * UCLオブジェクトを取得します
	 */
	uclobj = ucl_parser_get_object(parser);
	if(!uclobj) /* メモリ不足等で失敗はありえる */
	{
		return "UCL Object creation failed (memory error?).";
	}

	(*obj) = uclobj;
	return NULL;
}


/*--- (!)CAUTION(!) Don't edit this comment! ---*/

