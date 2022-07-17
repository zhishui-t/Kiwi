/**
 * @copyright Copyright (c) 2022 ~ 2022
 * @author zhishui-t
 * @date 2022-07-15
 * @description kiwi log
 */

#ifndef KIWI_LOG_H
#define KIWI_LOG_H

#include <stdio.h>

#define KiwiLog(format, ...) \
    do { \
        fprintf(stderr, format, ##__VA_ARGS__); \
    } while (0)

#endif // KIWI_LOG_H
