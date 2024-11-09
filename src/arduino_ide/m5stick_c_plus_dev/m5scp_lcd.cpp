/**
 * @file m5scp_lcd.hpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief M5Stick C PlusのLCDアプリソース
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "m5scp_lcd.hpp"

static void lcd_test_init(void);
static void lcd_test(void);

LGFX lcd;

// 初期化時の画面正常チェック
static void lcd_test_init(void)
{
    // 文字
    lcd.setRotation(ROTATION_D);
    lcd.fillScreen(TFT_BLACK);
    lcd.setCursor(0, 10);
    lcd.setTextColor(TFT_GREEN);
    lcd.setTextSize(3);
    lcd.printf("Init Display Test");
    delay(100);

    // スクリーン
    lcd.fillScreen(TFT_WHITE);
    delay(100);
    lcd.fillScreen(TFT_RED);
    delay(100);
    lcd.fillScreen(TFT_GREEN);
    delay(100);
    lcd.fillScreen(TFT_BLUE);
    delay(100);
    lcd.fillScreen(TFT_BLACK);
    delay(100);

    // スプライト
    lcd.drawRect(15, 55, 50, 50, TFT_BLUE);
    delay(100);
    lcd.fillRect(15, 55, 50, 50, TFT_BLUE);
    delay(100);
    lcd.drawCircle(40, 80, 30, TFT_RED);
    delay(100);
    lcd.fillCircle(40, 80, 30, TFT_RED);
    delay(100);
}

// 画面にランダムなスプライトを描画
static void lcd_test(void)
{
    lcd.fillTriangle(random(lcd.width() - 1), random(lcd.height() - 1),
                        random(lcd.width() - 1), random(lcd.height() - 1),
                        random(lcd.width() - 1), random(lcd.height() - 1),
                        random(0xfffe));
}

void m5scp_lcd_init(void)
{
    lcd.init();
    lcd_test_init();
}

void m5scp_lcd_main(void)
{
    lcd_test();
}