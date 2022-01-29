#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     D4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include "DHT.h" //**
#define DHTPIN D5 //**
#define DHTTYPE DHT11 //**   // DHT 11
DHT dht(DHTPIN, DHTTYPE); // **

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  dht.begin();
  display.display();
  delay(2000); // Pause for 2 seconds
}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String hum = String(h);
  String tem = String(t);
  // put your main code here, to run repeatedly:
display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.println("Bbcita");
  display.setCursor(10, 10);
  display.println("BBbrrrr!!");
  display.setCursor(10, 20);
  display.println(":v");
  display.setCursor(80, 20);
  display.println("");
  display.display();      // Show initial text
  delay(100);
}
