/**
 * @file app_main.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief  Core アプリ
 * @version 0.1
 * @date 2024-12-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <M5NanoC6.h>
#include "common.hpp"
#include "app_main.hpp"
#include "app_btn.hpp"
#include "app_filesystem.hpp"
#include "app_wifi.hpp"
#include "app_neopixel.hpp"

SemaphoreHandle_t g_serial_mux;
portMUX_TYPE g_port_mux = portMUX_INITIALIZER_UNLOCKED;
static xTaskHandle s_xTaskMain;
static xTaskHandle s_xTaskWiFi;
static bool s_wifi_flag = true;

#if 0
RTC_DateTypeDef g_rtc_date;
RTC_TimeTypeDef g_rtc_time;

char g_rtc_date_buf[] = {0};
char g_rtc_time_buf[] = {0};
#endif

static void get_rtc_time(void);

static void get_rtc_time(void)
{
#if 0
    // TODO:M5NanoC6用のRTC時刻取得処理の実装
    NanoC6.Rtc.GetDate(&g_rtc_date);
    NanoC6.Rtc.GetTime(&g_rtc_time);

    memset(&g_rtc_date_buf[0], 0x00, sizeof(g_rtc_date_buf));
    memset(&g_rtc_time_buf[0], 0x00, sizeof(g_rtc_time_buf));
    sprintf(g_rtc_date_buf,"%04d/%02d/%02d\n",
            g_rtc_date.Year,
            g_rtc_date.Month,
            g_rtc_date.Date);
    sprintf(g_rtc_time_buf,"%02d:%02d:%02d\n",
            g_rtc_time.Hours,
            g_rtc_time.Minutes,
            g_rtc_time.Seconds);
#endif
}

void vTaskCoreMain(void *p_parameter)
{
    DEBUG_PRINTF_RTOS("[Core] ... vTaskCoreMain\n");

    while (1)
    {
    // TODO:メインタスク処理
        NanoC6.update();
#if 1
        app_btn_polling();
        // get_rtc_time();
#else
        // DeepSleep @DEEPSLEEP_TIME_US
        uint32_t dat = (DEEPSLEEP_TIME_US / 60) / 1000000;
        DEBUG_PRINTF_RTOS("[Core] vTaskCoreMain ... No Proc. DeepSleep Now!\n");
        DEBUG_PRINTF_RTOS("DeepSleep : %d min\n", dat);
        esp_deep_sleep_start();
#endif
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void vTaskWiFi(void *p_parameter)
{
    DEBUG_PRINTF_RTOS("[Core] vTaskWiFi\n");
    app_wifi_init();

    while (1)
    {
        s_wifi_flag = app_wifi_main();

        if(s_wifi_flag != true){
            DEBUG_PRINTF_RTOS("[Core] vTaskWiFi Suspend now!\n");
            vTaskSuspend(NULL);
            DEBUG_PRINTF_RTOS("[Core] vTaskWiFi Resume!\n");
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void app_main_init(void)
{
    NanoC6.begin();
    g_serial_mux = xSemaphoreCreateMutex();

    // Deep Sleep
    esp_sleep_enable_timer_wakeup(DEEPSLEEP_TIME_US);

    // UART
    Serial.begin(115200);
    while (!Serial) {
        WDT_TOGGLE;
    }

    // ボタン
    app_btn_init();

    // LED
    pinMode(IR_LED_PIN, OUTPUT);
    pinMode(OB_LED_PIN, OUTPUT);
    // digitalWrite(OB_LED_PIN, HIGH);
    app_neopixel_init();
    app_neopixel_main(16, 0, 0, 0, true, false); // red, on

    // File System(SD/SPIFS/FATFS)
    // app_fs_init();

    // FreeRTOS
    xTaskCreatePinnedToCore(vTaskCoreMain,    // コールバック関数ポインタ
                            "vTaskCoreMain",  // タスク名
                            8192,              // スタック
                            NULL,              // パラメータ
                            3,                 // 優先度(0～7、7が最優先)
                            &s_xTaskMain, // ハンドル
                            CPU_CORE_1);       // Core0 or Core

    xTaskCreatePinnedToCore(vTaskWiFi,     // コールバック関数ポインタ
                            "vTaskWiFi",   // タスク名
                            8192,              // スタック
                            NULL,              // パラメータ
                            6,                 // 優先度(0～7、7が最優先)
                            &s_xTaskWiFi, // ハンドル
                            CPU_CORE_1);       // Core0 or Core
}

void app_main(void)
{
    // loopタスクは不要なのでSuspend
    // DEBUG_PRINTF_RTOS("[Core] ... loopTask\n");
    // vTaskDelay(10000 / portTICK_PERIOD_MS);
    vTaskSuspend(NULL);
}