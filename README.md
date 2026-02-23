# MotorDriver ライブラリ
Arduino UNOとESP32でPWM出力×2ピンタイプとデジタル出力×2ピン+PWM出力2ピンタイプ両方のモータードライバーを制御するためのライブラリです。  
# 仕様説明
速度指定とモーターへの出力を別関数に分けているためデバックが楽(?)です。加速度と減速度を指定して線形な加減速を行うこともできます。  
exampleにはL298N(3ピン制御×2モーター)用のサンプルコードがあります。
# 使い方
Arduino IDEの Sketch → include Library → Add .ZIP Library... からこのzipファイルを選択してください。
```Arduino
#include <MotoDriver.h>

//Arduino UNO//
MotorDriver2pin Motor1; //PWM出力×2ピンタイプ
MotorDriver3pin Motor2; //デジタル出力×2ピン+PWM出力2ピンタイプ
//ESP32//
ESP32MotorDriver2pin Motor1; //PWM出力×2ピンタイプ
ESP32MotorDriver3pin Motor2; //デジタル出力×2ピン+PWM出力2ピンタイプ

//モーターの上限速度と加減速度を設定することも可能 (デフォルトはmax:255,min:0)
MotorDriver2pin Motor1{max, min}; //上記の他classも同様

void setup(){
  //ピン設定
  Motor1.attach(pin1, pin2);
  Motor2.attach(pin1, pin2, pinPWM);
  //速度設定
  Motor1.setSpeed(speed);
  //加速度設定
  Motor1.setAccel(accel, decel);
  Motor1.setAccel(accel); //decelを省略するとaccelと同じになる
}

void loop(){
  //モーター出力
  Motor1.move(direc); //direc>0で正転、<0で逆転、==0でニュートラル
  Motor1.forward();   //Motor1.move(1)と等価
  Motor1.backward();  //Motor1.move(-1)と等価
  Motor1.stop();      //Motor1.move(0)と等価
  Motor1.lock();      //モーターの軸を固定して停止
  //加減速制御
  Motor1.accelLiner(target); //targetが現在の速度より小さい場合はaccelを用いて減速
                             //target省略時は上限速度を使用
  Motor1.decelLiner(targat); //targetが現在の速度より大きい場合はdecelを用いて加速
                             //target省略時は下限速度を使用
  //値取得用
  Motor1.getSpeed();
  Motor1.getAccel();
  Motor1.getDecel();
}
```
# 注意
- ## **実機での動作は未検証です！**
- 3pinの方でpin1,pin2だけを指定した場合、デフォルトのpwmピンが使われます。
- 2pinの方でpin1,pin2にアナログ出力ができないピンを指定するとエラーを吐きます(多分)。

---  
作成者：金栄智治  
最終更新日：2026/02/18