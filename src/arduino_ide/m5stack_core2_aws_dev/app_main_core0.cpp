/**
 * @file app_main_core1.cpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief  Core1 アプリ
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "common.hpp"
#include "app_main_core0.hpp"

void vTaskCore0Main(void *p_parameter)
{
    DEBUG_PRINTF_RTOS("[Core0] ... vTaskCore0Main\n");

    while (1)
    {
        // TODO:Core0メインタスク処理
        NOP;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void app_main_init_core0(void)
{
#if 0
    // FreeRTOS
    xTaskCreatePinnedToCore(vTaskCore0Main,    // コールバック関数ポインタ
                            "vTaskCore0Main",  // タスク名
                            4096,              // スタック
                            NULL,              // パラメータ
                            0,                 // 優先度(0～7、7が最優先)
                            NULL,              // ハンドル
                            CPU_CORE_0);       // Core0 or Core1
#endif
}

void app_main_core0(void)
{
    // DEBUG_PRINTF_RTOS("[Core0] ... loopTask\n");
    // vTaskDelay(10000 / portTICK_PERIOD_MS);
    vTaskSuspend(NULL);
}