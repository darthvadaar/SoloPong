#include <Servo.h> 
Servo tiltY; //Horizontal control servo
Servo pusher;

//MotorSpeeds:
int angY = 90;
int motorPinR = 5;
int motorPinL = 6;
int pusherAng = 90;
int pushDelay = 175;
int outL, outR;

void setup(){
  Serial.begin(9600);
  tiltY.attach(9);
  pusher.attach(10);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

}
  
void loop(){
  
  angY = map(analogRead(0),0,1023,46,134);
  tiltY.write(angY);
  outL = map(analogRead(1),0,1023,0,255);
  outR = map(analogRead(2),0,1023,0,255);
 
  pusher.write(0);
  delay(pushDelay);
  pusher.write(70);
  delay(pushDelay * 3);
  analogWrite(motorPinL,outL);
  analogWrite(motorPinR, outR);

  
  
}
