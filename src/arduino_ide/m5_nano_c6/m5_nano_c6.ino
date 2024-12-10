/**
 * @file m5_nano_c6.ino
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief M5Stack NanoC6 評価プログラム Arduino IDEファイル
 * @version 0.1
 * @date 2024-12-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "common.hpp"
#include "app_main.hpp"

void setup(void)
{
    app_main_init();
}

void loop()
{
    app_main();
}