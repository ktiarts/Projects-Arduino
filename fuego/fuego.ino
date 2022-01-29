#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
float h = dht.readHumidity();
float t = dht.readTemperature();
Serial.print("Humedad= ");
Serial.print(h);
Serial.print("   ");
Serial.print("Temperatura= ");
Serial.println(t);
int converter = map(h,70,100,0,255);
analogWrite(5,converter);
if(t >= 23){
  digitalWrite(6,HIGH);
}
if(t <=23){
digitalWrite(6,LOW);
  
}
}
