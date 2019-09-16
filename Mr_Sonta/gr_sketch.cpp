/*
 * gr_sketch.cpp - wavmp3p library
 * Copyright (c) 2015 Mitsuhiro Matsuura.  All right reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
/* This template is based on GR-CITRUS Sketch Template V1.00 */
/* Oct. 20th 2016, Yuuki Okamiya: modified using MTU1 for GR-CITRUS.*/

#include <Arduino.h>
#include <Utilities.h>
#include <MsTimer2.h>
#include <WavMp3p.h>
#include <SD.h>

#include <mh-z19.h>
#include <oled.h>

#define ON			1
#define OFF			0
#define LED_ON		HIGH
#define LED_OFF		LOW

#define PIN_SOL     3
unsigned char solOut;

#define PIN_ESPRST  4


typedef enum CO2Stage {
    GOOD,
    TYPICAL,
    BAD,
    DANGER
} CO2Stage;

CO2Stage stage;
const unsigned int ppmLevel[] = {500, 1000, 1500, 2000};

unsigned char solOn;

#define CYCLICINTERVAL 250
#define MININTERVAL    (60000/CYCLICINTERVAL)
unsigned long cyclicCnt;
unsigned long minCnt;


WavMp3p wavmp3p(44100);

static
void cyclic_handler(void);

void setup()
{
	cyclicCnt = 0;
	minCnt = 0;
	solOn = OFF;
	
	Serial.begin(115200);
	initMHZ19();         //Initialization of MH-Z19
	initOLED();          //Initialization of OLED displays
	
	Serial.println("wav & mp3 player");

	pinMode(PIN_LED0,   OUTPUT);
	pinMode(PIN_SOL,    OUTPUT);
	pinMode(PIN_ESPRST, OUTPUT);

	solOut = LOW;
	digitalWrite(PIN_LED0,   LED_OFF);
	digitalWrite(PIN_SOL,    solOut);
	digitalWrite(PIN_ESPRST, LOW);

	while(!SD.begin())
	{
		Serial.println("Card failed, or not present.");
		digitalWrite(PIN_LED0, LED_OFF);
		delay(1000);
		digitalWrite(PIN_LED0, LED_ON);
	}

	MsTimer2::set(CYCLICINTERVAL, cyclic_handler);
	MsTimer2::start();

	delay(1000);
	solOn = ON;
	wavmp3p.play("start.mp3");
	solOn = OFF;
}

// Play the described mp3/wav files
void loop()
{
	if((cyclicCnt % MININTERVAL) < (MININTERVAL*20/60)) stage = GOOD;
	else if((cyclicCnt % MININTERVAL) < (MININTERVAL*30/60)) stage = TYPICAL;
	else if((cyclicCnt % MININTERVAL) < (MININTERVAL*40/60)) stage = BAD;
	else if((cyclicCnt % MININTERVAL) < (MININTERVAL*60/60)) stage = DANGER;

	// Play
	switch(stage){
		case GOOD: 
			solOn = OFF;
			if((cyclicCnt%(MININTERVAL/6))==0)eyeHappySmall();						//0s
			else if((cyclicCnt%(MININTERVAL/6))==(MININTERVAL*4/60))eyeOff();		//4s
			else if((cyclicCnt%(MININTERVAL/6))==(MININTERVAL*5/60))eyeHappyBig();	//5s
			else if((cyclicCnt%(MININTERVAL/6))==(MININTERVAL*9/60))eyeOff();		//9s
			break;
		case TYPICAL: 
			eyeStandard();
//			if((cyclicCnt%(MININTERVAL/6))==(MININTERVAL*2/60)){
				solOn = ON;
				wavmp3p.play("message.mp3");
				solOn = OFF;
				delay(1000);
//			} 
			break;
		case BAD: 
			eyeBad();
//			if((cyclicCnt%(MININTERVAL/6))==(MININTERVAL*2/60)){
				solOn = ON;
				wavmp3p.play("badair.mp3");
				solOn = OFF;
				delay(1000);
//			}
			break;
		case DANGER: 
			eyeDanger();	
//			if((cyclicCnt%(MININTERVAL/6))==(MININTERVAL*2/60)){
				solOn = ON;
				wavmp3p.play("please.mp3");
				solOn = OFF;
				delay(1000);
//			} else if((cyclicCnt%(MININTERVAL/6))==(MININTERVAL*5/60)){
				solOn = ON;
				wavmp3p.play("kuru.mp3");
				solOn = OFF;
				delay(1000);
//			}
			break;
		default: 
			break;
	}
}

// The below handler enables to skip or stop.
static
void cyclic_handler()
{
    unsigned int ppm = getCO2ppm();
//	Serial.println(ppm);
	
/*	if(ppm < ppmLevel[0]){
	    stage = GOOD;
	} else if(ppm < ppmLevel[1]){
	    stage = TYPICAL;
	} else if(ppm < ppmLevel[2]){
	    stage = BAD;
	} else {
	    stage = DANGER;
	}*/
	
	if(solOn==ON) solOut = ~solOut;
	else solOut = LOW;
	digitalWrite(PIN_SOL, solOut);

    if(cyclicCnt == MININTERVAL) {
    	cyclicCnt = 0;
    	minCnt++;
    } else {
    	cyclicCnt++;
    }
}
