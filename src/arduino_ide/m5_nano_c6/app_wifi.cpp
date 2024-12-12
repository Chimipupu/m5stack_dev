/**
 * @file app_wifi.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief WiFiアプリ
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <M5NanoC6.h>
#include "app_wifi.hpp"
#include "app_neopixel.hpp"
#include "app_filesystem.hpp"

WebServer server(80);

// ファイルシステム
const char *p_ap_wifi_str = "/wifi_config.json";

// 初期APのWiFi設定
const char *p_ap_ssid_str = "ESP32 Dev AP";
const char *p_ap_password_str = "esp32dev";

// NTP
const char *ntpServer = "ntp.nict.jp";
const long gmtOffset_sec = 9 * 3600; // 日本時間 (UTC+9)
const int daylightOffset_sec = 0;

char g_ssid[16] = {0};
char g_password[32] = {0};

typedef enum {
    INDEX = 0,
    FACTOCY_CONFIG = 0x20,
    STA_WIFI_CONFIG = 0xFF
} e_html_type;

static e_html_type s_html_type = STA_WIFI_CONFIG;
static rgbled_state_t s_rgbled_state;
static tm s_ntp_timeinfo_t;
static tm s_rtc_timeinfo_t;
static bool s_wifi_flag = false;
static bool s_ap_flg = false;
static bool s_ftp_flg = false;

static bool load_wifi_config(void);
static void saveWiFiConfig(const String &ssid, const String &password);
static void setupAP(void);
static void handleRoot(void);
static void handleSave(void);
static void time_show(uint8_t type);
static void set_ntp_to_rtc_time(void);
static void wifi_online_proc(void);
static void wifi_off_online_proc(void);
static void ap_mode_main(void);
static void sta_mode_main(void);

static bool load_wifi_config(void)
{
    memset(&g_ssid[0], 0x00, sizeof(g_ssid));
    memset(&g_password[0], 0x00, sizeof(g_password));

    app_fs_wifi_config_read(&g_ssid[0], &g_password[0]);

    DEBUG_PRINTF_RTOS("WiFi設定を読み込みました\n");
    return true;
}

static void setupAP(void)
{
    WiFi.mode(WIFI_AP);
    DEBUG_PRINTF_RTOS("APモードを開始します\n");
    WiFi.softAP(p_ap_ssid_str, p_ap_password_str);

    DEBUG_PRINTF_RTOS("AP SSID : %s\n", p_ap_ssid_str);
    DEBUG_PRINTF_RTOS("AP Password : %s\n", p_ap_password_str);

    DEBUG_PRINTF_RTOS("AP Web Server IP addr : %s\n", WiFi.softAPIP().toString().c_str());
    String str = WiFi.macAddress();
    DEBUG_PRINTF_RTOS("WiFi MAC addr : %s\n", str.c_str());
}

static void time_show(uint8_t type)
{
    switch (type)
    {
        case NTP_TIME:
            getLocalTime(&s_ntp_timeinfo_t);
            DEBUG_PRINTF_RTOS("NTP:%04d/%02d/%02d %02d:%02d:%02d\n",
                            s_ntp_timeinfo_t.tm_year + 1900,
                            s_ntp_timeinfo_t.tm_mon + 1,
                            s_ntp_timeinfo_t.tm_mday,
                            s_ntp_timeinfo_t.tm_hour,
                            s_ntp_timeinfo_t.tm_min,
                            s_ntp_timeinfo_t.tm_sec);
            break;

        case RTC_TIME:
            getLocalTime(&s_rtc_timeinfo_t);
            DEBUG_PRINTF_RTOS("RTC:%04d/%02d/%02d %02d:%02d:%02d\n",
                            s_rtc_timeinfo_t.tm_year + 1900,
                            s_rtc_timeinfo_t.tm_mon + 1,
                            s_rtc_timeinfo_t.tm_mday,
                            s_rtc_timeinfo_t.tm_hour,
                            s_rtc_timeinfo_t.tm_min,
                            s_rtc_timeinfo_t.tm_sec);
            break;

        default:
            break;
    }
}

static void set_ntp_to_rtc_time(void)
{
    char timeStr[100], rtcStr[100];

    DEBUG_PRINTF_RTOS("Sync RTC & NTP\n");

    __DI(&g_port_mux);
    strftime(timeStr, sizeof(timeStr), "NTP: %Y/%m/%d %H:%M:%S", &s_ntp_timeinfo_t);
    time_t now;
    time(&now);
    struct timeval tv = {.tv_sec = now, .tv_usec = 0};
    settimeofday(&tv, NULL);
    __EI(&g_port_mux);

    DEBUG_PRINTF_RTOS("NTPとRTCを同期完了\n");
    time_show(NTP_TIME);
    time_show(RTC_TIME);
}

static void wifi_online_proc(void)
{
    if(s_ftp_flg != false)
    {
        app_neopixel_main(0, 0, 16, 0,true, false); // blue, on
        // app_ftp_main();
    } else {
        app_neopixel_main(0, 16, 0, 0,true, false); // green, on
    }
}

static void wifi_off_online_proc(void)
{
    if(s_ap_flg != false){
        app_neopixel_main(0, 0, 16, 0,true, false); // blue, on
    }else{
        app_neopixel_main(16, 0, 0, 0, true, false); // red, on
    }
}

static void sta_mode_main(void)
{
    DEBUG_PRINTF_RTOS("STAモードで接続を試みます\n");
    WiFi.mode(WIFI_STA);
    DEBUG_PRINTF_RTOS("STA SSID : %s\n",g_ssid);
    DEBUG_PRINTF_RTOS("STA Password : %s\n", g_password);
    WiFi.begin(g_ssid, g_password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30)
    {
        delay(500);
        DEBUG_PRINTF_RTOS(".");
        attempts++;
    }

    DEBUG_PRINTF_RTOS("\n");

    if (WiFi.status() == WL_CONNECTED)
    {
        s_wifi_flag = true;
        app_neopixel_main(0, 16, 0, 0,true, false); // green, on

        DEBUG_PRINTF_RTOS("Wifi connected!\n");
        DEBUG_PRINTF_RTOS("IP addr : %s\n", WiFi.localIP().toString().c_str());
        String str = WiFi.macAddress();
        DEBUG_PRINTF_RTOS("MAC addr : %s\n", str.c_str());

        DEBUG_PRINTF_RTOS("NTP Server connect\n");
        // __DI(&g_port_mux);
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        // __EI(&g_port_mux);

        set_ntp_to_rtc_time();

        // WEB Server
        // s_html_type = INDEX;
        // server.on("/", handleRoot);
        // server.begin();
        // server.handleClient();

#ifdef YD_ESP_S3
        // FTP Server
        app_ftp_init();
        s_ftp_flg = true;
#else
        DEBUG_PRINTF_RTOS("WiFi Disconnect!\n");
        WiFi.disconnect();
        s_wifi_flag = false;
#endif /* YD_ESP_S3 */
    } else {
        s_wifi_flag = true;
        ap_mode_main();
    }
}

static void ap_mode_main(void)
{
    setupAP();
    s_ap_flg = true;
    app_neopixel_main(0, 0, 16, 0,true, false); // blue, on

#if 0
    DEBUG_PRINTF_RTOS("uAP Web Server begin...\n");
    s_html_type = STA_WIFI_CONFIG;
    server.on("/", handleRoot);
    server.on("/save", HTTP_POST, handleSave);
    server.begin();
    server.handleClient();
#endif
}

void app_wifi_scan(void)
{
    DEBUG_PRINTF_RTOS("WiFi scan...\n");
    uint8_t network_cnt = WiFi.scanNetworks();

    if (network_cnt == 0) {
        DEBUG_PRINTF_RTOS("no WiFi network\n");
    } else {
        DEBUG_PRINTF_RTOS("found %d WiFi network\n", network_cnt);
        for (uint8_t i = 0; i < network_cnt; ++i) {
            DEBUG_PRINTF_RTOS("[WiFi Network No.%d]\n", i);
            String ssid = WiFi.SSID(i);
            DEBUG_PRINTF_RTOS("[SSID:%s] [RSSI:%d dBm] [Ch:%d]\n", ssid.c_str(), WiFi.RSSI(i), WiFi.channel(i));
        }
    }

    DEBUG_PRINTF_RTOS("");
}

/**
 * @brief WiFi アプリ初期化
 * 
 */
void app_wifi_init(void)
{
    // DEBUG_PRINTF_RTOS("WiFiをスキャン中...\n");
    // app_wifi_scan();

    DEBUG_PRINTF_RTOS("WiFi Config File Reading...\n");
    size_t  wifi_config_str = strlen(g_ssid);

    if (load_wifi_config() && (wifi_config_str > 0))
    {
        sta_mode_main();
    } else {
        s_wifi_flag = true;
        ap_mode_main();
    }
}

/**
 * @brief WiFi アプリメイン
 * 
 * @return true WiFiオンライン
 * @return false WiFiオフライン
 */
bool app_wifi_main(void)
{
    if ((s_wifi_flag != true) || (WiFi.status() != WL_CONNECTED))
    {
        wifi_off_online_proc();
    } else {
        wifi_online_proc();
    }

    server.handleClient();

    return s_wifi_flag;
}