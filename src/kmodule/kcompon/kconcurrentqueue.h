/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description kiwi queue thread safe
 */

#ifndef KIWI_COMPON_CONCURRENT_QUEUE_H
#define KIWI_COMPON_CONCURRENT_QUEUE_H

#include "ktypes.h"
#include "katomic.h"

typedef struct {
    KIWI_ATOMIC_POINTER head;
    KIWI_ATOMIC_POINTER tail;
    KIWI_ATOMIC size_t count;
} KiwiConcurrQueue;

KiwiConcurrQueue *KiwiConcurrQueueCreate(void);
void KiwiConcurrQueueDestroy(KiwiConcurrQueue *queue);

bool KiwiConcurrQueuePush(KiwiConcurrQueue *queue, const uintptr_t data);
bool KiwiConcurrQueuePop(KiwiConcurrQueue *queue, uintptr_t *data);

size_t KiwiConcurrQueueSize(KiwiConcurrQueue *queue);

#endif // KIWI_COMPON_CONCURRENT_QUEUE_H