/**
 * @file app_btn.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief ボタン アプリ処理
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <M5NanoC6.h>
#include "app_btn.hpp"
#include "app_neopixel.hpp"

static uint32_t hold_time_buf[] = { BTN_HOLD_3000_MS,
                                    BTN_HOLD_2000_MS,
                                    BTN_HOLD_1000_MS
                                    };
static void btn_hold_check(void);

/**
 * @brief ボタン長押しチェック
 * 
 */
static void btn_hold_check(void)
{
    bool res = false;
    size_t buf_size = sizeof(hold_time_buf) / sizeof(hold_time_buf[0]);
    uint32_t hold_time_ms = 0;

    for (size_t i = 0; i < buf_size; i++)
    {
        hold_time_ms = hold_time_buf[i];
        res = NanoC6.BtnA.pressedFor(hold_time_ms);
        if (res) {
            if (hold_time_ms == BTN_HOLD_3000_MS) {
                DEBUG_PRINTF_RTOS("[BTN] ... Button 3000msec以上 ON\n");
            } else {
                DEBUG_PRINTF_RTOS("[BTN] ... Button %dmsec ON\n", hold_time_ms);
            }
            app_neopixel_main(16, 16, 16, 0, true, false); // white
            return;
        }
    }
}

/**
 * @brief ボタンポーリング処理
 * 
 */
void app_btn_polling(void)
{
    // 押してるか
    if (NanoC6.BtnA.wasPressed()) {
        DEBUG_PRINTF_RTOS("[BTN] ... Button Press\n");
        app_neopixel_main(0, 16, 0, 0, true, false); // green
    }

    // 離したか
    if (NanoC6.BtnA.wasReleased()) {
        DEBUG_PRINTF_RTOS("[BTN] ... Button Release\n");
        app_neopixel_main(16, 0, 0, 0, true, false); // red
    }

    // 長押し
    btn_hold_check();
}

/**
 * @brief ボタン初期化
 * 
 */
void app_btn_init(void)
{
    pinMode(BTN_PIN, INPUT_PULLUP);
}