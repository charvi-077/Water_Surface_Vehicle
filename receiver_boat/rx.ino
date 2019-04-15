#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
//int throttle_l=0;
//int throttle_r=0;
byte data[2]={0,0};
int left_fan=0;
int right_fan=0;
const int enable_left=6 ;
const int enable_right=5 ;
const int m1for=4 ;
const int m1back=3 ;
const int m2for= 2;
const int m2back=7 ;

void setup(void){
 Serial.begin(9600);
 radio.begin();
 radio.setChannel(108);
 radio.openReadingPipe(1,pipe);
 radio.startListening();
 pinMode(6,OUTPUT);
 pinMode(7,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(2,OUTPUT);}
 
 
 void loop(void){
 if (radio.available()){
    radio.read(data, 2);
   Serial.println(data[0]);
   Serial.println(data[1]);
   //delay(1000);
 
    
   right_fan=(data[0]-127)*2;
   left_fan=(data[1]-127)*2;
if (left_fan<-255){left_fan=-255;}
    if (left_fan>255){left_fan=255;}
    if (right_fan<-255){right_fan=-255;}
    if (right_fan>255){right_fan=255;}
   Serial.println(left_fan);
   Serial.println(right_fan);
   Serial.println("");
 if (left_fan == 4) {
      digitalWrite(m1back,LOW);
      digitalWrite(m1for,LOW);
      Serial.println("motor not moving");
      
    }
    else if (left_fan<4){
      analogWrite(enable_left,-(left_fan));
      digitalWrite(m1back,HIGH);
      digitalWrite(m1for,LOW);
      Serial.println(" left motor moving forward");
    }
    else {analogWrite(enable_left,left_fan);
      digitalWrite(m1for,HIGH);
      digitalWrite(m1back,LOW);
      Serial.println(" left motor moving backward");
    }
      
    if (right_fan == 0) {
      digitalWrite(m2back,LOW);
      digitalWrite(m2for,LOW);
      Serial.println("motor not moving");
      
    }
    else if (right_fan<0){
      analogWrite(enable_right,-(right_fan));
      digitalWrite(m2back,HIGH);
      digitalWrite(m2for,LOW);
      Serial.println(" right motor moving forward");
    }
      
    else {
      analogWrite(enable_right,right_fan);
      digitalWrite(m2for,HIGH);
      digitalWrite(m2back,LOW);
      Serial.println(" right motor moving backward");
      }
    
   
 }}
    //if (right_fan<-210) {right_fan=-210;}
    //throttle_l=map(data[0],0,1023,1000,2000);
    //throttle_r=map(data[1],0,1023,1000,2000);
    //if (right_fan>210){right_fan=210;}
   
