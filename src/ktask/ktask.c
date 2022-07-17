/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-07
 * @description kiwi task 
 */

#include "ktask.h"
#include "kmemory.h"
#include "klog.h"

static void KiwiTaskServiceNodeCleaner(uintptr_t node)
{
    KiwiService *service = (KiwiService *)node;
    KiwiServiceFree(service);
}

static bool KiwiTaskInitWorkers(KiwiTask *task, const size_t workerCnt)
{
    task->workerCnt = workerCnt;
    task->workers = (KiwiWorker **)KIWI_ALLOC(sizeof(KiwiWorker *) * workerCnt);
    if (task->workers == NULL) {
        KiwiLog("[KiwiTaskInitWorkers] create failed\n");
        return false;
    }
    memset(task->workers, 0, sizeof(KiwiWorker *) *workerCnt));
    KiwiWorkerExector exector = {
        .onInit = NULL,
        .onDeinit = NULL,
        .onPoll = NULL
    };
    for (size_t i = 0; i < workerCnt; i++) {
        task->workers[i] = KiwiWorkerCreate((int32_t)i, &exector, task);
        if (task->workers[i] == NULL) {
            KiwiLog("[KiwiTaskInitWorkers] create worker failed workerId: %u\n", i);
            return false;
        }
    }
    return true;
}

static void KiwiTaskDeinitWorkers(KiwiTask *task)
{
    if (task->workers == NULL) {
        return;
    }

    for (size_t i = 0; i < task->workerCnt; i++) {
        if (task->workers[i] != NULL) {
            KiwiWorkerFree(task->workers);
        }
    }
    KIWI_SAFE_FREE(task->workers);
    task->workers = NULL;
}

static bool KiwiTaskInitServices(KiwiTask *task)
{
    task->services = KiwiVectorCreate(0, KiwiTaskServiceNodeCleaner);
    if (task->services == NULL) {
        KiwiLog("[KiwiTaskInitServices] create failed\n");
        return false;
    }
    return true;
}

KiwiTask *KiwiTaskCreate(const size_t workerCnt, KiwiSnax *snax)
{
    if (workerCnt == 0 || snax == NULL || snax->onCreate == NULL || snax->onPoll == NULL) {
        KiwiLog("[KiwiTaskCreate] param failed\n");
        return NULL;
    }
    KiwiTask *task = (KiwiTask *)KIWI_ALLOC(sizeof(KiwiTask));
    if (task == NULL) {
        KiwiLog("[KiwiTaskCreate] alloc failed\n");
        return NULL;
    }
    memset(task, 0, sizeof(KiwiTask));
    task->snax = *snax;
    KIWI_ATOMIC_INIT(task->isStarted, false);
    if (!(KiwiTaskInitWorkers(task, workerCnt))) {
        KiwiLog("[KiwiTaskCreate] init workers failed\n");
        KiwiTaskFree(task);
        return NULL;
    }

    if (!KiwiTaskInitServices(task)) {
        KiwiLog("[KiwiTaskCreate] init service failed\n");
        KiwiTaskFree(task);
        return NULL;
    }

    if (!KiwiSchedulerInit(&(task->scheduler))) {
        KiwiLog("[KiwiTaskCreate] init schedule failed\n");
        KiwiTaskFree(task);
        return NULL;
    }
    KiwiLog("[KiwiTaskCreate] task init ok\n");
    return task;
}

void KiwiTaskFree(KiwiTask *task)
{
    if (task == NULL) {
        return;
    }
    KiwiTaskDeinitWorkers(task->workers);
    KiwiVectorFree(task->services);
    task->services = NULL;
    KiwiSchedulerDeinit(&(task->scheduler));
    KIWI_SAFE_FREE(task);
}

int32_t KiwiTaskNewService(KiwiTask *task)
{

}

void KiwiTaskDelService(KiwiTask *task, const int32_t serviceId)
{

}

KiwiService *KiwiTaskService(KiwiTask *task, const int32_t serviceId)
{

}

bool KiwiTaskStart(KiwiTask *task)
{
    if (task == NULL) {
        return false;
    }
    if (KIWI_ATOMIC_LOAD(task->isStarted)) {
        KiwiLog("[KiwiTaskStart] task aleady started\n");
        return false;
    }
    KIWI_ATOMIC_STORE(task->isStarted, true);
    for (size_t i = 0; i < task->workerCnt; i++) {
        KiwiWorkerStart(task->workers[i]);
    }

    bool isStarted = true;
    while (true) {
        for (size_t i = 0; i < task->workerCnt; i++) {
            if (!KiwiWorkerIsRun(task->workers[i])) {
                isStarted = false;
                break;
            }
        }
        if (isStarted) {
            break;
        }
        KiwiThreadSleep(10);
    }
    KiwiLog("[KiwiTaskStart] task started\n");
}

void KiwiTaskStop(KiwiTask *task)
{
    KiwiLog("[KiwiTaskStart] task top\n");
}

KiwiWorker *KiwiTaskWorker(KiwiTask *task, const int32_t workerId)
{

}