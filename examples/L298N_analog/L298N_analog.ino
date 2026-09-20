// Arduino UNOでモータードライバーL298Nを制御する //

#include <AnalogMotorDriver.h>

struct Analog_L298N {
  const int pinA[] = {9, 8, 10};
  const int pinB[] = {7, 6, 5};
  AnalogMotor_3pin A(pinA);
  AnalogMotor_3pin B(pinB);
  void begin() {
    this->A.begin();
    this->B.begin();
  }
  void forward() {
    this->A.write(255);
    this->B.write(255);
  }
  void back() {
    this->A.write(-255);
    this->B.write(-255);
  }
  void left() {
    this->A.write(100);
    this->B.write(-100);
  }
  void right() {
    this->A.write(-100);
    this->B.write(100);
  }
  void stop() {
    this->A.write(0);
    this->B.write(0);
  }
} L298N;

void setup() {
  L298N.begin();
}

void loop() {
  L298N.forward();
  delay(1000);
  L298N.stop();
  delay(500);
  L298N.back();
  delay(1000);
}
