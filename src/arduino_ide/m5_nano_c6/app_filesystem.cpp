/**
 * @file app_filesystem.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief File System(SD/SPIFS/FATFS) アプリ 実装
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "app_filesystem.hpp"
#include <SD.h>

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
        DEBUG_PRINTF_RTOS("No SD Card. Plz, Insert SD & Reboot");
    }

    DEBUG_PRINTF_RTOS("File System Init(@SD)\n");
}

static void fs_test(void)
{
    DEBUG_PRINTF_RTOS("SD card Test\n");

    if (SD.exists(text_file_path)) {
        DEBUG_PRINTF_RTOS("test.txt exists\n");
    } else {
        DEBUG_PRINTF_RTOS("test.txt doesn't exist\n");
        DEBUG_PRINTF_RTOS("Creating test.txt\n");
    }

    File myFile = SD.open(text_file_path, FILE_WRITE);

    if (myFile) {
        DEBUG_PRINTF_RTOS("Writing to test.txt...\n");
        myFile.println("SD test.");
        myFile.close();
        DEBUG_PRINTF_RTOS("done.");
    } else {
        DEBUG_PRINTF_RTOS("error opening test.txt\n");
    }
    delay(500);
    myFile = SD.open(text_file_path, FILE_READ);
    if (myFile) {
        DEBUG_PRINTF_RTOS("/test.txt Content:");
        while (myFile.available()) {
            DEBUG_PRINTF_RTOS("%c", myFile.read());
        }
        myFile.close();
    } else {
        DEBUG_PRINTF_RTOS("error opening /test.txt\n");
    }
}

static void fs_wifi_config_read(char *p_ssid, char *p_password)
{
    DEBUG_PRINTF_RTOS("WiFi Config File Read(@SD)\n");

    if (SD.exists(wifi_config_file_path)) {
        DEBUG_PRINTF_RTOS("wifi_config.txt exists.\n");
    } else {
        DEBUG_PRINTF_RTOS("wifi_config.txt doesn't exist.\n");
        return;
    }

    File myFile = SD.open(wifi_config_file_path, FILE_READ);
    if (myFile) {
        DEBUG_PRINTF_RTOS("SSID:");

        String ssid = myFile.readStringUntil('\n');
        ssid.trim();
        ssid.toCharArray(p_ssid, ssid.length() + 1);
        DEBUG_PRINTF_RTOS("%s\n", p_ssid);

        DEBUG_PRINTF_RTOS("Password:");

        String password = myFile.readStringUntil('\n');
        ssid.trim();
        password.toCharArray(p_password, password.length() + 1);
        DEBUG_PRINTF_RTOS("%s\n", p_password);

        myFile.close();
    } else {
        DEBUG_PRINTF_RTOS("error opening wifi_config.txt\n");
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