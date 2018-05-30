/**
 * @file load.h
 */
#ifndef LOAD_H
#define LOAD_H

#include <ucl.h>

#ifdef __cplusplus
extern "C" {
#endif

int ucl_fload(const char* const path);

const char* file2uclobj(struct ucl_parser* parser, const char* const path, ucl_object_t** obj);

/*--- (!)CAUTION(!) Don't edit this comment! ---*/

#ifdef __cplusplus
}
#endif
#endif
