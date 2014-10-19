#include <Wire.h>
#include <SPI.h>
#include <SNShield.h>

/*
  ReadSensors
  This sample read sensors on Sensor Network Shield,
  then display the data.

  Note: This sample needs to import below libraries.
        - SNShield
        - SPI
        - Wire
        
 
  This example code is in the public domain.
 */

SNShield kurumi;

#define sensTime 4000
#define mskTime 100
#define micThrH 800
#define micThrL 100

//Rhythm (interval time)
unsigned long intervalT_me[20];  // measured time intevals
unsigned long intervalT_pw[20];  // stored time intervals (PASS WORD)
unsigned long curTime;           // current time
unsigned long tmpTime;           // temporary variable

// Pin 22,23,24 are assigned to RGB LEDs.
int led_red   = 22; // LOW active
int led_green = 23; // LOW active
int led_blue  = 24; // LOW active

//Microphone
#define _MicPin A3 // Pin for microphone
unsigned int mic_data;     // A/D value of microphone
unsigned int mic_tmp;      // temperary variable


void setup() {
  //Initialization
  kurumi.begin();
  Serial.begin(115200);
  Serial2.begin(115200);
  mic_data = 0;
  mic_tmp  = 0;
  
  for(int i=0; i<20; i++){
    intervalT_me[i] = 0;
    intervalT_pw[i] = 0;
  }
  
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_blue, OUTPUT);

  // turn the LEDs on, glow white.
  digitalWrite(led_red, LOW);
  digitalWrite(led_green, LOW);
  digitalWrite(led_blue, LOW);
}

void loop() {
  
//  mic_data = (analogRead(_MicPin)>>3);
  mic_data = analogRead(_MicPin);

  if((mic_data > micThrH)||(mic_data < micThrL)){
    int rhythmNum = 1;
    int intervalNum;
    Serial2.write('r');
    delay(500);
    while(1){
      delay(1);
//      mic_data = (analogRead(_MicPin)>>3);
      mic_data = analogRead(_MicPin);
      if((mic_data > micThrH)||(mic_data < micThrL)){
        Serial.println(mic_data,10);
        //Recording start (LED:RED)
        digitalWrite(led_red, LOW);
        digitalWrite(led_green, HIGH);
        digitalWrite(led_blue, HIGH);
        delay(mskTime);
        break;
      }
    }
    //Recording start
    while(1){
      delay(1);
//      mic_data = (analogRead(_MicPin)>>3);
      mic_data = analogRead(_MicPin);
      if((mic_data > micThrH)||(mic_data < micThrL)){
        intervalT_pw[0] = millis();
        Serial.println(mic_data,10);
        //Recording start (LED:GREEN)
        digitalWrite(led_red, HIGH);
        digitalWrite(led_green, LOW);
        digitalWrite(led_blue, HIGH);
        delay(mskTime);
        break;
      }
    }
    unsigned long endTime = intervalT_pw[0]+sensTime; 
    while(1){
      delay(1);
//      mic_data = (analogRead(_MicPin)>>3);
      mic_data = analogRead(_MicPin);
      if((mic_data > micThrH)||(mic_data < micThrL)){
        intervalT_pw[rhythmNum] = millis();
        Serial.println(mic_data,10);
        rhythmNum++;
        if(rhythmNum%2==0) digitalWrite(led_blue, LOW);
        else digitalWrite(led_blue, HIGH);
        delay(mskTime);
      }
      if(rhythmNum==20)break;
      if(endTime < millis())break;
    }
    //Recording finish (LED:BLUE)
    digitalWrite(led_red, HIGH);
    digitalWrite(led_green, HIGH);
    digitalWrite(led_blue, LOW);
    
    //Play start (LED:WHITHE)
    Serial2.write('c');
    digitalWrite(led_red, LOW);
    digitalWrite(led_green, LOW);
    digitalWrite(led_blue, LOW);
    delay(1000);
    for(intervalNum=0; intervalNum<rhythmNum; intervalNum++){
      if(intervalNum%2==0) {
        digitalWrite(led_red, LOW);
        digitalWrite(led_green, HIGH);
        digitalWrite(led_blue, LOW);
      }
      else{
        digitalWrite(led_red, HIGH);
        digitalWrite(led_green, LOW);
        digitalWrite(led_blue, LOW);
      }
      if(intervalNum<rhythmNum-1) {
        Serial2.write('c');
        delay((unsigned int)(intervalT_pw[intervalNum+1]-intervalT_pw[intervalNum]));
      }
//      else delay((unsigned int)(sensTime - intervalT_pw[intervalNum]));
      else {
        Serial2.write('c');
        delay(1000);
      }
    }
    //Play finish (LED:WHITHE)
    Serial2.write('e');
    digitalWrite(led_red, LOW);
    digitalWrite(led_green, LOW);
    digitalWrite(led_blue, LOW);
    delay(500);


    //
    //Pass word matching
    //
    for(int i=0; i<20; i++){
      intervalT_me[i] = 0;
    }
    int rhythmNum_me = 1;
    while(1){
      delay(1);
//      mic_data = (analogRead(_MicPin)>>3);
      mic_data = analogRead(_MicPin);
      if((mic_data > micThrH)||(mic_data < micThrL)){
        Serial.println(mic_data,10);
        //Recording start (LED:RED)
        digitalWrite(led_red, LOW);
        digitalWrite(led_green, HIGH);
        digitalWrite(led_blue, HIGH);
        delay(mskTime);
        break;
      }
    }
    //Recording start
    while(1){
      delay(1);
//      mic_data = (analogRead(_MicPin)>>3);
      mic_data = analogRead(_MicPin);
      if((mic_data > micThrH)||(mic_data < micThrL)){
        intervalT_me[0] = millis();
        Serial.println(mic_data,10);
        //Recording start (LED:GREEN)
        digitalWrite(led_red, HIGH);
        digitalWrite(led_green, LOW);
        digitalWrite(led_blue, HIGH);
        delay(mskTime);
        break;
      }
    }
    endTime = intervalT_me[0]+sensTime; 
    while(1){
      delay(1);
//      mic_data = (analogRead(_MicPin)>>3);
      mic_data = analogRead(_MicPin);
      if((mic_data > micThrH)||(mic_data < micThrL)){
        intervalT_me[rhythmNum_me] = millis();
        Serial.println(mic_data,10);
        rhythmNum_me++;
        if(rhythmNum%2==0) digitalWrite(led_blue, LOW);
        else digitalWrite(led_blue, HIGH);
        delay(mskTime);
      }
      if(rhythmNum_me==20)break;
      if(endTime < millis())break;
    }
    
    //
    // Judge start
    //
    signed long judgeValue;
    judgeValue = 0;
    for(intervalNum=0; intervalNum<rhythmNum; intervalNum++){
      intervalT_pw[intervalNum] = intervalT_pw[intervalNum+1]-intervalT_pw[intervalNum];
      intervalT_me[intervalNum] = intervalT_me[intervalNum+1]-intervalT_me[intervalNum];
      judgeValue = (signed long)(intervalT_pw[intervalNum] - intervalT_me[intervalNum]);
      Serial.print((unsigned int)intervalT_pw[intervalNum],10);
      Serial.write('\t');
      Serial.print((int)intervalT_me[intervalNum],10);
      Serial.write('\t');
      Serial.println((int)judgeValue,10);
      delay(20);
    }
    if(judgeValue > (unsigned long)rhythmNum*500){
      digitalWrite(led_red, LOW);
      digitalWrite(led_green, HIGH);
      digitalWrite(led_blue, HIGH);
    }
    else {
      digitalWrite(led_red, HIGH);
      digitalWrite(led_green, HIGH);
      digitalWrite(led_blue, LOW);
    }
    delay(1000);


    //Play finish (LED:WHITHE)
    digitalWrite(led_red, LOW);
    digitalWrite(led_green, LOW);
    digitalWrite(led_blue, LOW);
    delay(500);
  }
  else {
/*    int mic_tmp_ave;
    for(int i=0; i<256; i++){
      mic_tmp_ave = mic_tmp_ave + (int)(analogRead(_MicPin)>>3);
      delay(10);
    }
    mic_tmp_ave = mic_tmp_ave/256;
    mic_tmp  = mic_tmp_ave;*/
    delay(1);
  }//*/
}



