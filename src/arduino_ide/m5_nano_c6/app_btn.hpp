/**
 * @file app_btn.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief ボタン アプリ処理
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef APP_BTN_HPP
#define APP_BTN_HPP

#include "common.hpp"

#define BTN_PIN    9

void app_btn_init(void);
void app_btn_polling(void);

#endif /* APP_BTN_HPP */