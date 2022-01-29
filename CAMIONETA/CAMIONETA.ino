#include <SoftwareSerial.h>
SoftwareSerial mySerial(6, 7); // RX, TX

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
//  mySerial.begin(9600);
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(2, OUTPUT); pinMode(3, OUTPUT);pinMode(4, OUTPUT);pinMode(5, OUTPUT);

}

void loop(){

    if (mySerial.available() > 0) {
    char recibir = mySerial.read();
    switch (recibir){
    case 'w': adelante(); break;
    case 's': atras(); break;
    case 'a': izquierda(); break;
    case 'd': derecha(); break;
    case 'x': parada(); break;
    }
  }
}

void adelante(){ Serial.println("adelante"); digitalWrite(2, 1);digitalWrite(3, 0);digitalWrite(4, 1);digitalWrite(5, 0); }
void atras(){ Serial.println("atras");       digitalWrite(2, 0);digitalWrite(3, 1);digitalWrite(4, 0);digitalWrite(5, 1); }
void izquierda(){ Serial.println("izquierda");    digitalWrite(2, 1);digitalWrite(3, 0);digitalWrite(4, 0);digitalWrite(5, 1); }
void derecha(){ Serial.println("derecha");      digitalWrite(2, 0);digitalWrite(3, 1);digitalWrite(4, 1);digitalWrite(5, 0); }
void parada(){ Serial.println("stop");       digitalWrite(2, 0);digitalWrite(3, 0);digitalWrite(4, 0);digitalWrite(5, 0); } 



