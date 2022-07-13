/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description kiwi thread
 */
#include "kthread.h"
#include <unistd.h>
#include "kmemory.h"

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

bool KiwiThreadStart(KiwiThread *thread)
{
    if (thread == NULL) {
        return false;
    }
    if (thread->func == NULL) {
        return false;
    }
    KiwiThread *threadInfo = (KiwiThread *)KIWI_ALLOC(sizeof(KiwiThread));
    if (threadInfo == NULL) {
        return false;
    }
    *threadInfo = *thread;
    pthread_t pid;
    if (pthread_create(&pid, NULL, KiwiThreadOnRun, (void *)(threadInfo)) == 0) {
        KIWI_SAFE_FREE(threadInfo);
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