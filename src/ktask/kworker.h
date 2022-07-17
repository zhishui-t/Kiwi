/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-15
 * @description kiwi task worker
 */

#ifndef KIWI_TASK_WORKER_H
#define KIWI_TASK_WORKER_H

#include "ktypes.h"
#include "katomic.h"

typedef struct KiwiTask KiwiTask;
typedef struct KiwiWorker KiwiWorker;

typedef enum {
    K_W_ST_UNKONW = 0,
    K_W_ST_INIT,
    K_W_ST_RUNNING,
    K_W_ST_YIELD,
    K_W_ST_STOP,
    K_W_ST_EXIT
} KiwiWorkerStatus;

typedef struct {
    KIWI_ATOMIC int32_t ready;
    KIWI_ATOMIC int32_t done;
} KiwiWorkerJob;

typedef bool (*PfKiwiWorkerOnInit)(KiwiTask *task, KiwiWorker *worker);
typedef bool (*PfKiwiWorkerOnPoll)(KiwiTask *task, KiwiWorker *worker);
typedef void (*PfKiwiWorkerOnDeinit)(KiwiTask *task, KiwiWorker *worker);

typedef struct {
    PfKiwiWorkerOnInit onInit;
    PfKiwiWorkerOnPoll onPoll;
    PfKiwiWorkerOnDeinit onDeinit;
} KiwiWorkerExector;

struct KiwiWorker {
    int32_t id;
    KiwiWorkerExector exector;
    KiwiWorkerJob jobs;
    KiwiTask *task;
    uint8_t status;
};

KiwiWorker *KiwiWorkerCreate(const int32_t workerId, KiwiWorkerExector *exector, KiwiTask *task);
void KiwiWorkerFree(KiwiWorker *worker);

bool KiwiWorkerIsRun(KiwiWorker *worker);
void KiwiWorkerStart(KiwiWorker *worker);
void KiwiWorkerStop(KiwiWorker *worker);
void KiwiWorkerYield(KiwiWorker *worker);
void KiwiWorkerResume(KiwiWorker *worker); 

uint8_t KiwiWorkerStatus(KiwiWorker *worker);

bool KiwiWorkerHasJob(KiwiWorker *worker);
bool KiwiWorkerAssignJob(KiwiWorker *worker, const int32_t job);
int32_t KiwiWorkerGetJob(KiwiWorker *worker);

bool KiwiWorkerCompleteJob(KiwiWorker *worker, const int32_t job);
int32_t KiwiWorkerDoneJob(KiwiWorker *worker);

#endif // KIWI_TASK_WORKER_H
