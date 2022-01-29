/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x32 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/
#if ARDUINO > 10605
#include <Mouse.h>
#endif  //ARDUINO > 10605
#include <MouseTo.h>


#include <MPU6050_tockn.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
MPU6050 mpu6050(Wire);
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
 Mouse.begin();
  MouseTo.setCorrectionFactor(1);
}

void loop() {
  mpu6050.update();
//  Serial.print("angleX : ");
  
//  Serial.print(mpu6050.getAngleX());
//  Serial.print("\tangleY : ");
//  Serial.print(mpu6050.getAngleY());
//  Serial.print("\tangleZ : ");
//  Serial.println(mpu6050.getAngleZ());
int brutox = mpu6050.getAngleX();
int brutoy = mpu6050.getAngleZ();

int ejex = map (brutox,-180,180,0,900);
int ejey = map (brutoy,-180,180,0,900);
MouseTo.setTarget(ejex, ejey);
MouseTo.move(0,0)
Serial.print("ejeX : ");
  Serial.print(ejex);
  Serial.print("  ejeY : ");
  Serial.println(ejey);

  
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.print("X ");
  display.print(mpu6050.getAngleX());
  display.setCursor(10, 10);
 display.print("Y ");
  display.print(mpu6050.getAngleY());
  display.setCursor(10, 20);
  display.print("Z ");
  display.print(mpu6050.getAngleZ());
   display.display();      // Show initial text
  delay(1);


  
}

  
