/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-07
 * @description kiwi task 
 */

#ifndef KIWI_TASK_H
#define KIWI_TASK_H

#include "ktypes.h"
#include "kworker.h"
#include "kscheduler.h"
#include "kservice.h"
#include "kvector.h"

typedef uintptr_t (*PfKiwiSnaxCreate)(KiwiService *service);
typedef bool (*PfKiwiSnaxOnPoll)(KiwiService *service);

typedef struct {
    PfKiwiSnaxCreate onCreate;
    PfKiwiSnaxOnPoll onPoll;
} KiwiSnax;

typedef struct {
    KIWI_ATOMIC bool isStarted;
    size_t workerCnt;
    KiwiWorker **workers;
    KiwiScheduler scheduler;
    KiwiVector *services; // TODO: 这个后面换成hash表
    KiwiSnax snax;
} KiwiTask;

KiwiTask *KiwiTaskCreate(const size_t workerCnt, KiwiSnax *snax);
void KiwiTaskFree(KiwiTask *task);

int32_t KiwiTaskNewService(KiwiTask *task);
void KiwiTaskDelService(KiwiTask *task, const int32_t serviceId);
KiwiService *KiwiTaskService(KiwiTask *task, const int32_t serviceId);

bool KiwiTaskStart(KiwiTask *task);
void KiwiTaskStop(KiwiTask *task);

KiwiWorker *KiwiTaskWorker(KiwiTask *task, const int32_t workerId);

#endif // KIWI_TASK_H