#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial mySerial(6, 7); // RX, TX
Servo myservo1;
Servo myservo2;
  
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(2, OUTPUT); pinMode(3, OUTPUT);
  myservo1.attach(4); myservo2.attach(5);
}

void loop(){

    if (mySerial.available() > 0) {
    char recibir = mySerial.read();
    switch (recibir){
    case 'A': Led1On(); break;
    case 'B': Led2On(); break;
    case 'C': Led1Off(); break;
    case 'D': Led2Off(); break;
    case 'E': Puerta1On(); break;
    case 'F': Puerta1Off(); break;
    }
  }
}

void Led1On(){ Serial.println("Led 1 ON"); digitalWrite(2, 1); }
void Led2On(){ Serial.println("Led 2 ON");       digitalWrite(3, 1); }
void Led1Off(){ Serial.println("Led 1 OFF");    digitalWrite(2, 0); }
void Led2Off(){ Serial.println("Led 2 OFF");      digitalWrite(3, 0); }
void Puerta1On(){ Serial.println("Puerta 1 Abierto");  myservo1.write(90); myservo2.write(90); } 
void Puerta1Off(){ Serial.println("Puerta 1 Cerrado"); myservo1.write(0); myservo2.write(0); } 



