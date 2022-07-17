/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description memory 
 */
#include "kmemory.h"
#include <string.h>
#include <stdlib.h>

#define Kiwi_ALLOCATOR_MAIGC (0xF151FDEF)

static inline void KiwiAllocatorSetSize(void *buf, const size_t size)
{
    *((uint32_t *)buf) = size;
}

static inline uint32_t KiwiAllocatorGetSize(void *buf)
{
    return *((uint32_t *)buf); 
}

static inline void KiwiAllocatorSetMagic(void *buf, const size_t size)
{
    *((uint32_t *)((uint8_t *)buf + sizeof(uint32_t) + size)) = (uint32_t)Kiwi_ALLOCATOR_MAIGC;
}

static inline bool KiwiAllocatorCheckMagic(void *buf)
{
    uint32_t size = KiwiAllocatorGetSize(buf);
    uint32_t magic = *((uint32_t *)((uint8_t *)buf + sizeof(uint32_t) + size));
    return magic == (uint32_t)Kiwi_ALLOCATOR_MAIGC;
}

void *KiwiAlloc(const size_t size, const char *funcName, const size_t lineNo)
{
    if (size == 0) {
        return NULL;
    }
    void *buf = malloc(size + sizeof(uint32_t) + sizeof(uint32_t));
    if (buf == NULL) {
        return NULL;
    }
    KiwiAllocatorSetSize(buf, size);
    KiwiAllocatorSetMagic(buf, size);
    return (void *)((uint8_t *)buf + sizeof(uint32_t));
}

void KiwiFree(void *buf, const char *funcName, const size_t lineNo)
{
    (void)funcName;
    (void)lineNo;
    if (buf == NULL) {
        return;
    }
    void *memBuf = (void *)((uint8_t *)buf - sizeof(uint32_t));
    if (!KiwiAllocatorCheckMagic(memBuf)) {
        return;
    }
    free(memBuf);
}

bool KiwiReAlloc(void **buf, const size_t size, const char *funcName, const size_t lineNo)
{
    if (buf == NULL || *buf == NULL) {
        return false;
    }

    if (size == 0) {
        return false;
    }
    void *oriBuf = (void *)((uint8_t *)(*buf) - sizeof(uint32_t));
    if (!KiwiAllocatorCheckMagic(oriBuf)) {
        return false;
    }

    uint32_t oriSize = KiwiAllocatorGetSize(oriBuf);
    if (oriSize >= size) {
        return true;
    }
    void *newBuf = (void *)KiwiAlloc(size, funcName, lineNo);
    if (newBuf == NULL) {
        return false;
    }
    memset(newBuf, 0, size);
    memcpy(newBuf, *buf, oriSize);
    KiwiFree(*buf, funcName, lineNo);
    *buf = newBuf;
    return true;
}

char *KiwiStrDup(const char *src, const char *funcName, const size_t lineNo)
{
    if (src == NULL) {
        return NULL;
    }
    size_t srcLen = strlen(src);
    char *dest = (char *)KiwiAlloc(srcLen + 1, funcName, lineNo);
    if (dest == NULL) {
        return NULL;
    }
    memset(dest, 0, srcLen + 1);
    if (srcLen == 0) {
        return dest; 
    }
    strncpy(dest, src, srcLen);
    return dest;
}