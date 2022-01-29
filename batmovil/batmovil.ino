#include "DHT.h"
#define DHTPIN 3 
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);

  pinMode(9, OUTPUT); //Izq1
  pinMode(10, OUTPUT); //Izq 2

  pinMode(11, OUTPUT);  //der 1 
  pinMode(12, OUTPUT);  //der2
  dht.begin();

}/*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
 int aire = analogRead(A0);
 int luz = analogRead(A1);
Serial.print("*a");
Serial.println(aire);
Serial.println("*l");
Serial.println(luz);

 float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
 float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("*H");
  Serial.println(h);
  Serial.print("*T");
  Serial.println(t);
  Serial.print("*R");
  Serial.println(hic);

  if (Serial.available() > 0) {
    char recibir = Serial.read();

if (recibir== 'W'){

  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
}
     
if (recibir== 'S'){

  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
}
if (recibir== 'A'){

  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
    digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
}
if (recibir== 'D'){

  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
   digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
}
if (recibir== 'F'){

  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
   digitalWrite(11,LOW);
  digitalWrite(12,LOW);
}
}
  }

