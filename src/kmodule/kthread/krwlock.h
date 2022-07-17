/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description kiwi thread rw lock
 */

#ifndef KIWI_MODULE_THREAD_RW_LOCK_H
#define KIWI_MODULE_THREAD_RW_LOCK_H

#include <pthread.h>
#include "ktypes.h"

typedef struct KiwiRwlock KiwiRwlock;

bool KiwiRwlockInit(KiwiRwlock *rwlock);
void KiwiRwlockDeinit(KiwiRwlock *rwlock);

bool KiwiRwlockReadLock(KiwiRwlock *rwlock);
void KiwiRwlockReadUnLock(KiwiRwlock *rwlock);

bool KiwiRwlockWriteLock(KiwiRwlock *rwlock);
void KiwiRwlockWriteUnLock(KiwiRwlock *rwlock);

#endif // KIWI_MODULE_THREAD_RW_LOCK_H