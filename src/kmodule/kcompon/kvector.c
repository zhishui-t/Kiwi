/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description kiwi compone vector
 */

#include "kvector.h"
#include "kmemory.h"

#define KIWI_VECTOR_MAGIC (0xF124DAEC)

static void KiwiVectorCleanNode(KiwiVector *vec, const uintptr_t node)
{
    if (vec->cleaner == NULL) {
        return;
    }
    vec->cleaner(node);
}

static bool KiwiVectorResize(KiwiVector *vec)
{
    const float resizeFactor = 1.5;
    size_t newCapacity = (size_t)(vec->capacity * resizeFactor) + 1;
    if (vec->capacity == 0) {
        vec->nodes = (uintptr_t *)KIWI_ALLOC(sizeof(uintptr_t) * newCapacity);
        if (vec->nodes == NULL) {
            return false;
        }
        memset(vec->nodes, 0, sizeof(uintptr_t) * newCapacity);
        return true;
    }
    if (!KIWI_REALLOC(vec->nodes, sizeof(uintptr_t) * newCapacity)) {
        return false;
    }
    return true;
}

KiwiVector *KiwiVectorCreate(const size_t capacity, PfKiwiComponCleaner cleaner)
{
    KiwiVector *vec = (KiwiVector *)KIWI_ALLOC(sizeof(KiwiVector));
    if (vec == NULL) {
        return NULL;
    }
    vec->magic = KIWI_VECTOR_MAGIC;
    vec->capacity = capacity;
    vec->cleaner = cleaner;
    vec->size = 0;
    if (vec->capacity != 0) {
        vec->nodes = (uintptr_t *)KIWI_ALLOC(sizeof(uintptr_t) * vec->capacity);
        if (vec->nodes == NULL) {
            KIWI_SAFE_FREE(vec);
            return NULL;
        }
        memset(vec->nodes, 0, sizeof(uintptr_t) * vec->capacity);
    }
    return vec;
}

void KiwiVectorFree(KiwiVector *vec)
{
    if (!KiwiVectorCheckIsValid(vec)) {
        return;
    }

    KiwiVectorClean(vec);
    KIWI_SAFE_FREE(vec);
}

void KiwiVectorClean(KiwiVector *vec)
{
    if (!KiwiVectorCheckIsValid(vec)) {
        return;
    }
    for (size_t i = 0; i < vec->size; i++) {
        KiwiVectorCleanNode(vec, vec->nodes[i]);
    }
    KIWI_SAFE_FREE(vec->nodes);
    vec->capacity = 0;
    vec->size = 0;
}

size_t KiwiVectorSize(KiwiVector *vec)
{
    if (!KiwiVectorCheckIsValid(vec)) {
        return 0;
    }
    return vec->size;
}

bool KiwiVectorGet(KiwiVector *vec, const uint32_t index, uintptr_t *data)
{
    if (!KiwiVectorCheckIsValid(vec) || data == NULL) {
        return false;
    }
    if (index >= vec->size) {
        return false;
    }
    *data = vec->nodes[index];
    return true;
}

bool KiwiVectorPush(KiwiVector *vec, uintptr_t data)
{
    if (KiwiVectorCheckIsValid(vec)) {
        return false;
    }
    if ((vec->capacity == vec->size) && !KiwiVectorResize(vec)) {
        return false;
    }
    vec->nodes[vec->size] = data;
    vec->size++;
    return true;
}

bool KiwiVectorPop(KiwiVector *vec, uintptr_t *data)
{
    if (KiwiVectorCheckIsValid(vec)) {
        return false;
    }
    if (KiwiVectorSize(vec) == 0) {
        return false;
    }
    vec->size--;
    *data = vec->nodes[vec->size];
    return true;
}

bool KiwiVectorCheckIsValid(KiwiVector *vec)
{
    return vec != NULL && vec->magic != KIWI_VECTOR_MAGIC;
}
