/*********************************************************************
This is a library for MH-Z19, CO2 sensor
*********************************************************************/

#include "mh-z19.h"

void initMHZ19(void){
	SerialCO2.begin(9600);
}

unsigned int getCO2ppm(void){
	unsigned int ppm;
	const byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
	unsigned char response[9]; // for answer
	
	SerialCO2.write(cmd, 9); //request PPM CO2

	for (int i=0; i<9; i++){
		response[i] = SerialCO2.read();
	}
	if ((response[0] != 0xFF) || (response[1] != 0x86)){
		ppm = -1;
	} else {
		unsigned int responseHigh = (unsigned int) response[2];
		unsigned int responseLow = (unsigned int) response[3];
		ppm = (256 * responseHigh) + responseLow;
	}
	
	return ppm;
}


