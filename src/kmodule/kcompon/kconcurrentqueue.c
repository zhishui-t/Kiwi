/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description kiwi queue thread safe
 */
#include "kconcurrentqueue.h"
#include "kmemory.h"

typedef struct {
    uintptr_t data;
    KIWI_ATOMIC uintptr_t next;
} KiwiConcurrQueueNode;

KiwiConcurrQueueNode *KiwiConcurrQueueNodeCreate(const uintptr_t data)
{
    KiwiConcurrQueueNode *node = (KiwiConcurrQueueNode *)KIWI_ALLOC(sizeof(KiwiConcurrQueueNode));
    if (node == NULL) {
        return NULL;
    }
    KIWI_ATOMIC_INIT(node->next, 0);
    node->data = data;
    return node;
}

void KiwiConcurrQueueNodeFree(KiwiConcurrQueueNode *node)
{
    if (node == NULL) {
        return;
    }

    KIWI_SAFE_FREE(node);
}

KiwiConcurrQueue *KiwiConcurrQueueCreate(void)
{
    KiwiConcurrQueue *queue = (KiwiConcurrQueue *)KIWI_ALLOC(sizeof(KiwiConcurrQueue));
    if (queue == NULL) {
        return NULL;
    }
    KiwiConcurrQueueNode *node = KiwiConcurrQueueNodeCreate(0);
    if (node == NULL) {
        KIWI_SAFE_FREE(queue);
        return NULL;
    }
    KIWI_ATOMIC_INIT(queue->count, 0);
    KIWI_ATOMIC_INIT(queue->head, (uintptr_t)node);
    KIWI_ATOMIC_INIT(queue->tail, (uintptr_t)node);
    return queue;
}

void KiwiConcurrQueueDestroy(KiwiConcurrQueue *queue)
{
    if (queue == NULL) {
        return;
    }
    KiwiConcurrQueueNodeFree((KiwiConcurrQueueNode *)(queue->head));
    KIWI_ATOMIC_STORE(queue->head, 0);
    KIWI_ATOMIC_STORE(queue->tail, 0);
    KIWI_SAFE_FREE(queue);
}

bool KiwiConcurrQueuePush(KiwiConcurrQueue *queue, const uintptr_t data)
{
    if (queue == NULL) {
        return false;
    }
    KiwiConcurrQueueNode *node = KiwiConcurrQueueNodeCreate(data);
    if (node == NULL) {
        return false;
    }
    KiwiConcurrQueueNode *tail = NULL;
    do {
        tail = (KiwiConcurrQueueNode *)KIWI_ATOMIC_LOAD(queue->tail);
        if (tail == NULL) {
            KiwiConcurrQueueNodeFree(node);
            return false;
        }
    } while (!KIWI_ATOMIC_CAS(tail->next, NULL, node));
    KIWI_ATOMIC_CAS(queue->tail, tail, tail->next);
    KIWI_ATOMIC_INC(queue->count);
    return true;
}

bool KiwiConcurrQueuePop(KiwiConcurrQueue *queue, uintptr_t *data)
{
    if (KiwiConcurrQueueSize(queue) == 0) {
        return false;
    }
    if (data == NULL) {
        return false;
    }
    KIWI_ATOMIC_DEC(queue->count);
    return true;
}

size_t KiwiConcurrQueueSize(KiwiConcurrQueue *queue)
{
    return KIWI_ATOMIC_LOAD(queue->count);
}