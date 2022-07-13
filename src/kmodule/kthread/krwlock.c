/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description kiwi thread rw lock
 */

#include "krwlock.h"

bool KiwiRwlockInit(KiwiRwlock *rwlock)
{
    if (rwlock == NULL) {
        return false;
    }
    pthread_rwlock_init(&(rwlock->locker), NULL);
    return true;
}

void KiwiRwlockDeinit(KiwiRwlock *rwlock)
{
    if (rwlock == NULL) {
        return;
    }
    pthread_rwlock_destroy(&(rwlock->locker));
}

bool KiwiRwlockReadLock(KiwiRwlock *rwlock)
{
    if (rwlock == NULL) {
        return false;
    }
    pthread_rwlock_rdlock(&(rwlock->locker));
    return true;
}

void KiwiRwlockReadUnLock(KiwiRwlock *rwlock)
{
    if (rwlock == NULL) {
        return;
    }
    pthread_rwlock_unlock(&(rwlock->locker));
}

bool KiwiRwlockWriteLock(KiwiRwlock *rwlock)
{
    if (rwlock == NULL) {
        return false;
    }
    pthread_rwlock_wrlock(&(rwlock->locker));
    return true;
}

void KiwiRwlockWriteUnLock(KiwiRwlock *rwlock)
{
    if (rwlock == NULL) {
        return;
    }
    pthread_rwlock_unlock(&(rwlock->locker));
}
