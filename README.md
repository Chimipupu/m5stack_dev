# M5Stack評価F/W開発
M5Stackの評価F/W 開発リポジトリ👩‍💻

## 対象
- ✅M5Stick C Plus
- ✅M5Stack Core2 AWS

## ブランチ
- ✅[M5Stick C Plus🔗（ブランチ）](https://github.com/Chimipupu/m5stack_dev/tree/m5stick_c_plus)
- ✅[M5Stack Core2 AWS🔗（ブランチ）](https://github.com/Chimipupu/m5stack_dev/tree/m5stack_core2_aws)

## 実装状況
**凡例(✅実装済み、🆗ライブラリAPI、🚩TODO、❌TBD)**

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