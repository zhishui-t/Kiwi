/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-15
 * @description kiwi task worker
 */

#include "kworker.h"
#include "kmemory.h"
#include "klog.h"
#include "kthread.h"

#define KIWI_WORKER_DELAY_TIME (10)

KiwiWorker *KiwiWorkerCreate(const int32_t workerId, KiwiWorkerExector *exector, KiwiTask *task)
{
    if (task == NULL || workerId < 0) {
        return NULL;
    }
    if (exector == NULL || exector->onPoll == NULL) {
        return NULL;
    }
    KiwiWorker *worker = (KiwiWorker *)KIWI_ALLOC(sizeof(KiwiWorker));
    if (worker == NULL) {
        return NULL;
    }
    memset(worker, 0, sizeof(KiwiWorker));
    worker->exector = *exector;
    worker->id = workerId;
    KIWI_ATOMIC_INIT(worker->status, K_W_ST_UNKONW);
    KIWI_ATOMIC_INIT(worker->jobs.ready, -1);
    KIWI_ATOMIC_INIT(worker->jobs.done, -1);
    worker->task = task;
    return worker;
}

void KiwiWorkerFree(KiwiWorker *worker)
{
    if (worker == NULL) {
        return;
    }
    KIWI_SAFE_FREE(worker);
}

static void KiwiWorkerSetStatus(KiwiWorker *worker, const uint8_t status)
{
    uint8_t oldStatus = KIWI_ATOMIC_LOAD(worker->status);
    KiwiLog("worker[id: %d] status change %u --> %u \n", worker->id, oldStatus, status);
    KIWI_ATOMIC_STORE(worker->status, status);
}

void KiwiWorkerThreadRunner(uintptr_t cdata)
{
    KiwiWorker *worker = (KiwiWorker *)cdata;
    if (worker->exector.onInit != NULL && !worker->exector.onInit(worker->task, worker)) {
        KiwiWorkerSetStatus(worker, K_W_ST_EXIT);
        return;
    }
    KiwiWorkerSetStatus(worker, K_W_ST_RUNNING);
    uint8_t status;
    while (true) {
        status = KiwiWorkerStatus(worker);
        if (status == K_W_ST_STOP) {
            break;
        }
        if (status == K_W_ST_YIELD) {
            KiwiThreadSleep(KIWI_WORKER_DELAY_TIME);
            continue;
        }
        if (!worker->exector.onPoll(worker->task, worker)) {
            // 执行失败，睡眠一会，防止线程死循环
            KiwiThreadSleep(KIWI_WORKER_DELAY_TIME);
        }
    }
    if (worker->exector.onDeinit != NULL) {
        worker->exector.onDeinit(worker->task, worker);
    }
    KiwiWorkerSetStatus(worker, K_W_ST_EXIT);
}

bool KiwiWorkerIsRun(KiwiWorker *worker)
{
    uint8_t status = KiwiWorkerStatus(worker);
    return status == K_W_ST_RUNNING || status == K_W_ST_YIELD;
}

void KiwiWorkerStart(KiwiWorker *worker)
{
    if (worker == NULL) {
        return;
    }

    KiwiWorkerSetStatus(worker, K_W_ST_INIT);
    if (!KiwiThreadStart(KiwiWorkerThreadRunner, worker)) {
        KiwiWorkerSetStatus(worker, K_W_ST_EXIT);
    }
}

void KiwiWorkerStop(KiwiWorker *worker)
{
    uint8_t status = KiwiWorkerStatus(worker);
    if (status != K_W_ST_YIELD && status != K_W_ST_RUNNING) {
        return;
    }
    KiwiWorkerSetStatus(worker, K_W_ST_STOP);
}

void KiwiWorkerYield(KiwiWorker *worker)
{
    uint8_t currStatus = K_W_ST_RUNNING;
    if (KIWI_ATOMIC_CAS(worker->status, currStatus, K_W_ST_YIELD)) {
        KiwiLog("worker[id: %d] status change %u --> %u \n", worker->id, currStatus, K_W_ST_YIELD);
    }
}

void KiwiWorkerResume(KiwiWorker *worker)
{
    uint8_t currStatus = K_W_ST_YIELD;
    if (KIWI_ATOMIC_CAS(worker->status, currStatus, K_W_ST_RUNNING)) {
        KiwiLog("worker[id: %d] status change %u --> %u \n", worker->id, currStatus, K_W_ST_RUNNING);
    }
}

uint8_t KiwiWorkerStatus(KiwiWorker *worker)
{
    if (worker == NULL) {
        return K_W_ST_UNKONW;
    }
    return KIWI_ATOMIC_LOAD(worker->status);
}

bool KiwiWorkerHasJob(KiwiWorker *worker)
{
    if (worker == NULL) {
        return false;
    }
    return KIWI_ATOMIC_LOAD(worker->jobs.ready) > 0;
}

bool KiwiWorkerAssignJob(KiwiWorker *worker, const int32_t job)
{
    if (worker == NULL || job < 0) {
        return false;
    }
    if (KiwiWorkerHasJob(worker)) {
        return false;
    }
    KIWI_ATOMIC_STORE(worker->jobs.ready, job);
    return true;
}

int32_t KiwiWorkerGetJob(KiwiWorker *worker)
{
    if (worker == NULL) {
        return -1;
    }
    int32_t job = KIWI_ATOMIC_LOAD(worker->jobs.ready);
    if (job < 0) {
        return -1;
    }
    if (!KIWI_ATOMIC_CAS(worker->jobs.ready, job, -1)) {
        return -1;
    }
    return job;
}

bool KiwiWorkerCompleteJob(KiwiWorker *worker, const int32_t job)
{
    if (worker == NULL || job < 0) {
        return false;
    }

    int32_t invalidJob = -1;
    return KIWI_ATOMIC_CAS(worker->jobs.done, invalidJob, job);
}

int32_t KiwiWorkerDoneJob(KiwiWorker *worker)
{
    if (worker == NULL) {
        return -1;
    }
    int32_t job = KIWI_ATOMIC_LOAD(worker->jobs.done);
    if (!KIWI_ATOMIC_CAS(worker->jobs.done, job, -1)) {
        return -1;
    }
    return job;
}
