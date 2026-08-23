# MotorDriver
ArduinoとESP32で2ピンと3ピンタイプのモータードライバーをデジタル/アナログ出力で制御するライブラリ  

## ファイル構成
```
MotorDriver/
├─ examples/
│  ├─ basicusage/
│  │  └─ basicusage.ino
│  └─ L298N_analog/
│     └─ L298N_analog.ino
├─ src/
│  ├─ AccelMotorDriver.h
│  ├─ AnalogMotorDriver.h
│  └─ DigitalMotorDriver.h
├─ library.properties
└─ README.md
```

## 使い方
### `DigitalMotorDriver.h`
- インクルードしてDigitalMotorクラスのインスタンスを作成。
- `attach()`でピン配列を指定して、`move(方向は-1,0,1で指定)`でモーターを回転させる。

### `AnalogMotorDriver.h`
- インクルードしてAnalogMotorクラス(3ピンの場合はAnalogMotor_3pin)のインスタンスを作成。
- `attach()`でピン配列を指定して、`move(速度は-255~255で指定)`でモーターを回転させる。

### `AccelMotorDriver.h`
- インクルードしてAccelMotorクラス(3ピンの場合はAccelMotor_3pin)のインスタンスを作成。加速度と減速度を指定する(減速度は省略すると加速度と同じ値を使う)。
- `attach()`でピン配列を指定して、`move_a(速度は-255~255で指定)`でモーターを回転させる。
- `move()`を呼び出すと加減速を無視して即座に指定した速度でモーターを回転させる。