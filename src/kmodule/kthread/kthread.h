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

bool KiwiThreadStart(KiwiPfThreadFunc func, const uintptr_t cdata);
void KiwiThreadSleep(const uint32_t millSec);

#endif // KIWI_MODULE_THREAD_H