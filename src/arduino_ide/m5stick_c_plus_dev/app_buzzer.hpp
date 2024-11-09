/**
 * @file app_buzzer.hpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief ブザーのアプリ用ヘッダー
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef APP_BUZZER_HPP
#define MCU_BOARD_HPP

#include <stdint.h>

// GPIO
#define BUZZER_PIN      2   // Buzzer  @GPIO 2
#define IRLED_PIN       9   // IR LED  @GPIO 9
#define LED_PIN        10   // 赤LED   @GPIO 10
#define BUTTON_A_PIN   37   // ButtonA @GPIO 37
#define BUTTON_B_PIN   39   // ButtonB @GPIO 39

// 音階の周波数（C4 = 261 Hz から始まるオクターブ）
#define NOTE_C4  261
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  329
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  493

#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  987

#define NOTE_C6  1046
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976

#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951

void app_buzzer_tone(uint8_t pin, uint32_t melody, uint32_t duration);
void app_play_melody(uint8_t pin, const uint32_t *p_melody, uint8_t numNotes);
void app_buzzer_test(void);

#endif /* MCU_BOARD_HPP */