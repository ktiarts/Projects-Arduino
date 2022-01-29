#include "DHT.h"
#define DHTPIN 3 
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
void setup() {
  Serial.begin(9600);
    mySerial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
}

void loop() {
  delay(100);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("H");
  Serial.print(h);
  Serial.print("T");
  Serial.print(t);
  Serial.print("R");
  Serial.println(hic);
  
  mySerial.print("*H");
  mySerial.print(h);
  mySerial.print("*T");
  mySerial.print(t);
  mySerial.print("*R");
  mySerial.println(hic);
}
