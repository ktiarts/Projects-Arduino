#include <Servo.h>

Servo myservo1;
Servo myservo2;
int ejex;
int ejey;
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  myservo1.attach(9);
  myservo2.attach(10);
Serial1.println("inicializado");
pinMode(7,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial1.available() > 0) {
    char recibir = Serial1.read();
  if (recibir== 'A'){
    ejex = Serial1.parseInt();
  Serial.print("x: ");
  Serial.println(ejex);
  myservo1.write(ejex);
  }
  if (recibir== 'B'){
  ejey = Serial1.parseInt();
  Serial.print("y: ");
  Serial.println(ejey);
  myservo2.write(ejey);
  }
  if (recibir== 'C'){
digitalWrite(7,HIGH);
  }
    if (recibir== 'D'){
digitalWrite(7,LOW);
  }
  }
}
