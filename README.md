# M5Stick C Plus 開発
M5Stick C PlusのF/W開発ブランチ👩‍💻

## 対象
- ✅M5Stick C Plus

### 実装状況
**凡例(✅テスト完了、🆗実装済み、🚩TODO、❌TBD)**

- 📢外部モジュール
    - 🚩アンプ＆スピーカー（PAM8303）📢
- ✅M5Stick C Plus
  - 📍OS
    - 📍FreeRTOS
      - ✅CPU @Core0
        - ✅CPU Core0 メインタスク
      - ✅CPU @Core1
        - ✅CPU Core1 メインタスク
        - ✅UARTタスク
        - ✅ブザータスク📢
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
  - ✅ブザー (@GPIO2)📢
  - 🚩PMIC (@I2C)
  - 🚩IR (@GPIO9)
  - ✅LED (@GPI10)
  - 📍ボタン
    - ✅ボタンA (@GPIO37)
    - ✅ボタンB (@GPIO39)