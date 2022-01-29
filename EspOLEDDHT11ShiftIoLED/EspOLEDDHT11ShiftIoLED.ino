
#include <ESP8266WiFi.h>
#include <MQTT.h>

const char *ssid = "LABOTEC2.4";
const char *pass = "12345678";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;



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


    int x=payload.toInt();
    analogWrite(D6,x);
    Serial.println(x);
  
}





void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
  WiFi.begin(ssid, pass);
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  dht.begin();
  display.display();
  delay(2000); // Pause for 2 seconds


connect();
  pinMode(D6,OUTPUT);
}

void loop() {
  client.loop();
  delay(10); 

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String hum = String(h);
  String tem = String(t);
client.publish("/sensor1/humedad",hum); 
client.publish("/sensor1/temperatura",tem); 

  
  // put your main code here, to run repeatedly:
display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.println("Humedad");
  display.setCursor(10, 10);
  display.println(hum);
  display.setCursor(10, 20);
  display.println("Temperatura");
  display.setCursor(80, 20);
  display.println(tem);
  display.display();      // Show initial text
  delay(100);
}
