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

#include "common.hpp"
#include "app_main_core1.hpp"
#include "m5scp_lcd.hpp"

SemaphoreHandle_t g_serial_mux;
portMUX_TYPE g_port_mux = portMUX_INITIALIZER_UNLOCKED;
static xTaskHandle s_xTaskCore1Main;
static xTaskHandle s_xTaskCore1UART;

static uint8_t s_led_val = 0;
static uint8_t s_ir_led_val = 0;

/**
 * @brief ボタンA(GPIO37)割り込みハンドラ
 * 
 */
void IRAM_ATTR btn_a_isr()
{
    // TODO: ボタンAの割込み処理
    NOP;
}

/**
 * @brief ボタンB(GPIO39)割り込みハンドラ
 * 
 */
void IRAM_ATTR btn_b_isr()
{
    // TODO: ボタンBの割込み処理
    NOP;
}

void vTaskCore1UART(void *p_parameter)
{
    DEBUG_PRINTF_RTOS("[Core1] ... vTaskCore1UART\n");
    m5scp_lcd_init();

    while (1)
    {
        // TODO:UARTタスク処理
        digitalWrite(LED_PIN, s_led_val);
        digitalWrite(IRLED_PIN, s_ir_led_val);
        s_led_val = !s_led_val;
        s_ir_led_val = !s_ir_led_val;
        DEBUG_PRINTF_RTOS("LED = %d\n", s_led_val);
        DEBUG_PRINTF_RTOS("IR LED = %d\n", s_ir_led_val);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void vTaskCore1Main(void *p_parameter)
{
    DEBUG_PRINTF_RTOS("[Core1] ... vTaskCore1Main\n");
    m5scp_lcd_init();

    while (1)
    {
        // TODO:メインタスク処理
#if 1
        m5scp_lcd_main();
#else
        // DeepSleep @DEEPSLEEP_TIME_US
        uint32_t dat = (DEEPSLEEP_TIME_US / 60) / 1000000;
        DEBUG_PRINTF_RTOS("[Core1] vTaskCore1Main ... No Proc. DeepSleep Now!\n");
        DEBUG_PRINTF_RTOS("DeepSleep : %d min\n", dat);
        esp_deep_sleep_start();
#endif
        vTaskDelay(8 / portTICK_PERIOD_MS);
    }
}

void app_main_init_core1(void)
{
    // Deep Sleep
    esp_sleep_enable_timer_wakeup(DEEPSLEEP_TIME_US);

    // GPIO
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(IRLED_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_A_PIN, INPUT_PULLUP);
    pinMode(BUTTON_B_PIN, INPUT_PULLUP);
    attachInterrupt(BUTTON_A_PIN, btn_a_isr, CHANGE);
    attachInterrupt(BUTTON_B_PIN, btn_b_isr, CHANGE);

    // UART
    Serial.begin(115200);

    // FreeRTOS
    g_serial_mux = xSemaphoreCreateMutex();
    xTaskCreatePinnedToCore(vTaskCore1Main,    // コールバック関数ポインタ
                            "vTaskCore1Main",  // タスク名
                            8192,              // スタック
                            NULL,              // パラメータ
                            3,                 // 優先度(0～7、7が最優先)
                            &s_xTaskCore1Main, // ハンドル
                            CPU_CORE_1);       // Core0 or Core1

    xTaskCreatePinnedToCore(vTaskCore1UART,    // コールバック関数ポインタ
                            "vTaskCore1UART",  // タスク名
                            4096,              // スタック
                            NULL,              // パラメータ
                            1,                 // 優先度(0～7、7が最優先)
                            &s_xTaskCore1UART, // ハンドル
                            CPU_CORE_1);       // Core0 or Core1
}

void app_main_core1(void)
{
    // loopタスクは不要なのでSuspend
    // DEBUG_PRINTF_RTOS("[Core1] ... loopTask\n");
    // vTaskDelay(10000 / portTICK_PERIOD_MS);
    vTaskSuspend(NULL);
}