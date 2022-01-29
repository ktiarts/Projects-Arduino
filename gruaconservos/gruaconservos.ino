#include <Servo.h>
Servo servoIzq;
Servo servoDer;
Servo servoBase;
Servo servoBrazo1;
Servo servoBrazo2;
Servo servoGiroPinza;
Servo servoPinza;
int x1;
int x2;
int x3;
int x4;
int x5;
int x6;
int x7;
void setup() {
  // put your setup code here, to run once:
servoIzq.attach(2);
servoDer.attach(3);
servoBase.attach(4);
servoBrazo1.attach(5);
servoBrazo2.attach(6);
servoGiroPinza.attach(7);
servoPinza.attach(8);
pinMode(9,OUTPUT);
Serial.begin(9600);
}

void loop() {
 // put your main code here, to run repeatedly:
char bluetooth1 = Serial.read();
int luz = analogRead(A0);
Serial.print("*A");
Serial.println("Sensor de Luz = ");
Serial.print("*A");
Serial.println(luz);
if ( luz >= 700){
  digitalWrite(9,HIGH);
}
else {
  digitalWrite(9,LOW);  
}

if (bluetooth1 == 'a') {
     x1 = Serial.parseInt();
Serial.println("*B adelante o atras");
  servoIzq.write(x1);
  servoDer.write(x1);
}

if (bluetooth1 == 'b') {
     x1 = Serial.parseInt();
Serial.println("*B izq o der");
  servoIzq.write(x1);
  if ( x1 <90 ){
    x2= x1+90;
  }
  if ( x1 >90 ){
    x2= x1-90;
  }
  servoDer.write(x2);
}
if (bluetooth1 == 'c') {
     x3 = Serial.parseInt();
Serial.println("*B base");
  servoBase.write(x3);
}
if (bluetooth1 == 'd') {
     x4 = Serial.parseInt();
Serial.println("*B Brazo");
  servoBrazo1.write(x4);
}
if (bluetooth1 == 'e') {
     x5 = Serial.parseInt();
Serial.println("*B Muñeca");
  servoBrazo2.write(x5);
}
if (bluetooth1 == 'f') {
     x6 = Serial.parseInt();
Serial.println("*B Giro de Pinza");
  servoGiroPinza.write(x6);
}
if (bluetooth1 == 'g') {
     x7 = Serial.parseInt();
Serial.println("*B Presion de Pinza");
  servoPinza.write(x7);
}



}
