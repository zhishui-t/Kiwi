/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-07
 * @description kiwi service
 */

#ifndef KIWI_TASK_SERVICE_H
#define KIWI_TASK_SERVICE_H

#include "ktypes.h"

typedef enum {
    K_S_T_NONE = 1,
    K_S_T_NORMAL,
    K_S_T_SYSYTEM,
} KiwiServiceType;

typedef enum {
    K_S_ST_INIT = 1,
    K_S_ST_IDLE,
    K_S_ST_WOKE,
    K_S_ST_CLOSE
} KiwiServiceStatus;

typedef struct {
    uint32_t type : 8;
    uint32_t id  : 24;
} KiwiServiceId;

typedef struct {
    KiwiServiceId sid;
    uint8_t workId;
    uint8_t status;
} KiwiService;

#endif // KIWI_TASK_SERVICE_H