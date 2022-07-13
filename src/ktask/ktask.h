/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-07
 * @description kiwi task 
 */

#ifndef KIWI_TASK_H
#define KIWI_TASK_H

#include "ktypes.h"

typedef struct {
    
} KiwiTask;

bool KiwiTaskInit();
void KiwiTaskDeinit();

bool KiwiTaskStart();
void KiwiTaskStop();


#endif // KIWI_TASK_H