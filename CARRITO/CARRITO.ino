// This example uses an Adafruit Huzzah ESP8266
// to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

#include <ESP8266WiFi.h>
#include <MQTT.h>
#include <Servo.h>

const char ssid[] = "MOVISTAR_1B18";
const char pass[] = "mariovolvitorojo9940";
Servo timon;
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
  while (!client.connect("car", "", "")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/carro");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
int pos1 = payload.lastIndexOf('a');
    if (pos1 == 0){
    String numberxy = payload.substring(1); 
    int xnumber = numberxy.toInt(); 
    timon.write(xnumber);
    Serial.println("NUMERO DE PWM"); 
    Serial.println(xnumber);
    }

    int pos2 = payload.lastIndexOf('b');
    if (pos2 == 0){
    String numberxy = payload.substring(1); 
    int xnumber = numberxy.toInt(); 
    acelera(xnumber);
    Serial.println("NUMERO DE Aceleracion"); 
    Serial.println(xnumber);
    }
    int pos3 = payload.lastIndexOf('c');
    if (pos3 == 0){
    String numberxy = payload.substring(1); 
    int xnumber = numberxy.toInt(); 
    retrocede(xnumber);
    Serial.println("NUMERO DE Retrocede"); 
    Serial.println(xnumber);
    }
    int pos4 = payload.lastIndexOf('d');
    if (pos4 == 0){
    frena();
    Serial.println("Frena WN");
    }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("192.168.1.61",1883, net);
  client.onMessage(messageReceived);

  connect();
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
//  pinMode(D6,OUTPUT);
  timon.attach(D6);
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability
  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    client.publish("/hello", "world");
  }
}
void acelera(int valuex){
  analogWrite(D1,valuex);
  analogWrite(D2,0);
  analogWrite(D3,valuex);
  analogWrite(D4,0);
  }
void frena(){
  analogWrite(D1,0);
  analogWrite(D2,0);
  analogWrite(D3,0);
  analogWrite(D4,0);
  }
void retrocede(int valuex){
  analogWrite(D1,0);
  analogWrite(D2,valuex);
  analogWrite(D3,0);
  analogWrite(D4,valuex);
  }
