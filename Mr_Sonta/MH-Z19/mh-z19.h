/*********************************************************************
This is a library for MH-Z19, CO2 sensor
*********************************************************************/
#ifndef _MH_Z19_H_
#define _MH_Z19_H_

#include "Arduino.h"
//#include "Serial.h"
#define SerialCO2 Serial2

extern void initMHZ19(void);
extern unsigned int getCO2ppm(void);

#endif /* _MH-Z19_H_ */
