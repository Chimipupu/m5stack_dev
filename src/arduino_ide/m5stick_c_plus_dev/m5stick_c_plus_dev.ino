/**
 * @file m5stick_c_plus_dev.ino
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief M5Stick C Plus 評価プログラム Arduino IDEファイル
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "common.hpp"
#include "m5scp_lcd.hpp"

SemaphoreHandle_t g_serial_mux;
portMUX_TYPE g_port_mux = portMUX_INITIALIZER_UNLOCKED;
static xTaskHandle s_xTaskCore1Main;

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
    digitalWrite(IRLED_PIN, s_ir_led_val);
    s_ir_led_val != s_ir_led_val;
}

void vTaskCore1Main(void *p_parameter)
{
    DEBUG_PRINTF_RTOS("[Core1] ... vTaskCore1Main\n");
    m5scp_lcd_init();

    while (1)
    {
        // TODO:Core0メインタスク処理
        m5scp_lcd_main();
        digitalWrite(LED_PIN, s_led_val);
        s_led_val != s_led_val;
        vTaskDelay(8 / portTICK_PERIOD_MS);
    }
}

void app_main_init_core1(void)
{
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
                            NULL,              // ハンドル
                            CPU_CORE_1);       // Core0 or Core1
}

void setup()
{
    app_main_init_core1();
}

void loop()
{
    // loopタスクは不要なのでSuspend
    vTaskSuspend(NULL);
}