# M5Stack評価F/W開発
M5StackのF/W個人開発リポジトリ👩‍💻

## 対象
- ✅M5Stick C Plus

### 実装状況
**凡例(✅テスト完了、🆗実装済み、🚩TODO、❌TBD)**

- ✅M5Stick C Plus
  - 📍OS
    - 📍FreeRTOS
      - ✅CPU @Core0
      - ✅CPU @Core1
  - 📍WiFi🛜
    - 🚩STA
    - 🚩AP
  - 📍Bluetooth🛜
    - 🚩SSP
    - 🚩A2DP
  - 🚩LCD (@I2C)
    - ✅LovyanGFX
  - 🚩IMU (@I2C)
  - 🚩マイク (@I2S)
  - 🚩ブザー (@GPIO2)
  - 🚩PMIC (@I2C)
  - 🚩IR (@GPIO9)
  - 🚩RGBLED (@GPI10)
  - 📍ボタン
    - 🚩ボタンA (@GPIO37)
    - 🚩ボタンB (@GPIO39)