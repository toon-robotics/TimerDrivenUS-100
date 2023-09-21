# TimerDrivenUS-100

- [English](#english-ver)
- [日本語](#日本語版)

## English ver.
### Summary

- This is a module for ultrasonic distance sensor US-100 using ISR (Interrupt Service Routine) timer. It is possible to obtain distance information updated at regular intervals with a simple call. For more information, see this [blog post]().

### Ultrasonic Disntace Sensor US-100
- [adafruit](https://www.adafruit.com/product/4019#technical-details)
- [Digikey](https://www.digikey.com/en/products/detail/adafruit-industries-llc/4019/9808308?s=N4IgTCBcDaIKoGUC0BGADGkBdAvkA)

### Required Libraries
- [TimerInterrupt_Generic](https://github.com/khoih-prog/TimerInterrupt_Generic/tree/main)

### Connections between circuits
#### Arduino Leonardo
- Connect Vcc of US-100 to 5V or 3.3v of Arduino Leonardo
- Connect GND of US-100 to GND of Arduino Leonardo
- Connect Trig/TX on US-100 to TX (digital pin 1) on Leonardo
- Connect Echo/RX of US-100 to RX (digital pin 0) of Leonardo　　
#### Raspberry Pi Pico
- Connect Vcc of US-100 to 3.3V of Pi Pico
- Connect GND of US-100 to GND of Pi Pico
- Connect US-100's Trig/TX to Pi Pico's UART0 TX (GP0)
- Connect Echo/RX on US-100 to UART0 RX (GP1) on Pi Pico
### Usage
- Connect US-100 to Arduino Leonardo or Raspberry Pi Pico
- Open the sketch TimerDrivenUS-100.ino
- Install necessary libraries
- Upload & Run
- Display serial monitor

### Note
- You can also get the temperature by doing getTemperature() after executing requestTemperature().
- The constructor is
```
US100(unsigned int minDist = 100U, unsigned int maxDist = 2500U);
```
which allows you to set the minimum and maximum distance. If the distance outside of this range is observed, 0 is returned.

- You can change the measurement interval by setting TIMER_INTERVAL_MS in US100.h.

---

## 日本語版

### 概要
- ISR(Interrupt Service Routine)タイマーを使った超音波距離センサUS-100用モジュールです。簡単な呼び出しだけで一定間隔で更新される距離情報を取得できます。詳細は[こちら]()
###  超音波測距センサUS-100
- [adafruit](https://www.adafruit.com/product/4019#technical-details)
- [スイッチサイエンス](https://www.switch-science.com/products/5512)
- [マルツオンライン](https://www.marutsu.co.jp/pc/i/31848997/)

### 使用ライブラリ
- [TimerInterrupt_Generic](https://github.com/khoih-prog/TimerInterrupt_Generic/tree/main)

### 接続
#### Arduino Leonardo
- US-100のVccはArduino Leonardoの5Vまたは3.3vと接続
- US-100のGNDはArduino LeonardoのGNDと接続
- US-100のTrig/TXはLeonardoのTX（デジタルピン1）と接続
- US-100のEcho/RXはLeonardoのRX（デジタルピン0）と接続
#### Raspberry Pi Pico
- US-100のVccはPi Picoの3.3vと接続
- US-100のGNDはPi PicoのGNDと接続
- US-100のTrig/TXはPi PicoのUART0 TX（GP0）と接続
- US-100のEcho/RXはPi PicoのUART0 RX（GP1）と接続
### 使い方
- US-100とArduino LeonardoまたはRaspberry Pi Picoを接続する
- スケッチTimerDrivenUS-100.inoを開く
- ライブラリを導入
- アップロード＆実行
- シリアルモニターを表示
### メモ
- requestTemperature()を実行後にgetTemperature()を行うと気温もとれます。
- コンストラクタは
```
US100(unsigned int minDist = 100U, unsigned int maxDist = 2500U);
```
となっており、最小・最大距離を設定できます。この範囲外の計測値の場合は0を返します。

- US100.hのTIMER_INTERVAL_MSを変更することで測定間隔を調整できます。