# MotorDriver ver3.0
ArduinoとESP32で2ピンと3ピンタイプのモータードライバーをデジタル/アナログ出力で制御するライブラリ  

## ファイル構成
```
MotorDriver/
├─ examples/                # サンプルフォルダ
│  ├─ basicusage/
│  │  └─ basicusage.ino     # DigitalMotorDriverとAnalogMotorDriverの基本的な使い方の例
│  └─ L298N_analog/
│     └─ L298N_analog.ino   # L298NをAnalogMotorDriverで制御する例
├─ src/                     # ライブラリ本体
│  ├─ AccelMotorDriver.h    # 加減速付きモータードライバーのヘッダファイル
│  ├─ AnalogMotorDriver.h   # アナログ出力モータードライバーのヘッダファイル
│  └─ DigitalMotorDriver.h  # デジタル出力モータードライバーのヘッダファイル
├─ library.properties
└─ README.md
```

## 使い方
### `DigitalMotorDriver.h`
- インクルードしてDigitalMotorクラスのインスタンスを作成(ピン配列をコンストラクタの引数で渡す)。
- `begin()`で初期化、`write(方向は-1,0,1で指定)`でモーターを回転させる。

### `AnalogMotorDriver.h`
- インクルードしてAnalogMotorクラス(3ピンの場合はAnalogMotor_3pin)のインスタンスを作成(ピン配列をコンストラクタの引数で渡す)。
- `begin()`で初期化、`write(速度は-255~255で指定)`でモーターを回転させる。

### `AccelMotorDriver.h`
- インクルードしてAccelMotorクラス(3ピンの場合はAccelMotor_3pin)のインスタンスを作成(ピン配列をコンストラクタの引数で渡す)。加速度と減速度を指定する(減速度は省略すると加速度と同じ値を使う)。
- `begin()`で初期化、`write(速度は-255~255で指定)`で目標速度に対して一定の加減速度を保つようにモーターを回転させる。
- `writeDirect()`を呼び出すと加減速を無視して即座に指定した速度でモーターを回転させる。

## 拡張
`AnalogMotor_Base`を継承して独自のモータードライバークラスを作成することができる(例：AnalogMotor_Arduinoクラス)。  
また、作成したモータードライバークラスに対して`AnalogMotorConcept`を用いて、任意のモータードライバークラスにさらなる機能を追加した拡張クラスを作成できる(例：AccelMotorWrapperクラス)。  

## ライセンス
[MIT License](LICENSE)

---
最終更新日: 2026-09-22  
更新者: Tomoooji  