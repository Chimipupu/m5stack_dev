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
#include <LovyanGFX.hpp>
#include <LGFX_AUTODETECT.hpp>

// USBが左基準
typedef enum
{
    ROTATION_A = 0, // 右下基準
    ROTATION_B,     // TBD基準
    ROTATION_C,     // TBD基準
    ROTATION_D,     // TBD基準
};

void m5scp_lcd_init(void);
void m5scp_lcd_main(void);

#endif /* M5SCP_LCD_HPP */