/**
 * @file app_main_core1.hpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief  Core1 アプリ
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef APP_MAIN_CORE1_HPP
#define APP_MAIN_CORE1_HPP

// FreeRTOS
// #include <task.h>

// DeepSleep
#include "esp_sleep.h"
#define DEEPSLEEP_TIME_US_30SEC   30ULL * 1000000ULL      // 30秒
#define DEEPSLEEP_TIME_US_1MIN    60ULL * 1000000ULL      // 1分
#define DEEPSLEEP_TIME_US_2MIN    120ULL * 1000000ULL     // 2分
#define DEEPSLEEP_TIME_US_3MIN    180ULL * 1000000ULL     // 3分
#define DEEPSLEEP_TIME_US_5MIN    300ULL * 1000000ULL     // 5分
#define DEEPSLEEP_TIME_US_10MIN   600ULL * 1000000ULL     // 10分
#define DEEPSLEEP_TIME_US_15MIN   900ULL * 1000000ULL     // 15分
#define DEEPSLEEP_TIME_US_20MIN   1200ULL * 1000000ULL    // 20分
#define DEEPSLEEP_TIME_US_30MIN   1800ULL * 1000000ULL    // 30分
#define DEEPSLEEP_TIME_US_1HOUR   3600ULL * 1000000ULL    // 1時間
#define DEEPSLEEP_TIME_US_2HOUR   7200ULL * 1000000ULL    // 2時間
#define DEEPSLEEP_TIME_US_3HOUR   10800ULL * 1000000ULL   // 3時間
#define DEEPSLEEP_TIME_US_5HOUR   18000ULL * 1000000ULL   // 5時間
#define DEEPSLEEP_TIME_US_8HOUR   28800ULL * 1000000ULL   // 8時間
#define DEEPSLEEP_TIME_US_12HOUR  43200ULL * 1000000ULL   // 12時間
#define DEEPSLEEP_TIME_US_24HOUR  86400ULL * 1000000ULL   // 24時間

#define DEEPSLEEP_TIME_US         DEEPSLEEP_TIME_US_1MIN

void app_main_init_core1(void);
void app_main_core1(void);

#endif /* APP_MAIN_CORE1_HPP */