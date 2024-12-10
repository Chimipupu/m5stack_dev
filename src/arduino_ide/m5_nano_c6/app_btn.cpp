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

/**
 * @brief ボタンポーリング処理
 * 
 */
void app_btn_polling(void)
{
    // TODO:ボタンのポーリング
    if (NanoC6.BtnA.wasPressed()) {
        // 処理を記入
    }

    if (NanoC6.BtnA.wasReleased()) {
        // 処理を記入
    }
}

/**
 * @brief ボタン初期化
 * 
 */
void app_btn_init(void)
{
    pinMode(BTN_PIN, INPUT_PULLUP);
}