/**
 * @file m5scp_lcd.hpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief M5Stick C PlusのLCDヘッダー
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef M5SCP_LCD_HPP
#define M5SCP_LCD_HPP

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

void m5scp_lcd_init(void);
void m5scp_lcd_test(void);
void m5scp_lcd_main(void);

#endif /* M5SCP_LCD_HPP */