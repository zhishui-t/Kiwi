/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description kiwi loop queue
 */

#include "kloopqueue.h"
#include "kmemory.h"

KiwiLoopQueue *KiwiLoopQueueCreate(const size_t capacity)
{
    if (capacity == 0) {
        return NULL;
    }
    
    KiwiLoopQueue *loopQueue = (KiwiLoopQueue *)KIWI_ALLOC(sizeof(KiwiLoopQueue));
    if (loopQueue == NULL) {
        return NULL;
    }
    memset(loopQueue, 0, sizeof(KiwiLoopQueue));
    loopQueue->capacity = capacity + 1;
    loopQueue->datas = (uintptr_t *)KIWI_ALLOC(sizeof(uintptr_t) * loopQueue->capacity);
    if (loopQueue->datas == NULL) {
        KIWI_SAFE_FREE(loopQueue);
        return NULL;
    }
    memset(loopQueue->datas, 0, sizeof(uintptr_t) * loopQueue->capacity);
    return loopQueue;
}

void KiwiLoopQueueDestroy(KiwiLoopQueue *loopQueue)
{
    if (loopQueue == NULL) {
        return;
    }
    KIWI_SAFE_FREE(loopQueue->datas);
    KIWI_SAFE_FREE(loopQueue);
}

bool KiwiLoopQueuePush(KiwiLoopQueue *loopQueue, uintptr_t data)
{
    if (KiwiLoopQueueIsFull(loopQueue)) {
        return false;
    }
    loopQueue->datas[loopQueue->rear] = data;
    loopQueue->rear = (loopQueue->rear + 1) % loopQueue->capacity;
    return true;
}

bool KiwiLoopQueuePop(KiwiLoopQueue *loopQueue, uintptr_t *data)
{
    if (KiwiLoopQueueIsEmpty(loopQueue)) {
        return false;
    }
    if (data == NULL) {
        return false;
    }
    *data = loopQueue->datas[loopQueue->front];
    loopQueue->front = (loopQueue->front + 1) % loopQueue->capacity;
    return true;
}

bool KiwiLoopQueueIsEmpty(KiwiLoopQueue *loopQueue)
{
    if (loopQueue == NULL) {
        return true;
    }

    return loopQueue->front == loopQueue->rear;
}

bool KiwiLoopQueueIsFull(KiwiLoopQueue *loopQueue)
{
    if (loopQueue == NULL) {
        return true;
    }

    return loopQueue->front == ((loopQueue->rear + 1) % loopQueue->capacity);
}

size_t KiwiLoopQueueSize(KiwiLoopQueue *loopQueue)
{
    if (loopQueue == NULL) {
        return 0;
    }    
    return (loopQueue->rear - loopQueue->front + loopQueue->capacity) % loopQueue->capacity;
}

size_t KiwiLoopQueueCapacity(KiwiLoopQueue *loopQueue)
{
    if (loopQueue == NULL) {
        return 0;
    }
    return loopQueue->capacity - 1;
}
