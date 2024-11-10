/**
 * @file app_lcd.hpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief LCDヘッダー
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef APP_LCD_HPP
#define APP_LCD_HPP

#include "common.hpp"

#define LGFX_AUTODETECT
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <LGFX_AUTODETECT.hpp>

// USBが左基準
typedef enum
{
    ROTATION_A = 0, // TBD基準
    ROTATION_B,     // TBD基準
    ROTATION_C,     // 右下基準
    ROTATION_D,     // 左上基準
}E_LCD_ROTATION;

extern char g_rtc_date_buf[];
extern char g_rtc_time_buf[];

void app_lcd_init(void);
void app_lcd_test(void);
void app_lcd_main(void);

#endif /* APP_LCD_HPP */