/**
 * @file ucltest.c
 *   ucltest's main function
 */
#include <stdio.h>
#include "load/load.h"

int ucltest(int argc, char** argv)
{
	/* TODO: implement... */
	/*printf("ucltest default main\n");
	return 0;*/
	return ucl_fload("../testdata/test.ucl");
}
