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
    u8g2.drawStr( 0, 0, "Funciona");
  u8g2.drawStr( 0, 12, "LINE");
  u8g2.sendBuffer();
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  printX();
  client.loop();
  delay(100);  // <- fixes some issues with WiFi stability
    if (!client.connected()) {
    connect();
  }
Serial.print( analogRead(34 ));
Serial.print(" ");
Serial.print( analogRead(35));
Serial.print(" ");
Serial.print( analogRead(32));
Serial.print(" ");
Serial.print(analogRead(25));
Serial.print(" ");
float timon = analogRead(35);
float acel = analogRead(34);
float angulo = ( timon * 0.002442002442 )+10;
float poder = acel * 0.02442002442;
Serial.print(" ");
Serial.print(angulo);
Serial.print(" ");
Serial.print(poder);
Serial.print(" ");
  bot1 = analogRead(32);
  bot2 = analogRead(25);
  String timonx = String(angulo);
  String Acelx = String(poder);
client.publish("/timon", timonx);
client.publish("/Acel", Acelx);
  
if((bot1 > 4000)&&(bot2 > 4000)){
  Serial.print("D");
  client.publish("/modo", "D");
}
if((bot2 > 4000)&&(bot1 < 2)){
  Serial.print("R");
  client.publish("/modo", "R");
}

Serial.println("  ");
}

void printX(){
  u8g2.clearBuffer();
  
  
  u8g2_prepare();
  
  float x1 = analogRead(35);
  float y2 = analogRead(34);

  int x = map (x1,0,4095,0,84);
  int y = map (y2,0,4095,0,84);


  u8g2.drawFrame(0,0,x,10);
  u8g2.drawFrame(0,12,y,10);
  u8g2.drawStr( 0, 0, "Timon");
  u8g2.drawStr( 0, 12, "Acelerador");
  if((bot1 > 4000)&&(bot2 > 4000)){
    u8g2.drawStr( 0, 25, "DOWN");
  }
  if((bot2 > 4000)&&(bot1 < 2)){
    u8g2.drawStr( 0, 25, "UP");
  }
  
  u8g2.sendBuffer();
}
