/**
 * @file app_filesystem.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief File System(SD/SPIFS/FATFS)ヘッダ
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef APP_FILESYSTEM_HPP
#define APP_FILESYSTEM_HPP

#include "common.hpp"

void app_fs_init(void);
void app_fs_wifi_config_read(char *p_ssid, char *p_password);

#endif /* APP_FILESYSTEM_HPP */