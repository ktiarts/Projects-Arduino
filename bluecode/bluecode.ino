#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <MQTTClient.h>
SoftwareSerial mySerial(D5, D6); // RX, TX
const char ssid[] = "ssid";
const char pass[] = "pass";
WiFiClient net;
MQTTClient client;
unsigned long lastMillis = 0;
void connect();  // <- predefine connect() for setup()

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 WiFi.begin(ssid, pass);
 pinMode(D2,OUTPUT);// relay 1 
 pinMode(D3,OUTPUT);// relay 2 
 pinMode(D4,OUTPUT);//RELAY 3
 client.begin("broker.shiftr.io", net);
 
digitalWrite(D2,HIGH);
digitalWrite(D3,HIGH);
digitalWrite(D4,HIGH);
  connect();
}
void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
Serial.print("\nconnecting...");
  while (!client.connect("arduino", "try", "try")) {
    Serial.print(".");
    delay(1000);
    if (Serial.available() > 0) {
   char x=mySerial.read();

  if (x=='R'){
    digitalWrite(D2,HIGH);
  }
   if (x=='r'){
    digitalWrite(D2,LOW);
    
  }
    if (x=='Y'){
    digitalWrite(D3,HIGH);
  }
   if (x=='y'){
    digitalWrite(D3,LOW);
    
  }
    if (x=='B'){
    digitalWrite(D4,HIGH);
  }
   if (x=='b'){
    digitalWrite(D4,LOW);
  }

}
  }
}
    /*if ( Serial available()> 0){
    char recibir = Serial.read();
  }
  Serial.println("\nconnected!");
 client.subscribe("/hello");
  // client.unsubscribe("/hello");
}*/
void loop() {
  char x=mySerial.read();
  if (x=='R'){
    digitalWrite(D2,HIGH);
  }
   if (x=='r'){
    digitalWrite(D2,LOW);
    
  }
    if (x=='Y'){
    digitalWrite(D3,HIGH);
  }
   if (x=='y'){
    digitalWrite(D3,LOW);
    
  }
    if (x=='B'){
    digitalWrite(D4,HIGH);
  }
   if (x=='b'){
    digitalWrite(D4,LOW);
  }
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability
  if (!client.connected()) {
    connect();
  } 
}
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.println("incoming: " + topic + " - " + payload);
 if (payload.startsWith("A", 0)) {
  digitalWrite(D2,LOW);
  delay(500); 
  } 
 if (payload.startsWith("B", 0)) {
  digitalWrite(D3,HIGH);
  delay(500); 
  }
  if (payload.startsWith("C", 0)) {
  digitalWrite(D4,HIGH);
  delay(500); 
  }
}
