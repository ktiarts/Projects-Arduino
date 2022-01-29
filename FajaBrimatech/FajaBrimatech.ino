#include <Ultrasonic.h>
Ultrasonic ultra(D5,D6);   // (Trig PIN,Echo PIN)
int Medicion=0;
#include <ESP8266WiFi.h>
#include <MQTT.h>

const char ssid[] = "MOVISTAR_1B18";
const char pass[] = "mariovolvitorojo9940";

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
  while (!client.connect("ESPFaja", "", "")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/Faja");
  client.subscribe("/Beeper");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

if (topic == "/Faja"){
int pwmx = payload.toInt();
analogWrite(D2,pwmx);
  
  if (payload == "GO"){FajaAvanza();Serial.println("Avanaza");}

  if (payload == "STOP"){FajaStop();}
}

if (topic == "/Beeper"){
  if (payload == "Beep"){Beep();Serial.println("BEEPS");}
  if (payload == "UnBeep"){UnBeep();}
}

}

void setup() {
  Serial.begin(115200);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  WiFi.begin(ssid, pass);
  digitalWrite(D3,HIGH);
  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("192.168.43.108", net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
Deteccion();

}


void FajaAvanza(){
  digitalWrite(D2,HIGH);
}
void FajaStop(){
  digitalWrite(D2,LOW);
}
void Deteccion(){
  Medicion=ultra.Ranging(CM);
  String medicion = String(Medicion);
  //client.publish("/ultrasonido", medicion);
  Serial.println(medicion);
 if (millis() - lastMillis > 300) {
    lastMillis = millis();
    client.publish("/ultrasonido", medicion);
  }
}
void Beep(){
  digitalWrite(D3,LOW);
}
void UnBeep(){
  digitalWrite(D3,HIGH);
}

  
   


  
