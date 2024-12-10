/**
 * @file app_neopixel.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief NeoPixelアプリ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef APP_NEOPIXEL_HPP
#define APP_NEOPIXEL_HPP

#include "common.hpp"
#include <Adafruit_NeoPixel.h>

#define RGBLED_PWR_PIN       19 // M5NanoC6のNeoPixelの電源ピン
#define RGBLED_PIN           20 // M5NanoC6のNeoPixelの信号ピン
#define NUMPIXELS            1

typedef struct {
    uint8_t red;        // 赤色の輝度 (0-255)
    uint8_t green;      // 緑色の輝度 (0-255)
    uint8_t blue;       // 青色の輝度 (0-255)
    uint8_t brightness; // LEDの明るさ (0-255)
    bool onoff;         // LEDがオンかオフか
    bool autoled;       // 自動制御のフラグ
} rgbled_state_t;

void app_neopixel_init(void);
void app_neopixel_main(uint8_t red,uint8_t green, uint8_t blue, uint8_t brightness, bool onoff, bool autoled);

#endif /* APP_NEOPIXEL_HPP */