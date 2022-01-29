#include <Average.h>
int sensorValue1;
int sensorValue2;
int sensorValue3;

#include <SoftwareSerial.h>
#include <Stepper.h>
SoftwareSerial blu(3, 2); // RX, TX
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 4, 6, 5, 7);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
    myStepper.setSpeed(60);
    blu.begin(9600);
    blu.println("hola");


  pinMode(4, OUTPUT); //Izq 1
  pinMode(5, OUTPUT); //Izq 2
  pinMode(6, OUTPUT); //PWM 
  pinMode(7, OUTPUT); //PWM 
  pinMode(13, OUTPUT);//PWM 



}
void loop() {
  // put your main code here, to run repeatedly:
 int minat = 0;
  int maxat = 0;
  Average<float> ave1(100);
  for (int i = 0; i < 100; i++) {
    sensorValue1 = analogRead(A0);
    ave1.push(sensorValue1);
     }
       Average<float> ave2(100);
  for (int i = 0; i < 100; i++) {
    sensorValue2 = analogRead(A1);
    ave2.push(sensorValue2);
     }
       Average<float> ave3(100);
  for (int i = 0; i < 100; i++) {
    sensorValue3 = analogRead(A2);
    ave3.push(sensorValue3);
     }
//  Serial.print("I");
  blu.print("I");
//  Serial.println(ave1.mean()); //media
  blu.println(ave1.mean());
//  Serial.print("R");
  blu.print("R");
//  Serial.println(ave2.mean()); //media
   blu.println(ave2.mean());
//  Serial.print("V");
  blu.print("V");
//  Serial.println(ave3.mean()); //media
   blu.println(ave3.mean());
  delay(500);
if (blu.available() > 0) {
  
  char recibir = blu.read();

  if (recibir == 'A'){  
  blu.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);
  }
if (recibir == 'B'){
  blu.println("anti-clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);
  }

if (recibir == 'p'){
int numero = blu.parseInt();
analogWrite(4,numero);
  blu.println(numero);
}
  
}


}
