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
#include "common.hpp"
#include "app_main_core0.hpp"
#include "app_main_core1.hpp"

void setup(void)
{
    app_main_init_core1();
}

void loop()
{
    app_main_core1();
}