// Arduino UNOでモータードライバーL298Nを制御する //

#include <AnalogMotorDriver.h>

struct Analog_L298N{
  AnalogMotor_3pin A;
  AnalogMotor_3pin B;
  const int pinA[] = {9,8,10};
  const int pinB[] = {7,6,5};
  void begin(){
    this->A.attach(this->pinA);
    this->B.attach(this->pinB);
  }
  void forward(){
    this->A.move(255);
    this->B.move(255);
  }
  void back(){
    this->A.move(-255);
    this->B.move(-255);
  }
  void left(){
    this->A.move( 100);
    this->B.move(-100);
  }
  void right(){
    this->A.move(-100);
    this->B.move( 100);
  }
  void stop(){
    this->A.move(0);
    this->B.move(0);
  }
} L298N;

void setup(){
  L298N.begin();
}

void loop(){
  L298N.forward();
  delay(1000);
  L298N.stop();
  delay(500);
  L298N.back();
  delay(1000);
}
