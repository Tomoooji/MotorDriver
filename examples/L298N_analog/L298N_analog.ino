// モータードライバーL298Nを制御する //

#include <array> // ライブラリ内でincludeはしているが念のため
#include <AnalogMotorDriver.h>

constexpr std::array<uint8_t, 3> pinA = {9, 8, 10};
constexpr std::array<uint8_t, 3> pinB = {7, 6, 5};

struct Analog_L298N {
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
