/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-07
 * @description kiwi thread spinlock
 */

#include "kspinlock.h"

struct KiwiSpinlock {
    KIWI_ATOMIC bool lock;
};

void KiwiSpinlockInit(KiwiSpinlock *spinlock)
{
    if (spinlock == NULL) {
        return;
    }
    KIWI_ATOMIC_INIT(spinlock->lock, false);
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
    bool srcStatus = false;
    return KIWI_ATOMIC_CAS(spinlock->lock, srcStatus, true);
}

void KiwiSpinlockLock(KiwiSpinlock *spinlock)
{
    if (spinlock == NULL) {
        return;
    }
    bool srcStatus = false;
    while (!KIWI_ATOMIC_CAS(spinlock->lock, srcStatus, true)) {}
}

void KiwiSpinlockUnlock(KiwiSpinlock *spinlock)
{
    if (spinlock == NULL) {
        return;
    }
    bool srcStatus = true;
    KIWI_ATOMIC_CAS(spinlock->lock, srcStatus, false);
}