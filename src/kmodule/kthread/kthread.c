/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description kiwi thread
 */
#include "kthread.h"
#include <unistd.h>
#include "kmemory.h"

typedef struct {
    KiwiPfThreadFunc func;
    uintptr_t cdata;
} KiwiThread;

static void *KiwiThreadOnRun(void *args)
{
    KiwiThread *thread = (KiwiThread *)args;
    if (thread == NULL) {
        return NULL;
    }
    thread->func(thread->cdata);
    KIWI_SAFE_FREE(thread);
    return NULL;
}

bool KiwiThreadStart(KiwiPfThreadFunc func, const uintptr_t cdata)
{
    if (func == NULL) {
        return false;
    }
    KiwiThread *thread = (KiwiThread *)KIWI_ALLOC(sizeof(KiwiThread));
    if (thread == NULL) {
        return false;
    }
    thread->cdata = cdata;
    thread->func = func;
    pthread_t pid;
    if (pthread_create(&pid, NULL, KiwiThreadOnRun, (void *)(thread)) == 0) {
        KIWI_SAFE_FREE(thread);
        return false;
    }
    pthread_detach(pid);
    return true;
}

void KiwiThreadSleep(const uint32_t millSec)
{
    struct timespec req = {
        .tv_sec = 0,
        .tv_nsec = millSec * 1000 * 1000
    };
    nanosleep(&req, NULL);
}