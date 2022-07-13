/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description memory 
 */
#ifndef KIWI_MOUDLE_MEMORY_H
#define KIWI_MOUDLE_MEMORY_H

#include "ktypes.h"

void *KiwiAlloc(const size_t size, const char *funcName, const size_t lineNo);

void KiwiFree(void *buf, const char *funcName, const size_t lineNo);

bool KiwiReAlloc(void **buf, const size_t size, const char *funcName, const size_t lineNo);

char *KiwiStrDup(const char *src, const char *funcName, const size_t lineNo);

#define KIWI_ALLOC(size) KiwiAlloc((size), __func__, __LINE__);
#define KIWI_SAFE_FREE(buf) \
do { \
    if ((buf) != NULL) { \
        KiwiFree((void *)(buf), __func__, __LINE__); \
    } \
} while (0)

#define KIWI_REALLOC(buf, size) KiwiReAlloc((void **)(&(buf)), size, __func__, __LINE__)

#define KIWI_STRDUP(src) KiwiStrDup((src), __func__, __LINE__)

#endif // Z_MOUDLE_MEMORY_H