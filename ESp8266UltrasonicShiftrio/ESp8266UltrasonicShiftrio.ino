#include "DHT.h"
#define DHTPIN D5     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

#include <Ultrasonic.h>

Ultrasonic ultraleft(D0,D1);   // (Trig PIN,Echo PIN)

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(D3, D4, D5, D7, D6);
#include <ESP8266WiFi.h>
#include <MQTT.h>

const char *ssid = "MOVISTAR_1B18";
const char *pass = "mariovolvitorojo9940";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("Mario", "ESP12345678", "abc12345678")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/hello");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {
  dht.begin();
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);
display.begin();  
display.setContrast(50);
display.clearDisplay();
  connect();
//  
//   display.setTextSize(1);
//  display.setTextColor(BLACK);
//  display.setCursor(0,0);
//  display.println("Hello, world!");
//  display.setTextColor(WHITE, BLACK); // 'inverted' text
//  display.println(3.141592);
//  display.setTextSize(2);
//  display.setTextColor(BLACK);
//  display.print("0x"); display.println(0xDEADBEEF, HEX);
//  display.display();
//  delay(2000);
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
  float h = ultraleft.Ranging(CM);
//  float t = dht.readTemperature();
String hum = String(h);
//String tem = String(t);

   display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Distancia");
  display.setCursor(0,20);
display.print(hum);
display.println(" cm");
display.display();
display.clearDisplay();

client.publish("/sensor1/distance",hum);  
//client.publish("/sensor1/temperatura",tem);
delay(500);
}
