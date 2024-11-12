/**
 * @file app_filesystem.hpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief File System(SD/SPIFS/FATFS) アプリ 実装
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "app_filesystem.hpp"
#include <M5Core2.h>
// #include <SD.h>

const char *p_test_write_txt = "sd write test";
constexpr char text_file_path[] = "/txt/plain/test.txt";
constexpr char wifi_config_file_path[] = "/sys/wifi_config.txt";

static void fs_init(void);
static void fs_test(void);
static void fs_wifi_config_read(char *p_ssid, char *p_password);

static void fs_init(void)
{
    if (!SD.begin())
    {
        M5.Lcd.println("No SD Card. Plz, Insert SD & Reboot");
        DEBUG_PRINTF_RTOS("No SD Card. Plz, Insert SD & Reboot");
        while (1)
        ;
    }

    M5.Lcd.println("File System Init(@SD)");
    DEBUG_PRINTF_RTOS("File System Init(@SD)\n");
}

static void fs_test(void)
{
    M5.Lcd.println("SD card Test");

    if (SD.exists(text_file_path)) {
        M5.Lcd.println("test.txt exists.");
    } else {
        M5.Lcd.println("test.txt doesn't exist.");
        M5.Lcd.println("Creating test.txt");
    }

    File myFile = SD.open(text_file_path, FILE_WRITE);

    if (myFile) {
        M5.Lcd.println("Writing to test.txt...");
        myFile.println("SD test.");
        myFile.close();
        M5.Lcd.println("done.");
    } else {
        M5.Lcd.println("error opening test.txt");
    }
    delay(500);
    myFile = SD.open(text_file_path, FILE_READ);
    if (myFile) {
        M5.Lcd.println("/test.txt Content:");
        while (myFile.available()) {
            M5.Lcd.write(myFile.read());
        }
        myFile.close();
    } else {
        M5.Lcd.println("error opening /test.txt");
    }
}

static void fs_wifi_config_read(char *p_ssid, char *p_password)
{
    M5.Lcd.println("WiFi Config File Read(@SD)");

    if (SD.exists(wifi_config_file_path)) {
        M5.Lcd.println("wifi_config.txt exists.");
    } else {
        M5.Lcd.println("wifi_config.txt doesn't exist.");
        return;
    }

    File myFile = SD.open(wifi_config_file_path, FILE_READ);
    if (myFile) {
        M5.Lcd.printf("SSID:");

        String ssid = myFile.readStringUntil('\n');
        ssid.trim();
        ssid.toCharArray(p_ssid, ssid.length() + 1);
        M5.Lcd.printf("%s\n", p_ssid);

        M5.Lcd.printf("Password:");

        String password = myFile.readStringUntil('\n');
        ssid.trim();
        password.toCharArray(p_password, password.length() + 1);
        M5.Lcd.printf("%s\n", p_password);

        myFile.close();
    } else {
        M5.Lcd.println("error opening wifi_config.txt");
    }
}

void app_fs_init(void)
{
    fs_init();
    // fs_test();
}

void app_fs_wifi_config_read(char *p_ssid, char *p_password)
{
    fs_wifi_config_read(p_ssid, p_password);
}