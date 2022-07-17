/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-17
 * @description kiwi task scheduler
 */

#ifndef KIWI_TASK_SCHEDULER_H
#define KIWI_TASK_SCHEDULER_H

#include "ktypes.h"
#include "katomic.h"
#include "kloopqueue.h"
#include "kworker.h"

typedef struct KiwiTask *KiwiTask;

typedef struct {
    KiwiTask *task;
    KIWI_ATOMIC int32_t ownerId;
    KiwiLoopQueue jobs;
} KiwiScheduler;

bool KiwiSchedulerInit(KiwiScheduler *scheduler);
void KiwiSchedulerDeinit(KiwiScheduler *scheduler);

bool KiwiSchedulerTryAcquire(KiwiScheduler *shedule, const int32_t workerId);
void KiwiSchedulerRelease(KiwiScheduler *shedule);

bool KiwiSchedulerDispatch(KiwiScheduler *shedule, KiwiWorker *worker);

#endif // KIWI_TASK_SCHEDULER_H