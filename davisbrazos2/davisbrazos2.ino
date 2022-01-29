/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;

int val1;
int val2;
int val3;
int val4;
int val5;
int val6;

int valx1;
int valx2;
int valx3;
int valx4;
int valx5;
int valx6;

void setup() {
  
  Serial.begin(115200); 
  myservo1.attach(2);
  myservo2.attach(3);
  myservo3.attach(4);
  myservo4.attach(5);
  myservo5.attach(6);
  myservo6.attach(7);

}

void loop() {


  val1 = analogRead(A0);
  val2 = analogRead(A1);
  val3 = analogRead(A2);
  val4 = analogRead(A3);
  val5 = analogRead(A4);
  val6 = analogRead(A5);

  valx1 = map(val4, 0, 1023, 0, 180);
  valx2 = map(val4, 0, 1023, 180, 0);
  valx3 = map(val6, 0, 1023, 180, 0);
  valx4 = map(val4, 0, 1023, 0, 180);
  valx5 = map(val5, 0, 1023, 0, 180);
  valx6 = map(val6, 0, 1023, 0, 180);

  Serial.print(valx1);
  Serial.print("  ");
  Serial.print(valx2);
  Serial.print("  ");
  Serial.print(valx3);
  Serial.print("  ");
  Serial.print(valx4);
  Serial.print("  ");
  Serial.print(valx5);
  Serial.print("  ");
  Serial.print(valx6);
  Serial.println("  ");

  myservo1.write(valx1);
  myservo2.write(valx2);
  myservo3.write(valx3);
  myservo4.write(valx4);
  myservo5.write(valx5);
  myservo6.write(valx6);

  delay(100);
}

