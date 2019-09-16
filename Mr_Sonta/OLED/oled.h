/*********************************************************************
This is a library for OLED
*********************************************************************/
#ifndef _OLED_H_
#define _OLED_H_

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306_Wire1.h>
#include <SPI.h>
#include <Wire.h>

#include "happyEyeBmp.h"
#include "badEyeBmp.h"
#include "dangerEyeBmp.h"

#define OLED_RESET 4
//extern Adafruit_SSD1306 display1(OLED_RESET);
//extern Adafruit_SSD1306 display2(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 


static const unsigned char blinkBmp[] =
{ B11110000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111, //0
  B11111110,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B01111111,
  B00011111,B11000000,B00000000,B00000000,B00000000,B00000000,B00000011,B11111000,
  B00000011,B11111000,B00000000,B00000000,B00000000,B00000000,B00011111,B11000000,
  B00000000,B01111111,B00000000,B00000000,B00000000,B00000000,B11111110,B00000000,
  B00000000,B00001111,B11111000,B00000000,B00000000,B00011111,B11110000,B00000000,
  B00000000,B00000001,B11111111,B11100000,B00000111,B11111111,B10000000,B00000000,
  B00000000,B00000000,B00000111,B11111111,B11111111,B11100000,B00000000,B00000000, //7
  B00000000,B00000000,B00000000,B00011111,B11111000,B00000000,B00000000,B00000000  //8
};

static const unsigned char heartBmp[] =
{ B00011111,B00000000,B11111000, //0
  B00111111,B11000011,B11111100,
  B01111111,B11100111,B11111110,
  B01111111,B11111111,B11111110,
  B11111111,B11111111,B11111111,
  B11111111,B11111111,B11111111,
  B11111111,B11111111,B11111111,
  B11111111,B11111111,B11111111, //7
  B01111111,B11111111,B11111110,
  B01111111,B11111111,B11111110,
  B00111111,B11111111,B11111100,
  B00111111,B11111111,B11111100,
  B00011111,B11111111,B11111000,
  B00011111,B11111111,B11111000,
  B00001111,B11111111,B11110000,
  B00000111,B11111111,B11100000, //15
  B00000011,B11111111,B11000000,
  B00000001,B11111111,B10000000,
  B00000000,B11111111,B00000000,
  B00000000,B01111110,B00000000,
  B00000000,B00111100,B00000000,
  B00000000,B00011000,B00000000  //21
};

void initOLED(void);
void eyeClear(void);
void eyeOff(void);
void eyeStandard(void);
void eyeHappySmall(void);
void eyeHappyBig(void);
void eyeBad(void);
void eyeDanger(void);
static void drawBlinkingEye(Adafruit_SSD1306 *display);
static void drawHeartEye(Adafruit_SSD1306 *display);
static void drawHappySmallEye(Adafruit_SSD1306 *display);
static void drawHappyBigEye(Adafruit_SSD1306 *display);
static void drawBadEye(Adafruit_SSD1306 *display);
static void drawDangerEye(Adafruit_SSD1306 *display);

/*
void testdrawchar(void);
void testdrawtriangle(void);
void testfilltriangle(void);
void testdrawroundrect(void);
void testfillroundrect(void);   
void testdrawrect(void);
void testdrawline(void);
void testscrolltext(void);
*/

#endif /* _OLED_H_ */
