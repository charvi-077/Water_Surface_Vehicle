#include  <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int Left_ctr = 0;
int Right_ctr = 0;
byte data[4] = {0,0,0,0};
int joystick_1_PushButtonPin = 2;
int joystick_2_PushButtonPin = 3;


void setup(void){
 Serial.begin(115200);
 radio.begin();
 radio.setChannel(108);
 radio.openWritingPipe(pipe);
 //pinMode(3, OUTPUT);+
 // pinMode(4, OUTPUT);
 // digitalWrite(4, HIGH);
 // digitalWrite(3, LOW);
 pinMode(joystick_1_PushButtonPin, INPUT);
 pinMode(joystick_2_PushButtonPin, INPUT);
 digitalWrite(joystick_1_PushButtonPin, HIGH);
 digitalWrite(joystick_2_PushButtonPin, HIGH);
}


 
void loop(void){
  Left_ctr = analogRead(A0);
  Right_ctr = analogRead(A1);
  data[0] = map(Left_ctr, 0, 1023, 0, 255);
  data[1] = map(Right_ctr, 0, 1023, 0, 255);
  data[2]= digitalRead(joystick_1_PushButtonPin);
  data[3]= digitalRead(joystick_2_PushButtonPin);
  //data[0]=(data[0]-127)*2;
  //data[1]=(data[0]-127)*2;
  radio.write(data, sizeof(data));

  
//  Serial.println(throttle_l);
 // Serial.println(data[0]);
 // Serial.println("  :  ");
 // Serial.println(data[1]);
 // delay(1000);
 }
  
