# MotorDriver ライブラリ
Arduino UNOとESP32でPWM出力×2ピンタイプとデジタル出力×2ピン+PWM出力2ピンタイプ両方のモータードライバーを制御するためのライブラリです。  
# 仕様説明
速度指定とモーターへの出力を別関数に分けているためデバックが楽(?)です。加速度と減速度を指定して線形な加減速を行うこともできます。  
exampleにはL298N(3ピン制御×2モーター)用のサンプルコードがあります。
# 使い方
最初にArduino IDEの Sketch → include Library → Add .ZIP Library... からこのzipファイルを選択してください。
``` C++
#include <MotoDriver.h>

//Arduino UNO//
MotorDriver2pin Motor1; //PWM出力×2ピンタイプ
MotorDriver3pin Motor2; //デジタル出力×2ピン+PWM出力2ピンタイプ
//ESP32//
ESP32MotorDriver2pin Motor1; //PWM出力×2ピンタイプ
ESP32MotorDriver3pin Motor2; //デジタル出力×2ピン+PWM出力2ピンタイプ

//デジタル出力のみで動かしたい場合は第一引数にtrueを指定
MotorDriver2pin Motor1{true};

//モーターの上限速度(~255)と下限速度(0~)を設定することも可能 (デフォルトはmax:255,min:0)
MotorDriver2pin Motor1{max, min}; //上記の他classも同様

void setup(){
  //ピン設定
  Motor1.attach(pin1, pin2);
  Motor2.attach(pin1, pin2, pinPWM);
  //速度設定
  Motor1.setVelocity(speed); //符号が回転方向、絶対値が回転速度
  //デジタル出力のみの時はspeed=0の時に停止、それ以外は回転し続ける
   Motor1.setSpeed(speedval); //回転速度だけ変更したい時用
   //デジタル出力のみの時はspeedval=0の時に停止、それ以外は回転し続ける
   Motor1.setDirec(1 or -1); //回転方向だけ指定したい時用
  //加速度設定(デジタル出力のみの場合は無効)
  Motor1.setAccel(accel, decel);
  Motor1.setAccel(accel); //decelを省略するとaccelと同じになる
}

void loop(){
  //モーター出力
  Motor1.move(); //設定済みのVerocityに従ってモーターを回転
  Motor1.move(velocity); //内部のverocityを引数から更新し、モーターを回転
  Motor1.forward();   //前進
  Motor1.backward();  //後退
  Motor1.stop();      //停止(ニュートラル)
  Motor1.lock();      //モーターの軸を固定して停止
  //加減速制御(デジタル出力のみの場合は無効)
  Motor1.accelLiner(target); //targetが現在の速度より小さい場合はaccelを用いて減速
                             //target省略時は初期化時の上限速度を使用
  Motor1.decelLiner(targat); //targetが現在の速度より大きい場合はdecelを用いて加速
                             //target省略時は初期化時の下限速度を使用
  //値取得用
  Motor1.getSpeed();
  Motor1.getAccel();
  Motor1.getDecel();
}
```
# 注意
- ## **実機での動作は未検証です！**
- 3pinの方でpin1,pin2だけを指定した場合、デフォルトのpwmピン(Arduino UNO: 11ピン, ESP32: 15ピン)が使われます。

---  
作成者：金栄智治  
最終更新日：2026/02/25
