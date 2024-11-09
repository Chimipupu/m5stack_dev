
/**
 * @file app_buzzer.cpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief ブザーのアプリ
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "common.hpp"
#include "app_buzzer.hpp"

// きらきら星
volatile const uint32_t melody_star[][2] = {
    {NOTE_C4, 4}, {NOTE_C4, 4}, {NOTE_G4, 4}, {NOTE_G4, 4},
    {NOTE_A4, 4}, {NOTE_A4, 4}, {NOTE_G4, 2},
    {NOTE_F4, 4}, {NOTE_F4, 4}, {NOTE_E4, 4}, {NOTE_E4, 4},
    {NOTE_D4, 4}, {NOTE_D4, 4}, {NOTE_C4, 2}
};

volatile const uint32_t numNotes_star = sizeof(melody_star) / sizeof(melody_star[0]);

void app_buzzer_tone(uint8_t pin, uint32_t melody, uint32_t duration)
{
    tone(pin, melody, duration);
    noTone(pin);
}

void app_play_melody(uint8_t pin, const uint32_t *p_melody, uint8_t numNotes)
{
    for (uint8_t i = 0; i < numNotes; i++)
    {
        uint32_t note = p_melody[i * 2];                // 音階を取得
        uint32_t duration = 1000 / p_melody[i * 2 + 1]; // 音符の長さを計算
        tone(pin, note, duration);
        delay(duration * 1.3);                          // 音と音の間隔を調整
        noTone(pin);                                    // 次の音の前に停止
    }
}

void app_buzzer_test(void)
{
    // きらきら星 演奏
    app_play_melody(BUZZER_PIN, (const uint32_t *)melody_star, numNotes_star);
}