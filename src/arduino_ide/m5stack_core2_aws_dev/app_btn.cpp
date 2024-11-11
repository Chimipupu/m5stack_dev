/**
 * @file app_btn.cpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief ボタン アプリ処理
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "app_btn.hpp"
#include <M5Core2.h>

/**
 * @brief ボタンポーリング処理
 * 
 */
void app_btn_polling(void)
{
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
        // TODO:ボタンAの処理
        NOP;
    } else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 200)) {
        // TODO:ボタンBの処理
        NOP;
    } else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 200)) {
        // TODO:ボタンCの処理
        NOP;
    } else if (M5.BtnB.wasReleasefor(700)) {
        M5.Lcd.clear(BLACK);
        M5.Lcd.setCursor(0, 0);
    }
}

/**
 * @brief ボタン初期化
 * 
 */
void app_btn_init(void)
{
    // TODO:仮想タッチボタン追加
    NOP;
}