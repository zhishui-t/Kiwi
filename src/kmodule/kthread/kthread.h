/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description kiwi thread
 */

#ifndef KIWI_MODULE_THREAD_H
#define KIWI_MODULE_THREAD_H

#include <pthread.h>
#include "ktypes.h"

typedef void (*KiwiPfThreadFunc)(uintptr_t cdata);

typedef struct {
    KiwiPfThreadFunc func;
    uintptr_t cdata;
} KiwiThread;

bool KiwiThreadStart(KiwiThread *thread);
void KiwiThreadSleep(const uint32_t millSec);

#endif // KIWI_MODULE_THREAD_H