/*********************************************************************
This is a library for OLED
*********************************************************************/

#include "oled.h"

Adafruit_SSD1306 display1(OLED_RESET);
Adafruit_SSD1306 display2(OLED_RESET);


//#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
//#endif

void initOLED()   {                
  display1.begin(SSD1306_SWITCHCAPVCC, 0x3C, true);  // initialize with the I2C addr 0x3C (for the 128x64)
  display2.begin(SSD1306_SWITCHCAPVCC, 0x3D, true);  // initialize with the I2C addr 0x3D (for the 128x64)

  // Clear the buffer.
  eyeClear();
  eyeStandard();
}

void eyeClear(void) {
  display1.clearDisplay();
  display2.clearDisplay();
}

void eyeOff(void) {
  display1.clearDisplay();
  display2.clearDisplay();
  display1.display();
  display2.display();
}

void eyeStandard(void) {
/*  display1.fillRect(display1.width()/2+20, display1.height()/2-25, 40, 40, WHITE);
  display1.display();
  display2.fillRect(display2.width()/2-20-40, display2.height()/2-25, 40, 40, WHITE);
  display2.display();*/

  eyeClear();
  display1.fillCircle(display1.width()/2+30, display1.height()/2-5, 22, WHITE);
  display1.display();
  display2.fillCircle(display2.width()/2-30, display2.height()/2-5, 22, WHITE);
  display2.display();
  
/*  display1.fillCircle(display1.width()/2, display1.height()/2, 26, WHITE);
  display1.fillCircle(display1.width()/2-15, display1.height()/2, 10, BLACK);
  display1.display();
  display2.fillCircle(display2.width()/2, display2.height()/2, 26, WHITE);
  display2.fillCircle(display2.width()/2+15, display2.height()/2, 10, BLACK);
  display2.display();*/
}

void eyeHappySmall(void) {
  eyeClear();
  drawHappySmallEye(&display1);
  display1.display();
  drawHappySmallEye(&display2);
  display2.display();
}

void eyeHappyBig(void) {
  eyeClear();
  drawHappyBigEye(&display1);
  display1.display();
  drawHappyBigEye(&display2);
  display2.display();
}

void eyeBad(void) {
  eyeClear();
  drawBadEye(&display1);
  display1.display();
  drawBadEye(&display2);
  display2.display();
}

void eyeDanger(void) {
  eyeClear();
  drawDangerEye(&display1);
  display1.display();
  drawDangerEye(&display2);
  display2.display();
}

static void drawBlinkingEye(Adafruit_SSD1306 *display){
  display->drawBitmap(32, 32, blinkBmp, 64, 9, WHITE);
}

static void drawHeartEye(Adafruit_SSD1306 *display){
  display->fillCircle(display1.width()/2, display1.height()/2, 26, WHITE);
  display->drawBitmap(display->width()/2-12, display->height()/2-11, heartBmp, 24, 22, BLACK);
}

static void drawHappySmallEye(Adafruit_SSD1306 *display){
  display->drawBitmap(31, 8, happySmallEyeBmp, HAPPYSMALL_EYE_BMP_W, HAPPYSMALL_EYE_BMP_H, WHITE);
}

static void drawHappyBigEye(Adafruit_SSD1306 *display){
  display->drawBitmap(15, 0, happyBigEyeBmp, HAPPYBIG_EYE_BMP_W, HAPPYBIG_EYE_BMP_H, WHITE);
}

static void drawBadEye(Adafruit_SSD1306 *display){
  display->drawBitmap(15, 16, badEyeBmp, BAD_EYE_BMP_W, BAD_EYE_BMP_H, WHITE);
}

static void drawDangerEye(Adafruit_SSD1306 *display){
  display->drawBitmap(4, 5, dangerEyeBmp, DANGER_EYE_BMP_W, DANGER_EYE_BMP_H, WHITE);
}

/*
void testdrawchar(void) {
  display1.setTextSize(1);
  display1.setTextColor(WHITE);
  display1.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display1.write(i);
    if ((i > 0) && (i % 21 == 0))
      display1.println();
  }    
  display1.display();
  delay(1);
}


void testdrawtriangle(void) {
  for (int16_t i=0; i<min(display1.width(),display1.height())/2; i+=5) {
    display1.drawTriangle(display1.width()/2, display1.height()/2-i,
                     display1.width()/2-i, display1.height()/2+i,
                     display1.width()/2+i, display1.height()/2+i, WHITE);
    display1.display();
    delay(1);
  }
}

void testfilltriangle(void) {
  uint8_t color = WHITE;
  for (int16_t i=min(display1.width(),display1.height())/2; i>0; i-=5) {
    display1.fillTriangle(display1.width()/2, display1.height()/2-i,
                     display1.width()/2-i, display1.height()/2+i,
                     display1.width()/2+i, display1.height()/2+i, WHITE);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display1.display();
    delay(1);
  }
}

void testdrawroundrect(void) {
  for (int16_t i=0; i<display1.height()/2-2; i+=2) {
    display1.drawRoundRect(i, i, display1.width()-2*i, display1.height()-2*i, display1.height()/4, WHITE);
    display1.display();
    delay(1);
  }
}

void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i=0; i<display1.height()/2-2; i+=2) {
    display1.fillRoundRect(i, i, display1.width()-2*i, display1.height()-2*i, display1.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display1.display();
    delay(1);
  }
}
   
void testdrawrect(void) {
  for (int16_t i=0; i<display1.height()/2; i+=2) {
    display1.drawRect(i, i, display1.width()-2*i, display1.height()-2*i, WHITE);
    display1.display();
    delay(1);
  }
}

void testdrawline() {  
  for (int16_t i=0; i<display1.width(); i+=4) {
    display1.drawLine(0, 0, i, display1.height()-1, WHITE);
    display1.display();
    delay(1);
  }
  for (int16_t i=0; i<display1.height(); i+=4) {
    display1.drawLine(0, 0, display1.width()-1, i, WHITE);
    display1.display();
    delay(1);
  }
  delay(250);
  
  display1.clearDisplay();
  for (int16_t i=0; i<display1.width(); i+=4) {
    display1.drawLine(0, display1.height()-1, i, 0, WHITE);
    display1.display();
    delay(1);
  }
  for (int16_t i=display1.height()-1; i>=0; i-=4) {
    display1.drawLine(0, display1.height()-1, display1.width()-1, i, WHITE);
    display1.display();
    delay(1);
  }
  delay(250);
  
  display1.clearDisplay();
  for (int16_t i=display1.width()-1; i>=0; i-=4) {
    display1.drawLine(display1.width()-1, display1.height()-1, i, 0, WHITE);
    display1.display();
    delay(1);
  }
  for (int16_t i=display1.height()-1; i>=0; i-=4) {
    display1.drawLine(display1.width()-1, display1.height()-1, 0, i, WHITE);
    display1.display();
    delay(1);
  }
  delay(250);

  display1.clearDisplay();
  for (int16_t i=0; i<display1.height(); i+=4) {
    display1.drawLine(display1.width()-1, 0, 0, i, WHITE);
    display1.display();
    delay(1);
  }
  for (int16_t i=0; i<display1.width(); i+=4) {
    display1.drawLine(display1.width()-1, 0, i, display1.height()-1, WHITE); 
    display1.display();
    delay(1);
  }
  delay(250);
}

void testscrolltext(void) {
  display1.setTextSize(2);
  display1.setTextColor(WHITE);
  display1.setCursor(10,0);
  display1.clearDisplay();
  display1.println("scroll");
  display1.display();
  delay(1);
 
  display1.startscrollright(0x00, 0x0F);
  delay(2000);
  display1.stopscroll();
  delay(1000);
  display1.startscrollleft(0x00, 0x0F);
  delay(2000);
  display1.stopscroll();
  delay(1000);    
  display1.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display1.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display1.stopscroll();
}*/

