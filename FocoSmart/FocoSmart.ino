#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX


void setup()   /*----( SETUP: RUNS ONCE )----*/
{
//  mySerial.begin(9600);
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(3, OUTPUT); pinMode(5, OUTPUT);pinMode(6, OUTPUT);pinMode(9, OUTPUT);

}

void loop(){

    if (mySerial.available() > 0) {
    char recibir = mySerial.read();
    switch (recibir){
    case 'r': rojo(); break;
    case 'v': verde(); break;
    case 'a': azul(); break;
    case 'n': negativo(); break;
    
    }
  }
}

void rojo(){ Serial.println("adelante");   int valr = mySerial.parseInt();         analogWrite(3,valr); }
void verde(){ Serial.println("atras");     int valv = mySerial.parseInt();         analogWrite(5,valv); }
void azul(){ Serial.println("izquierda");  int vala = mySerial.parseInt();         analogWrite(6,vala); }
void negativo(){ Serial.println("derecha");int valn = mySerial.parseInt();         analogWrite(9,valn); }


