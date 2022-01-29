#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

void setup()   /*----( SETUP: RUNS ONCE )----*/
{

  Serial.begin(9600);
  mySerial.begin(9600);
  myservo1.attach(3);
  myservo2.attach(4);
  myservo3.attach(5);
  myservo4.attach(6);
myservo1.write(90);
myservo2.write(90);
myservo3.write(90);
myservo4.write(90);
delay(100);
}

void loop(){

    if (mySerial.available() > 0) {
    char recibir = mySerial.read();

    switch (recibir){
    case 'r': pinza(); break;
    case 'v': brazo(); break;
    case 'x': brazo1(); break;
    case 'a': base(); break;

    }
    }
  }


void pinza(){ int valr = mySerial.parseInt();         myservo1.write(valr); delay(15);  }
void brazo(){ int valv = mySerial.parseInt();         myservo2.write(valv); delay(15); }
void brazo1(){ int valx = mySerial.parseInt();         myservo3.write(valx); delay(15); }
void base(){  int vala = mySerial.parseInt();         myservo4.write(vala);delay(15); }



