/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description kiwi atomic 
 */
#ifndef KIWI_MOUDLE_THREAD_ATOMIC_H
#define KIWI_MOUDLE_THREAD_ATOMIC_H

#include <stdatomic.h>
#include "ktypes.h"

#define KIWI_ATOMIC _Atomic
#define KIWI_ATOMIC_INIT(var, val) atomic_init(&(var), (val))
#define KIWI_ATOMIC_STORE(var, val) atomic_store(&(var), (val))
#define KIWI_ATOMIC_LOAD(var) atomic_load(&(var))
#define KIWI_ATOMIC_INC(var) atomic_fetch_inc(&(var))
#define KIWI_ATOMIC_DEC(var) atomic_fetch_dec(&(var))

static inline bool KiwiAtomicCAS(atomic_uintptr_t *ptr, uintptr_t oVal, uintptr_t nVal)
{
	return atomic_compare_exchange_weak(ptr, &oVal, nVal) == 1;
}

#define KIWI_ATOMIC_CAS(ptr, oVal, nVal) \
    KiwiAtomicCAS((atomic_uintptr_t *)(&(ptr)), (uintptr_t)(oVal), (uintptr_t)(nVal))

#endif // KIWI_MOUDLE_THREAD_ATOMIC_H
