/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-07
 * @description kiwi service
 */

#ifndef KIWI_TASK_SERVICE_H
#define KIWI_TASK_SERVICE_H

#include "ktypes.h"
#include "kloopqueue.h"
#include "kmessage.h"

typedef struct KiwiTask KiwiTask; 

typedef enum {
    K_S_ST_INIT = 1,
    K_S_ST_IDLE,
    K_S_ST_READY,
    K_S_ST_WOKE,
    K_S_ST_CLOSE
} KiwiServiceStatus;

typedef struct {
    int32_t id;
    uint8_t workId;
    uint8_t status;
    KiwiLoopQueue msgs;
    KiwiMessage *send;
    KiwiMsgReceipt receiptMsg;
    KiwiTask *task;
    uintptr_t snaxInst;
} KiwiService;

KiwiService *KiwiServiceCreate(const int32_t serviceId, KiwiTask *task);
void KiwiServiceFree(KiwiService *service);

void KiwiServiceResume(KiwiService *service);

uint8_t KiwiServiceStatus(KiwiService *service);
void KiwiServiceSetStatus(KiwiService *service, const uint8_t status);

KiwiMsgReceipt *KiwiServicePushMessage(KiwiService *service, const KiwiMessage *msg);
KiwiMessage *KiwiServicePopMessage(KiwiService *service);

void KiwiServiceWirteReceipt(KiwiService *service, const KiwiMsgReceipt *receipt);
KiwiMsgReceipt *KiwiServiceReadReceipt(KiwiService *service);


#endif // KIWI_TASK_SERVICE_H