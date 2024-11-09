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
    lcd.init();

    // 文字
    lcd.setRotation(ROTATION_D);
    lcd.fillScreen(TFT_BLACK);
    lcd.setCursor(0, 10);
    lcd.setTextColor(TFT_WHITE);
    lcd.setTextSize(1);
    lcd.printf("Display Test!");
    delay(500);

    // スクリーン
    lcd.fillScreen(TFT_WHITE);
    delay(500);
    lcd.fillScreen(TFT_RED);
    delay(500);
    lcd.fillScreen(TFT_GREEN);
    delay(500);
    lcd.fillScreen(TFT_BLUE);
    delay(500);
    lcd.fillScreen(TFT_BLACK);
    delay(500);

    // スプライト
    lcd.drawRect(15, 55, 50, 50, TFT_BLUE);
    delay(500);
    lcd.fillRect(15, 55, 50, 50, TFT_BLUE);
    delay(500);
    lcd.drawCircle(40, 80, 30, TFT_RED);
    delay(500);
    lcd.fillCircle(40, 80, 30, TFT_RED);
    delay(500);
}

// 画面にランダムなスプライトを描画
static void lcd_test(void)
{
#if 1
    lcd.fillTriangle(random(lcd.width() - 1), random(lcd.height() - 1),
                        random(lcd.width() - 1), random(lcd.height() - 1),
                        random(lcd.width() - 1), random(lcd.height() - 1),
                        random(0xfffe));
#endif
}

void m5scp_lcd_init(void)
{
    lcd_test_init();
}

void m5scp_lcd_main(void)
{
    lcd_test();
}