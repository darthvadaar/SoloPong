/*
INPUTS:
Potentiometer
IR sensor

OUTPUTS:
Motor
Servo
RGB LED



*/

#include <Event.h>
#include "Timer.h"
#include <Servo.h>
//#include <IRremote.h>
//IRrecv irrecv(4);
//decode_results results;
Servo tiltY; //Horizontal control servo
Servo tilt2;
Servo pusher;
//IR
//int signal = 0;
//timer
Timer t;
int tickEvent1;
int tickEvent2;

//pins
int angY = 90;
int motorPinR = 5;
int motorPinL = 6;

int R = 2;
int G = 1;
int B = 0;

//counters
int pusherAng = 90;
int pushDelay = 350;
int outL, outR;

void setup(){
  Serial.begin(9600);
  tiltY.attach(9);
  tilt2.attach(3);
  pusher.attach(10);
 // irrecv.enableIRIn();
  pinMode(motorPinR,OUTPUT);
  pinMode(motorPinL,OUTPUT);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  
  tickEvent1 = t.every(pushDelay,pusherback);
}


void loop(){
  
  angY = map(analogRead(0),0,1023,46,134);
  tiltY.write(angY);
  tilt2.write(180 - angY);
  outL = map(analogRead(1),0,1023,0,255);
  outR = map(analogRead(2),0,1023,0,255);
  difficulty();
  
  analogWrite(motorPinL,outL);
  analogWrite(motorPinR, outR);
  t.update();
/*  if (irrecv.decode(&results)){
    Serial.println("yay");
    if (results.value != signal){
      signal = results.value;
      Serial.println(signal);
    }
  }
  irrecv.resume();*/
  
}


//pushing functions
void pusherback(){
  pusher.write(0);
  tickEvent1 = t.after(400,pusherpush);
}
void pusherpush (){
  pusher.write(65);
}

void difficulty(){
 if (pushDelay < 200){
   digitalWrite(R, LOW);
   digitalWrite(G, HIGH);
   digitalWrite(B, LOW);
 }
 else if(pushDelay < 400){
   digitalWrite(R, LOW);
   digitalWrite(G, LOW);
   digitalWrite(B, HIGH);
 }
 else if(pushDelay > 400){
   digitalWrite(R, HIGH);
   digitalWrite(G, LOW);
   digitalWrite(B, LOW);
 }
  
}

