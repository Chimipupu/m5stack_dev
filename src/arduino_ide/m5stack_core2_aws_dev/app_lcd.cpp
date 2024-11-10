/**
 * @file app_lcd.hpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief LCDアプリ ソース
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "app_lcd.hpp"

LGFX lcd;
static LGFX_Sprite sprite(&lcd);

static void lcd_clear(void);
static void lcd_test_init(void);
static void lcd_test(void);
static void rtc_lcd_show(void);

static void lcd_clear(void)
{
    sprite.fillScreen(TFT_BLACK);
    sprite.setTextColor(TFT_GREEN);
    sprite.setCursor(0, 0);
    sprite.pushSprite(0, 0);
}

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
    delay(200);

    // スクリーン
    lcd.fillScreen(TFT_WHITE);
    delay(200);
    lcd.fillScreen(TFT_RED);
    delay(200);
    lcd.fillScreen(TFT_GREEN);
    delay(200);
    lcd.fillScreen(TFT_BLUE);
    delay(200);
    lcd.fillScreen(TFT_BLACK);
    delay(200);

    // スプライト
    lcd.drawRect(15, 55, 50, 50, TFT_BLUE);
    delay(200);
    lcd.fillRect(15, 55, 50, 50, TFT_BLUE);
    delay(200);
    lcd.drawCircle(40, 80, 30, TFT_RED);
    delay(200);
    lcd.fillCircle(40, 80, 30, TFT_RED);
    delay(200);
}

static void rtc_lcd_show(void)
{
    lcd.fillScreen(TFT_BLACK);
    lcd.setCursor(0, 0);
    lcd.setTextColor(TFT_WHITE);
    lcd.printf("Data:%s\n", g_rtc_date_buf);
    lcd.printf("Time:%s\n", g_rtc_time_buf);
}

// 画面にランダムなスプライトを描画
static void lcd_test(void)
{
    lcd.fillTriangle(random(lcd.width() - 1), random(lcd.height() - 1),
                        random(lcd.width() - 1), random(lcd.height() - 1),
                        random(lcd.width() - 1), random(lcd.height() - 1),
                        random(0xfffe));
}

void app_lcd_init(void)
{
    lcd.init();
    lcd.setRotation(ROTATION_A);
    sprite.setColorDepth(16);
    sprite.setTextWrap(false);
    sprite.setTextSize(1);
    sprite.createSprite(lcd.width(), lcd.height());
}

void app_lcd_test(void)
{
    for(uint8_t i = 0; i < 100; i++) {
        lcd_test();
    }

    lcd_test_init();
    lcd_clear();

    // lcd.setCursor(0, 10);
    // // sprite.setFont(&fonts::lgfxJapanGothic_8);
    // sprite.setFont(&fonts::efontJA_12);
    // sprite.setTextColor(TFT_WHITE);
    // sprite.setTextSize(1);
    // sprite.printf("ちみの新しいおもちゃ\n");
    // sprite.printf("M5Stack Core2 AWS\n");
    // sprite.printf("WiFiもBluetoothも!\n");
    // sprite.printf("CPUも2つも乗ってる!\n");
    // sprite.printf("電子工作おもろい！\n");
    // sprite.pushSprite(0, 0);
}

void app_lcd_main(void)
{
    rtc_lcd_show();
}