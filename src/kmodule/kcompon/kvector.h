/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description kiwi compone vector
 */

#ifndef KIWI_COMPON_VECTOR_H
#define KIWI_COMPON_VECTOR_H

#include "ktypes.h"
#include "kcompon.h"

typedef struct {
    uint32_t magic;
    size_t capacity;
    size_t size;
    uintptr_t *nodes;
    PfKiwiComponCleaner cleaner;
} KiwiVector;

KiwiVector *KiwiVectorCreate(const size_t capacity, PfKiwiComponCleaner cleaner);
void KiwiVectorFree(KiwiVector *vec);
void KiwiVectorClean(KiwiVector *vec);

size_t KiwiVectorSize(KiwiVector *vec);
bool KiwiVectorGet(KiwiVector *vec, const uint32_t index, uintptr_t *data);

bool KiwiVectorPush(KiwiVector *vec, const uintptr_t data);
bool KiwiVectorPop(KiwiVector *vec, uintptr_t *data);

bool KiwiVectorCheckIsValid(KiwiVector *vec);

#endif // KIWI_COMPON_VECTOR_H
