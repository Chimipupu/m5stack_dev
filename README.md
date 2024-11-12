# MM5Stack Core2評価F/W開発
M5Stack Core2のF/W開発ブランチ👩‍💻

## 対象
- ✅M5Stack Core2 AWS

## 実装状況
**凡例(✅実装済み、🆗ライブラリAPI、🚩TODO、❌TBD)**

- 📢外部モジュール
    - 🚩アンプ＆スピーカー（PAM8303）📢
- ✅M5Stack Core2 AWS
  - 📍OS
    - 📍FreeRTOS
      - ✅CPU @Core0
        - ✅CPU Core0 メインタスク
      - ✅CPU @Core1
        - ✅CPU Core1 メインタスク
          - ✅SDカードのR/W
          - ✅WiFiにSTAで接続
          - ✅タッチボタン(A/B/C)のポーリング
          - ✅LCDのアプリ処理
  - 📍WiFi🛜
    - ✅STA
    - 🚩AP
  - 📍Bluetooth🛜
    - 🚩SSP
    - 🚩A2DP
  - 📍LCD
    - ✅LovyanGFX
  - 🚩IMU
  - 🚩マイク
  - 🚩スピーカー📢
  - 🚩PMIC
  - 🚩RGB LED ... NeoPixel x10
  - ✅SDIO(microSDカード)
  - 📍ボタン(タッチセンサ)
    - ✅ボタンA
    - ✅ボタンB
    - ✅ボタンC