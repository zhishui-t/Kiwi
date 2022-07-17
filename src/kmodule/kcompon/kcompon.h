/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-03
 * @description kiwi compone common def
 */

#ifndef KIWI_COMPON_H
#define KIWI_COMPON_H

#include "ktypes.h"

typedef void (*PfKiwiComponCleaner)(uintptr_t node);
typedef void (*PfKiwiComponCompare)(uintptr_t node, uintptr_t key);

#endif // KIWI_COMPON_Hs