#include "snshield_fuji.h"
//#include <SNShield.h>
#include <SPI.h>
#include <Wire.h>


long long time_st;
SNShield kurumi;
int accy;
int gyroy;

void setup() {
  // put your setup code here, to run once:
  kurumi.begin();
  Serial.begin(115200);
  Serial2.begin(115200);

  time_st = micros();
  time_st = time_st + 500000;
}

void loop() {
  char c1 = Serial.read();
  if(c1=='s'){
    time_st = micros() + 500000;
    while(1){
      while(time_st>micros());
      time_st = time_st+10000;

//      gyroy = kurumi.getRawGyroy();
      gyroy = kurumi.getRawAccy();
//      accy = kurumi.getRawAccy();
      accy = analogRead(A3);
      
      Serial.print(accy,10);
      Serial.write(',');
      Serial.print(gyroy,10);
      Serial.write('\r\n');
      c1 = Serial.read();
      if(c1=='e')break;
      Serial.flush();
    }
  }
  char c2 = Serial2.read();
  if(c2=='s'){
    time_st = micros() + 500000;
    while(1){
      while(time_st>micros());
      time_st = time_st+10000;

//      gyroy = kurumi.getRawGyroy();
      gyroy = kurumi.getRawAccy();
//      accy = kurumi.getRawAccy();
      accy = analogRead(A3);
      
      Serial2.print(accy,10);
      Serial2.write(',');
      Serial2.print(gyroy,10);
      Serial2.write('\r\n');
      c2 = Serial2.read();
      if(c2=='e')break;
      Serial2.flush();
    }
  }
}
