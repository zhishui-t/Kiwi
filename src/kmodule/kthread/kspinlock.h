/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-07
 * @description kiwi thread spinlock
 */

#ifndef KIWI_MODULE_THREAD_SPINLOCK_H
#define KIWI_MODULE_THREAD_SPINLOCK_H

#include "katomic.h"
#include "ktypes.h"

typedef struct KiwiSpinlock KiwiSpinlock;

void KiwiSpinlockInit(KiwiSpinlock *spinlock);
void KiwiSpinlockDeinit(KiwiSpinlock *spinlock);

bool KiwiSpinlockTryLock(KiwiSpinlock *spinlock);
void KiwiSpinlockLock(KiwiSpinlock *spinlock);
void KiwiSpinlockUnlock(KiwiSpinlock *spinlock);

#endif // KIWI_MODULE_THREAD_SPINLOCK_H