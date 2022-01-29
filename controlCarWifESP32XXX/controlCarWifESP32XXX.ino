#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_PCD8544_84X48_F_4W_SW_SPI u8g2(U8G2_R0,/* clock=*/ 14, /* data=*/ 13, /* cs=*/ 15, /* dc=*/ 27, /* reset=*/ 26);  // Nokia 5110 Display

int bot1;
int bot2;                        

#include <WiFi.h>
#include <MQTT.h>

const char ssid[] = "MOVISTAR_1B18";
const char pass[] = "mariovolvitorojo9940";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;


void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("ControlX", "", "")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

//  client.subscribe("/hello");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  u8g2.begin();
  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("192.168.1.63",1883, net);
  connect();
  
      u8g2.clearBuffer(); 
  u8g2_prepare();
    u8g2.drawStr( 0, 0, "Funciona");
  u8g2.drawStr( 0, 12, "ONLINE");
  u8g2.sendBuffer();
  client.onMessage(messageReceived);
}

void loop() {
//  printX();
  client.loop();
  delay(100);  // <- fixes some issues with WiFi stability
    if (!client.connected()) {
    connect();
  }
    u8g2.clearBuffer(); 
  u8g2_prepare();
    u8g2.drawStr( 0, 0, "Funciona");
  u8g2.drawStr( 0, 12, "ONLINE");
  u8g2.sendBuffer();
  client.onMessage(messageReceived);
}
