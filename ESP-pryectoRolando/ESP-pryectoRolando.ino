#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#include <WiFi.h>
#include <MQTT.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
//#define BUTTON_PIN_BITMASK 0x9C00000000
WiFiClient net;
MQTTClient client;
 #define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 60        /* Time ESP32 will go to sleep (in seconds) */
RTC_DATA_ATTR int bootCount = 0;

unsigned long lastMillis = 0;

int sw1,sw2,sw3,sw4,sw5,sw6,sw7,sw8;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(10);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("ESPx", "LeMicro", "")) {
    Serial.print(".");
    delay(10);
  }

  Serial.println("\nconnected!");

  client.subscribe("/hello");
  // client.unsubscribe("/hello");
}

//void messageReceived(String &topic, String &payload) {
//  Serial.println("incoming: " + topic + " - " + payload);
//}

void setup() {
  WiFi.setTxPower(WIFI_POWER_2dBm);
  Serial.begin(115200);
WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
  pinMode(36,INPUT);
  pinMode(39,INPUT);
  pinMode(34,INPUT);
  pinMode(35,INPUT);

    wifiMulti.addAP("MOVISTAR_1B18", "mariovolvitorojo9940");
    wifiMulti.addAP("yTEZLA", "TEZLITA");
    wifiMulti.addAP("LeBigMac", "CuartoDeLibra321");

    Serial.println("Connecting Wifi...");
    if(wifiMulti.run() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
  
//  WiFi.begin(ssid, pass);
//  client.onMessage(messageReceived);
    
  client.begin("192.168.1.11", net);
  connect();

    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");
}

void loop() {
  
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
   if(wifiMulti.run() != WL_CONNECTED) {
        Serial.println("WiFi not connected!");
        delay(10);
    }
Serial.print("sw1 = ");Serial.println(digitalRead(22));
Serial.print("sw2 = ");Serial.println(digitalRead(21));
Serial.print("sw3 = ");Serial.println(digitalRead(19));
Serial.print("sw4 = ");Serial.println(digitalRead(18));
Serial.print("sw5 = ");Serial.println(digitalRead(5));
Serial.print("sw6 = ");Serial.println(digitalRead(17));
Serial.print("sw7 = ");Serial.println(digitalRead(16));
Serial.print("sw8 = ");Serial.println(digitalRead(4));

sw1 = digitalRead(22);
sw2 = digitalRead(21);
sw3 = digitalRead(19);
sw4 = digitalRead(18);
sw5 = digitalRead(5);
sw6 = digitalRead(17);
sw7 = digitalRead(16);
sw8 = digitalRead(4);


//--------------------------------------1---------------------------------------------------
if((sw1==0)&&(sw2==0)&&(sw3==0)&&(sw4==0)){
if (digitalRead(36) == 1) {client.publish("/home", "1a");Serial.println("1a");delay(100);  }
if (digitalRead(36) == 0) {client.publish("/home", "1b");Serial.println("1b");delay(100);  }
if (digitalRead(39) == 1) {client.publish("/home", "2a");Serial.println("2a");delay(100);  }
if (digitalRead(39) == 0) {client.publish("/home", "2b");Serial.println("2b");delay(100);  }
if (digitalRead(34) == 1) {client.publish("/home", "3a");Serial.println("3a");delay(100);  }
if (digitalRead(34) == 0) {client.publish("/home", "3b");Serial.println("3b");delay(100);  }
if (digitalRead(35) == 1) {client.publish("/home", "4a");Serial.println("4a");delay(100);  }
if (digitalRead(35) == 0) {client.publish("/home", "4b");Serial.println("4b");delay(100);  }
}
//--------------------------------------1---------------------------------------------------

//--------------------------------------2---------------------------------------------------
if((sw1==1)&&(sw2==0)&&(sw3==0)&&(sw4==0)){
if (digitalRead(36) == 1) {client.publish("/home", "5a");Serial.println("5a");delay(100);  }
if (digitalRead(36) == 0) {client.publish("/home", "5b");Serial.println("5b");delay(100);  }
if (digitalRead(39) == 1) {client.publish("/home", "6a");Serial.println("6a");delay(100);  }
if (digitalRead(39) == 0) {client.publish("/home", "6b");Serial.println("6b");delay(100);  }
if (digitalRead(34) == 1) {client.publish("/home", "7a");Serial.println("7a");delay(100);  }
if (digitalRead(34) == 0) {client.publish("/home", "7b");Serial.println("7b");delay(100);  }
if (digitalRead(35) == 1) {client.publish("/home", "8a");Serial.println("8a");delay(100);  }
if (digitalRead(35) == 0) {client.publish("/home", "8b");Serial.println("8b");delay(100);  }
}
//--------------------------------------2---------------------------------------------------

//--------------------------------------3---------------------------------------------------
if((sw1==0)&&(sw2==1)&&(sw3==0)&&(sw4==0)){
if (digitalRead(36) == 1) {client.publish("/home", "9a");Serial.println("9a");delay(100);  }
if (digitalRead(36) == 0) {client.publish("/home", "9b");Serial.println("9b");delay(100);  }
if (digitalRead(39) == 1) {client.publish("/home", "10a");Serial.println("10a");delay(100);  }
if (digitalRead(39) == 0) {client.publish("/home", "10b");Serial.println("10b");delay(100);  }
if (digitalRead(34) == 1) {client.publish("/home", "11a");Serial.println("11a");delay(100);  }
if (digitalRead(34) == 0) {client.publish("/home", "11b");Serial.println("11b");delay(100);  }
if (digitalRead(35) == 1) {client.publish("/home", "12a");Serial.println("12a");delay(100);  }
if (digitalRead(35) == 0) {client.publish("/home", "12b");Serial.println("12b");delay(100);  }
}
//--------------------------------------3---------------------------------------------------

//--------------------------------------4---------------------------------------------------
if((sw1==1)&&(sw2==1)&&(sw3==0)&&(sw4==0)){
if (digitalRead(36) == 1) {client.publish("/home", "13a");Serial.println("13a");delay(100);  }
if (digitalRead(36) == 0) {client.publish("/home", "13b");Serial.println("13b");delay(100);  }
if (digitalRead(39) == 1) {client.publish("/home", "14a");Serial.println("14a");delay(100);  }
if (digitalRead(39) == 0) {client.publish("/home", "14b");Serial.println("14b");delay(100);  }
if (digitalRead(34) == 1) {client.publish("/home", "15a");Serial.println("15a");delay(100);  }
if (digitalRead(34) == 0) {client.publish("/home", "15b");Serial.println("15b");delay(100);  }
if (digitalRead(35) == 1) {client.publish("/home", "16a");Serial.println("16a");delay(100);  }
if (digitalRead(35) == 0) {client.publish("/home", "16b");Serial.println("16b");delay(100);  }
}
//--------------------------------------4---------------------------------------------------

//--------------------------------------5---------------------------------------------------
if((sw1==0)&&(sw2==0)&&(sw3==1)&&(sw4==0)){
if (digitalRead(36) == 1) {client.publish("/home", "17a");Serial.println("17a");delay(100);  }
if (digitalRead(36) == 0) {client.publish("/home", "17b");Serial.println("17b");delay(100);  }
if (digitalRead(39) == 1) {client.publish("/home", "18a");Serial.println("18a");delay(100);  }
if (digitalRead(39) == 0) {client.publish("/home", "18b");Serial.println("18b");delay(100);  }
if (digitalRead(34) == 1) {client.publish("/home", "19a");Serial.println("19a");delay(100);  }
if (digitalRead(34) == 0) {client.publish("/home", "19b");Serial.println("19b");delay(100);  }
if (digitalRead(35) == 1) {client.publish("/home", "20a");Serial.println("20a");delay(100);  }
if (digitalRead(35) == 0) {client.publish("/home", "20b");Serial.println("20b");delay(100);  }
}
//--------------------------------------5---------------------------------------------------

//--------------------------------------6---------------------------------------------------
if((sw1==1)&&(sw2==0)&&(sw3==1)&&(sw4==0)){
if (digitalRead(36) == 1) {client.publish("/home", "21a");Serial.println("21a");delay(100);  }
if (digitalRead(36) == 0) {client.publish("/home", "21b");Serial.println("21b");delay(100);  }
if (digitalRead(39) == 1) {client.publish("/home", "22a");Serial.println("22a");delay(100);  }
if (digitalRead(39) == 0) {client.publish("/home", "22b");Serial.println("22b");delay(100);  }
if (digitalRead(34) == 1) {client.publish("/home", "23a");Serial.println("23a");delay(100);  }
if (digitalRead(34) == 0) {client.publish("/home", "23b");Serial.println("23b");delay(100);  }
if (digitalRead(35) == 1) {client.publish("/home", "24a");Serial.println("24a");delay(100);  }
if (digitalRead(35) == 0) {client.publish("/home", "24b");Serial.println("24b");delay(100);  }
}
//--------------------------------------6---------------------------------------------------

//--------------------------------------7---------------------------------------------------
if((sw1==0)&&(sw2==1)&&(sw3==1)&&(sw4==0)){
if (digitalRead(36) == 1) {client.publish("/home", "25a");Serial.println("25a");delay(100);  }
if (digitalRead(36) == 0) {client.publish("/home", "25b");Serial.println("25b");delay(100);  }
if (digitalRead(39) == 1) {client.publish("/home", "26a");Serial.println("26a");delay(100);  }
if (digitalRead(39) == 0) {client.publish("/home", "26b");Serial.println("26b");delay(100);  }
if (digitalRead(34) == 1) {client.publish("/home", "27a");Serial.println("27a");delay(100);  }
if (digitalRead(34) == 0) {client.publish("/home", "27b");Serial.println("27b");delay(100);  }
if (digitalRead(35) == 1) {client.publish("/home", "28a");Serial.println("28a");delay(100);  }
if (digitalRead(35) == 0) {client.publish("/home", "28b");Serial.println("28b");delay(100);  }
}
//--------------------------------------7---------------------------------------------------

//--------------------------------------8---------------------------------------------------
if((sw1==1)&&(sw2==1)&&(sw3==1)&&(sw4==0)){
if (digitalRead(36) == 1) {client.publish("/home", "29a");Serial.println("29a");delay(100);  }
if (digitalRead(36) == 0) {client.publish("/home", "29b");Serial.println("29b");delay(100);  }
if (digitalRead(39) == 1) {client.publish("/home", "30a");Serial.println("30a");delay(100);  }
if (digitalRead(39) == 0) {client.publish("/home", "30b");Serial.println("30b");delay(100);  }
if (digitalRead(34) == 1) {client.publish("/home", "31a");Serial.println("31a");delay(100);  }
if (digitalRead(34) == 0) {client.publish("/home", "31b");Serial.println("31b");delay(100);  }
if (digitalRead(35) == 1) {client.publish("/home", "32a");Serial.println("32a");delay(100);  }
if (digitalRead(35) == 0) {client.publish("/home", "32b");Serial.println("32b");delay(100);  }
}
//--------------------------------------8---------------------------------------------------

//--------------------------------------9---------------------------------------------------
if((sw1==0)&&(sw2==0)&&(sw3==0)&&(sw4==1)){
if (digitalRead(36) == 1) {client.publish("/home", "33a");Serial.println("33a");delay(100);  }
if (digitalRead(36) == 0) {client.publish("/home", "33b");Serial.println("33b");delay(100);  }
}
//--------------------------------------9---------------------------------------------------
  
  Serial.println("bais");
  
  esp_wifi_stop(); 
  esp_deep_sleep_start();
}
