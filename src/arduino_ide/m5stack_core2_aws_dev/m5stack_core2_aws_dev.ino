/**
 * @file m5stick_c_plus_dev.ino
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief M5Stack Core2 AWS 評価プログラム Arduino IDEファイル
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <M5Core2.h>
#include <Adafruit_NeoPixel.h>

#define PIN 25
#define NUMPIXELS 10
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
static void rgbled_test(void);
static void do_vibration(void);

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
        }
        else if ((it % 3) == 1) {
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

void setup()
{
    // pixels.begin();
    M5.begin();

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.println("Touch Button(A/B/C) Test");
    M5.Lcd.setTextColor(RED);
}

void loop()
{
    M5.update();
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
        M5.Lcd.print('A');
    } else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 200)) {
        M5.Lcd.print('B');
    } else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 200)) {
        M5.Lcd.print('C');
    } else if (M5.BtnB.wasReleasefor(700)) {
        M5.Lcd.clear(BLACK);
        M5.Lcd.setCursor(0, 0);
    }
}