#include "MotorDriver.h"
#include "MotorDriver3pin.h"

MotorDriver wheel;
//*
L298N leg;

void InitAll(){
  wheel.Attach(3,11);
  leg.A.Attach(7,6,5);
  leg.B.Attach(8,9,10);
}

void setup(){
  InitAll();
}

void loop() {
  wheel.Forward();
  leg.A.Forward();
  leg.B.Backward();
  delay(1000);
  wheel.Stop();
  leg.A.Stop();
  leg.B.Stop();
  delay(100);
  wheel.Backward();
  leg.A.Backward();
  leg.B.Forward();
  delay(1000);
}
//*/
// 以下は加速度制御用 //
/*
bool accel = true;

void setup(){
  Serial.begin(9600);
  wheel.Attach(5,6);
  wheel.SetAccel(10,5);
  delay(1000);
}

void loop(){
  if(accel){
    wheel.AccelLiner();
    if(wheel.GetSpeed() == SPEED_MAX){
      accel = false;
    }
  }
  else{
    wheel.DecelLiner();
    if(wheel.GetSpeed() == SPEED_MIN){
      accel = true;
    }  
  }
  wheel.Forward();
  Serial.println(wheel.GetSpeed());
  delay(100);
}
//*/