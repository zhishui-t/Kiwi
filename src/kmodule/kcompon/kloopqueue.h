/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description kiwi loop queue
 */

#ifndef KIWI_COMPON_LOOP_QUEUE_H
#define KIWI_COMPON_LOOP_QUEUE_H

#include "ktypes.h"

typedef struct {
    size_t capacity;
    uint32_t front;
    uint32_t rear;
    uintptr_t *datas;
} KiwiLoopQueue;

KiwiLoopQueue *KiwiLoopQueueCreate(const size_t capacity);
void KiwiLoopQueueDestroy(KiwiLoopQueue *loopQueue);

bool KiwiLoopQueuePush(KiwiLoopQueue *loopQueue, uintptr_t data);
bool KiwiLoopQueuePop(KiwiLoopQueue *loopQueue, uintptr_t *data);

bool KiwiLoopQueueIsEmpty(KiwiLoopQueue *loopQueue);
bool KiwiLoopQueueIsFull(KiwiLoopQueue *loopQueue);

size_t KiwiLoopQueueSize(KiwiLoopQueue *loopQueue);
size_t KiwiLoopQueueCapacity(KiwiLoopQueue *loopQueue);

#endif // KIWI_COMPON_LOOP_QUEUE_H
