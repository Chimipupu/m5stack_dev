/**
 * @file common.hpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief 共通ヘッダー
 * @version 0.1
 * @date 2024-10-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef COMMON_HPP
#define COMMON_HPP

// C,C++ Lib
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <Arduino.h>

// FreeRTOS
// #include <FreeRTOS.h>
// #include <task.h>
// #include <semphr.h>


// 割込みマスク・許可
#define __DI            portENTER_CRITICAL
#define __EI            portEXIT_CRITICAL
#define __DI_ISR        portENTER_CRITICAL_ISR
#define __EI_ISR        portEXIT_CRITICAL_ISR

extern portMUX_TYPE g_port_mux;
extern SemaphoreHandle_t g_serial_mux;

#define CPU_CORE_0      0
#define CPU_CORE_1      1

// #define ATOM_S3
#define ATOM_S3_LITE
// #define YD_ESP_S3

#ifndef APP_CORE
// #define APP_CORE        CPU_CORE_0
#define APP_CORE        CPU_CORE_1

#if APPLE_CORE == CPU_CORE_0
#define core0_init    setup
#define core0_main    loop
#else
#define core1_init    setup
#define core1_main    loop
#endif

#define CPU_CORE_0      0
#define CPU_CORE_1      1

// #define APP_CORE        CPU_CORE_0
#define APP_CORE        CPU_CORE_1

#if APP_CORE == CPU_CORE_0
    #define core0_init    setup
    #define core0_main    loop
#else
    #define core1_init    setup
    #define core1_main    loop
#endif
#endif

#define DEBUG_PRINTF_RTOS   safeSerialPrintf
#ifdef DEBUG_PRINTF_RTOS
extern "C"
{
#ifdef NOP
#undef NOP
    static inline void NOP(void)
    {
        asm volatile("nop");
    }
#endif

    static inline void safeSerialPrintf(const char *format, ...)
    {
        if (xSemaphoreTake(g_serial_mux, portMAX_DELAY) == pdTRUE) {
            __DI(&g_port_mux);
            va_list args;
            va_start(args, format);

            for (const char *p = format; *p != '\0'; p++) {
                if (*p == '%') {
                    p++;  // '%'の次の文字を見る
                    int width = 0;
                    int precision = -1;

                    // 幅の取得
                    while (*p >= '0' && *p <= '9') {
                        width = width * 10 + (*p - '0');
                        p++;
                    }

                    // 精度の取得
                    if (*p == '.') {
                        p++;
                        precision = 0;
                        while (*p >= '0' && *p <= '9') {
                            precision = precision * 10 + (*p - '0');
                            p++;
                        }
                    }

                    // フォーマット指定子に基づいて処理
                    switch (*p) {
                        case 'd':  // 整数
                            Serial.print(va_arg(args, int));
                            break;
                        case 'f':  // 浮動小数点数（float）
                        case 'l':  // 'l' は無視
                        case 'F':  // 浮動小数点数（float、大文字）
                            Serial.print(va_arg(args, double), (precision >= 0) ? precision : 2);
                            break;
                        case 's':  // 文字列
                            Serial.print(va_arg(args, char*));
                            break;
                        case 'c':  // 文字
                            Serial.print((char)va_arg(args, int));
                            break;
                        case 'x':  // 16進数（小文字）
                        case 'X':  // 16進数（大文字）
                            Serial.print(va_arg(args, int), HEX);
                            break;
                        default:  // 他のフォーマット指定子はそのまま表示
                            Serial.print(*p);
                            break;
                    }
                } else if (*p == '\r' || *p == '\n') {
                    // 改行シーケンスの処理
                    Serial.println(); // 改行
                } else {
                    // '%'でない文字はそのまま表示
                    Serial.print(*p);
                }
            }
            va_end(args);
            __EI(&g_port_mux);
            xSemaphoreGive(g_serial_mux);
        } else {
            Serial.println("Failed to acquire mutex!");
        }
    }
}
#endif /* DEBUG_PRINTF_RTOS */

#endif /* COMMON_HPP */