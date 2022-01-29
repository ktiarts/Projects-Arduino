#include <Time.h>
#include<TimeLib.h>
#include <Servo.h>
#include <TimeAlarms.h>
#include <OneWire.h> //Se importan las librerías
#include <DallasTemperature.h>
#define Pin 2 //Se declara el pin donde se conectará la DATA
 
Servo myservo;  // create servo object to control a servo
  time_t T0 ; 
OneWire ourWire(Pin); //Se establece el pin declarado como bus para la comunicación OneWire
 
DallasTemperature sensors(&ourWire); //Se instancia la librería DallasTemperature
void setup() 
{ 
  Serial.begin(115200);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
sensors.begin();
  myservo.write(90); 
  delay(100);
}

void loop()
{     
sensors.requestTemperatures(); //Prepara el sensor para la lectura
float tempe= sensors.getTempCByIndex(0);
Serial.print(tempe); //Se lee e imprime la temperatura en grados Celsius
Serial.println(" grados Centigrados");

  
  time_t t= now();
   T0 = SetFecha(1970, 1, 21, 0, 0, 0);
  // printFecha(T0) ; 
   
   printFecha(T0 - t);
   Serial.println("--------------------------------");
   time_t H =  T0 - t ;
/*
   Serial.print(String(year(H )- 1970)+" años,"  + String(month(H)-1 )+" meses,");
   Serial.println(String(day(H))+ " dias," + String(hour(H))+ " horas");
   Serial.println("--------------------------------");
*/

if (H >= 345600){
  digitalWrite(3,LOW);
}
  Alarm.timerRepeat(7200, Repeats); 
if (tempe <= 37.8){
  digitalWrite(4,LOW);
}
if (tempe >= 37.8){
  digitalWrite(4,HIGH);
}

}

time_t SetFecha(int y, int m, int d, int h, int mi, int s  )

{  tmElements_t Fecha ;
   Fecha.Second = s;
   Fecha.Minute = mi;
   Fecha.Hour = h;
   Fecha.Day = d ;
   Fecha.Month = m ;
   Fecha.Year = y -1970 ;
   
   return makeTime(Fecha);
 }

void Repeats() {
  myservo.write(90); 
  delay(200);
  myservo.write(40); 
  delay(200);
  myservo.write(90); 
  delay(200);
  myservo.write(130); 
  delay(200);
  myservo.write(90); 
  delay(200);           
}

void printFecha(time_t t)

{ Serial.print(day(t));
  Serial.print(+ "/") ;
  Serial.print(month(t));
  Serial.print(+ "/") ;
  Serial.print(year(t));  
  Serial.print( " ") ;
  Serial.print(hour(t));
  Serial.print(+ ":") ;
  Serial.print(minute(t));
  Serial.print(":") ;
  Serial.println(second(t));
  delay(1);  
}

