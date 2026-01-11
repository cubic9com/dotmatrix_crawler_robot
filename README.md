# Overview / 概要

This project implements a crawler robot that receives movement commands via [ESP-NOW protocol](https://www.espressif.com/en/solutions/low-power-solutions/esp-now) and displays animated directional arrows on a 16x16 LED dot-matrix.

\[日本語\]

[ESP-NOWプロトコル](https://www.espressif.com/en/solutions/low-power-solutions/esp-now) で操作できるクローラーロボットを作ってみました。ジョイスティックから送った指示に合わせて走り、走行方向を16x16のLEDドットマトリックスに表示します。

![video](video.gif)

# Story

It all began with a simple question:
"What if a robot could show what it’s thinking while it moves?"

Crawler robots are excellent at overcoming obstacles, but they often feel silent and purely mechanical. I wanted to give mine something more—a way to express its intentions. To achieve this, I added a 16x16 WS2812B LED matrix to the front of the robot. Rather than serving as a static decoration, the display became the robot's "face."

When the robot moves forward, a bold arrow appears. When it turns, the arrow shifts to match its direction. These small visual cues transform the robot from a cold machine into something that feels more like a tiny creature with purpose and awareness.

The robot receives its movement commands wirelessly using the [ESP-NOW protocol](https://www.espressif.com/en/solutions/low-power-solutions/esp-now). At the heart of the system is a [Seeed Studio XIAO ESP32-C6 microcontroller](https://wiki.seeedstudio.com/xiao_esp32c6_getting_started/), which manages both motion control and display logic. A [Toshiba TB6612FNG dual motor driver](https://aliexpress.com/item/1005005973846875.html) powers the crawler's motors, while the [16x16 WS2812B LED dot-matrix panel](https://aliexpress.com/item/4000544584524.html) brings its actions to life with bright, crisp arrow animations.

\[日本語\]

すべては、こんな素朴な疑問から始まりました。
「ロボットが動きながら、自分の考えを“見せる”ことができたらどうだろう？」

クローラーロボットは走破性に優れていますが、どこか無言で、ただの機械のようにも感じられます。そこで私は、このロボットに「意思を表現する手段」を与えたいと考えました。その答えが、ロボットの上部に取り付けた 16×16のLEDドットマトリクスディスプレイです。単なる装飾ではなく、この表示をロボットの「顔」として機能させました。

前進するときには太い矢印が表示され、旋回すると矢印も進行方向に合わせて変化します。こうした小さな視覚的表現によって、ロボットは冷たい機械から、目的と意識を持った小さな生き物のような存在へと変わっていきます。

ロボットの動作指令は [ESP-NOW プロトコル](https://www.espressif.com/en/solutions/low-power-solutions/esp-now) を用いて無線で送信されます。中核となるのは [Seeed Studio XIAO ESP32-C6](https://wiki.seeedstudio.com/xiao_esp32c6_getting_started/) マイコンで、走行制御と表示制御の両方を担っています。モーターの駆動には [東芝製TB6612FNGデュアルモータードライバー](https://aliexpress.com/item/1005005973846875.html) を使用し、[16×16のWS2812B LEDドットマトリクス](https://aliexpress.com/item/4000544584524.html) が、明るくシャープな矢印アニメーションによってロボットの動きを視覚的に表現します。

# Hardware Requirements / ハードウェア要件

## Components / コンポーネント

- Microcontroller: [Seeed Studio XIAO ESP32-C6](https://wiki.seeedstudio.com/xiao_esp32c6_getting_started/)
- Motor Driver: [Toshiba TB6612FNG dual motor driver](https://aliexpress.com/item/1005005973846875.html)
- Crawler Kit: [TP101](https://aliexpress.com/item/1005002052435803.html)
- Dot-Matrix Display: [16x16 WS2812B LED dot-matrix panel](https://aliexpress.com/item/4000544584524.html)
- Rechargeable Ni-MH AA Battery x 4 (4.8V)

\[日本語\]

- マイクロコントローラー: [Seeed Studio XIAO ESP32-C6](https://wiki.seeedstudio.com/xiao_esp32c6_getting_started/)
- モータードライバー: [東芝 TB6612FNG デュアルモータードライバー](https://aliexpress.com/item/1005005973846875.html)
- クローラーキット: [TP101](https://aliexpress.com/item/1005002052435803.html)
- ドットマトリックスディスプレイ: [16x16 WS2812B LEDドットマトリックスパネル](https://aliexpress.com/item/4000544584524.html)
- ニッケル水素充電池 x 4 (4.8V)

## Pin Connections / ピン接続

| XIAO ESP32-C6 Pin | TB6612FNG Pin  | Dot-matrix display Pin  | Battery Pin |
| ----------------- | -------------- | ----------------------- | ----------- |
| D0                | PWMA           | -                       | -           |
| D1                | AIN2           | -                       | -           |
| D2                | AIN1           | -                       | -           |
| D3                | BIN1           | -                       | -           |
| D4                | BIN2           | -                       | -           |
| D5                | PWMB           | -                       | -           |
| D7                | -              | DIN                     | -           |
| D8                | -              | -                       | -           |
| D9                | -              | -                       | -           |
| D10               | STBY           | -                       | -           |
| 3V3               | VCC            | -                       | -           |
| GND               | GND            | GND                     | GND         |
| VBUS              | -              | -                       | VBAT        |
| -                 | VM             | -                       | VBAT        |
| -                 | -              | 5V                      | VBAT        |

![circuit](circuit01.jpg)
![circuit](circuit02.jpg)

# Software Requirements / ソフトウェア要件

## Dependencies / 依存ライブラリ

- [FastLED](https://github.com/FastLED/FastLED) - LED dot-matrix control
- [LovyanGFX](https://github.com/lovyan03/LovyanGFX) - Graphics rendering

\[日本語\]

- [FastLED](https://github.com/FastLED/FastLED) - LEDドットマトリクス制御
- [LovyanGFX](https://github.com/lovyan03/LovyanGFX) - グラフィックスレンダリング

# Project Structure / プロジェクト構成

```
dotmatrix_crawler_robot/
├── src/
│   └── main.cpp                    # Main program logic
├── include/
│   ├── constants.h                 # Pin definitions and configuration
│   ├── motor_controller.hpp        # Motor control interface
│   ├── led_display.hpp             # LED dot-matrix display interface
│   ├── animation_controller.hpp    # Animation manager
│   └── arrow_images.h              # Pregenerated arrow image data
├── platformio.ini                  # PlatformIO configuration
└── README.md                       # This file
```

\[日本語\]

```
dotmatrix_crawler_robot/
├── src/
│   └── main.cpp                    # メインプログラムロジック
├── include/
│   ├── constants.h                 # ピンの定義と設定
│   ├── motor_controller.hpp        # モーター制御インターフェース
│   ├── led_display.hpp             # LEDドットマトリックスディスプレイインターフェース
│   ├── animation_controller.hpp    # アニメーション管理
│   └── arrow_images.h              # 事前生成された矢印画像データ
├── platformio.ini                  # PlatformIOの設定
└── README.md                       # このファイル
```

# How to Change the Images / 画像の変更方法

1. Open the image with [GIMP](https://www.gimp.org/).
1. Click [File] > [Export As...].
1. Click [Select File Type (By Extension)].
1. Select [C source code].
1. Click [Export] button.
1. Open the exported file.
1. Copy the data section enclosed in double quotation marks and replace the corresponding element in `arrowImg` array within `include/arrow_images.h`.

\[日本語\]

1. GIMPを画像を開く。
1. 「ファイル」 > 「名前をつけてエクスポート」をクリックする。
1. 「ファイル形式の選択」をクリックする。
1. 「C ソースコード」を選択する。
1. 「エクスポート」ボタンをクリックする。
1. エクスポートされたファイルを開く。
1. ダブルクォーテーションで囲まれたデータ部をコピーし、　`include/arrow_images.h` の `arrowImg` 配列内の要素と置き換える。

# Related Projects / 関連プロジェクト

- A wireless joystick: [dotmatrix_crawler_joystick](https://github.com/cubic9com/dotmatrix_crawler_joystick) - The wireless joystick for this crawler robot

\[日本語\]

- 無線ジョイスティック: [dotmatrix_crawler_joystick](https://github.com/cubic9com/dotmatrix_crawler_joystick) - このクローラーロボット用の無線ジョイスティック

# License / ライセンス

Copyright (C) 2025, cubic9com All rights reserved.

This project is licensed under the MIT license.

See the `LICENSE` file for details.
