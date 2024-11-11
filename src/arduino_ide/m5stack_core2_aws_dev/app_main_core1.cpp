/**
 * @file app_main_core0.cpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief  Core1 アプリ
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <M5Core2.h>
#include <Adafruit_NeoPixel.h>
#include "common.hpp"
#include "app_main_core1.hpp"
#include "app_lcd.hpp"
#include "app_btn.hpp"
#include "app_filesystem.hpp"

SemaphoreHandle_t g_serial_mux;
portMUX_TYPE g_port_mux = portMUX_INITIALIZER_UNLOCKED;
static xTaskHandle s_xTaskCore1Main;

#define PIN       25
#define NUMPIXELS 10

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
RTC_DateTypeDef g_rtc_date;
RTC_TimeTypeDef g_rtc_time;

char g_rtc_date_buf[] = {0};
char g_rtc_time_buf[] = {0};

static void rgbled_test(void);
static void do_vibration(void);
static void get_rtc_time(void);

static void rgbled_test(void)
{
    pixels.clear();
    for (int it = 0; it < NUMPIXELS; it++)
    {
        int jt = it - 1;
        if (jt < 0) {
            jt = 8;
        }

        if ((it % 3) == 0) {
            pixels.setPixelColor(it, pixels.Color(0, 150, 0));
        } else if ((it % 3) == 1) {
            pixels.setPixelColor(it, pixels.Color(0, 0, 150));
        } else {
            pixels.setPixelColor(it, pixels.Color(150, 0, 0));
        }

        pixels.setPixelColor(jt, pixels.Color(0, 0, 0));
        pixels.show();
        // delay(10);
    }
}

// 振動モーター
static void do_vibration(void)
{
    M5.Axp.SetLDOEnable(3, true);
    delay(500);
    M5.Axp.SetLDOEnable(3, false);
}

static void get_rtc_time(void)
{
    M5.Rtc.GetDate(&g_rtc_date);
    M5.Rtc.GetTime(&g_rtc_time);

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
}

void vTaskCore1Main(void *p_parameter)
{
    DEBUG_PRINTF_RTOS("[Core1] ... vTaskCore1Main\n");

    while (1)
    {
        // TODO:メインタスク処理
#if 1
        M5.update();
        app_btn_polling();
        // get_rtc_time();
        // app_lcd_main();
#else
        // DeepSleep @DEEPSLEEP_TIME_US
        uint32_t dat = (DEEPSLEEP_TIME_US / 60) / 1000000;
        DEBUG_PRINTF_RTOS("[Core1] vTaskCore1Main ... No Proc. DeepSleep Now!\n");
        DEBUG_PRINTF_RTOS("DeepSleep : %d min\n", dat);
        esp_deep_sleep_start();
#endif
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void app_main_init_core1(void)
{
    M5.begin();
    delay(500); // ドライバ初期化待ち
    g_serial_mux = xSemaphoreCreateMutex();

    // Deep Sleep
    esp_sleep_enable_timer_wakeup(DEEPSLEEP_TIME_US);

    // UART
    Serial.begin(115200);

    // ボタン
    app_btn_init();

    // LED
    // pixels.begin();

    // LCD
    app_lcd_init();
    app_lcd_test();

    // File System(SD/SPIFS/FATFS)
    // TODO:下記エラーの原因調査
    // E (1073) I2S: i2s_driver_uninstall(2048): I2S port 0 has not installed
    app_fs_init();

    // FreeRTOS
    xTaskCreatePinnedToCore(vTaskCore1Main,    // コールバック関数ポインタ
                            "vTaskCore1Main",  // タスク名
                            8192,              // スタック
                            NULL,              // パラメータ
                            6,                 // 優先度(0～7、7が最優先)
                            &s_xTaskCore1Main, // ハンドル
                            CPU_CORE_1);       // Core0 or Core1
}

void app_main_core1(void)
{
    // loopタスクは不要なのでSuspend
    // DEBUG_PRINTF_RTOS("[Core1] ... loopTask\n");
    // vTaskDelay(10000 / portTICK_PERIOD_MS);
    vTaskSuspend(NULL);
}