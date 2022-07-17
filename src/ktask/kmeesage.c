/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-17
 * @description kiwi task message
 */

#include "kmessage.h"
#include "kmemory.h"

KiwiMessage *KiwiMessageDup(KiwiMessage *msg)
{
    if (msg == NULL) {
        return NULL;
    }
    KiwiMessage *newMsg = (KiwiMessage *)KIWI_ALLOC(sizeof(KiwiMessage));
    if (newMsg == NULL) {
        return NULL;
    }
    *newMsg = *msg;
    return newMsg;
}
void KiwiMessageFree(KiwiMessage *msg)
{
    if (msg == NULL) {
        return;
    }
    KIWI_SAFE_FREE(msg);
}

KiwiMsgReceipt *KiwiMsgReceiptDup(KiwiMsgReceipt *receipt)
{
    if (receipt == NULL) {
        return NULL;
    }
    KiwiMsgReceipt *newReceipt = (KiwiMsgReceipt *)KIWI_ALLOC(sizeof(KiwiMsgReceipt));
    if (newReceipt == NULL) {
        return NULL;
    }
    newReceipt->type = receipt->type;
    newReceipt->msg = NULL;
    if (receipt == NULL) {
        return newReceipt;
    }
    newReceipt->msg = KiwiMessageDup(receipt->msg);
    if (newReceipt->msg == NULL) {
        KIWI_SAFE_FREE(newReceipt);
        return NULL;
    }
    return newReceipt;
}

void KiwiMsgReceiptFree(KiwiMsgReceipt *receipt)
{
    if (receipt == NULL) {
        return;
    }
    KiwiMessageFree(receipt->msg);
    KIWI_SAFE_FREE(receipt);
}