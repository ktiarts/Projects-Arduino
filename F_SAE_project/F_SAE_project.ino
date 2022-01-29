// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       F_SAE_project.ino
    Created:	19/05/2018 2:39:27 a. m.
    Author:     THE-BAT\Mario The King
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
#include "DHT.h"	
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

#define DHTPIN 2
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);
void setup()
{
	Serial.begin(9600);
	Wire.begin();
	mpu6050.begin();
	mpu6050.calcGyroOffsets(true);
	dht.begin();
}

// Add the main program code into the continuous loop() function
void loop()
{


}
