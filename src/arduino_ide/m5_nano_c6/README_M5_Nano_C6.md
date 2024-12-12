# M5NanoC6評価F/W開発

M5NanoC6の評価F/W開発ブランチ👩‍💻

## 📍開発環境

### 📍IDE

- 📍[Arduino IDE v2.34🔗](https://github.com/arduino/arduino-ide/releases/tag/2.3.4)
  - 📍[[GitHub] M5NanoC6🔗](https://github.com/m5stack/M5NanoC6)

### 📍基板

- 📍[M5Stack Nano C6🔗](https://docs.m5stack.com/ja/core/M5NanoC6)

## 実装状況

**凡例(✅実装済み、🚩TODO、❌TBD)**

- 📍OS
  - 📍FreeRTOS
    - ✅📍インタスク
      - ✅SDカードのR/W
      - ✅ボタンポーリング
      - ✅RGBLEDのアプリ処理
    - 📍WiFiタスク🛜
      - ✅STA
      - ✅AP