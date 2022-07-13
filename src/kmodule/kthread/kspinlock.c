/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-07
 * @description kiwi thread spinlock
 */

#include "kspinlock.h"

void KiwiSpinlockInit(KiwiSpinlock *spinlock)
{
    if (spinlock == NULL) {
        return;
    }
    KIWI_ATOMIC_INIT(spinlock->lock, 0);
}

void KiwiSpinlockDeinit(KiwiSpinlock *spinlock)
{
    if (spinlock == NULL) {
        return;
    }
    KIWI_ATOMIC_INIT(spinlock->lock, 0);
}

bool KiwiSpinlockTryLock(KiwiSpinlock *spinlock)
{
    if (spinlock == NULL) {
        return false;
    }
    return KIWI_ATOMIC_CAS(spinlock->lock, 0, 1);
}

void KiwiSpinlockLock(KiwiSpinlock *spinlock)
{
    if (spinlock == NULL) {
        return;
    }
    while (!KIWI_ATOMIC_CAS(spinlock->lock, 0, 1)) {}
}

void KiwiSpinlockUnlock(KiwiSpinlock *spinlock)
{
    if (spinlock == NULL) {
        return;
    }
    KIWI_ATOMIC_CAS(spinlock->lock, 1, 0);
}