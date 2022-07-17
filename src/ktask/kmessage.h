/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-17
 * @description kiwi task message
 */

#ifndef KIWI_TASK_MESSAFE_H
#define KIWI_TASK_MESSAFE_H

#include "ktypes.h"

typedef enum {
    K_MSG_TYPE_REQ = 1,
    K_MSG_TYPE_RSP,
    K_MSG_TYPE_ERROR,
} KiwiMsgType;

typedef enum {
    K_MSG_SEND_RECEIPT_NONE = 1,
    K_MSG_SEND_RECEIPT_OK,
    K_MSG_SEND_RECEIPT_FAILED,
    K_MSG_SEND_RECEIPT_BLOCKED,
} KiwiMsgReceiptType;

typedef struct {
    KiwiMessage *msg;
    uint8_t type;
} KiwiMsgReceipt;

typedef struct {
    int32_t srcId;
    int32_t destId;
    uint32_t sessionId;
    uint8_t type;
    uint8_t *body;
    size_t bodyLen;
} KiwiMessage;

KiwiMessage *KiwiMessageDup(KiwiMessage *msg);
void KiwiMessageFree(KiwiMessage *msg);

KiwiMsgReceipt *KiwiMsgReceiptDup(KiwiMsgReceipt *receipt);
void KiwiMsgReceiptFree(KiwiMsgReceipt *receipt);

#endif // KIWI_TASK_MESSAFE_H
