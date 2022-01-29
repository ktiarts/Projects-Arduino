#include <Servo.h>
Servo myservo;
#include <Ultrasonic.h>
Ultrasonic ultra(D5,D6);   // (Trig PIN,Echo PIN)
int Medicion=0;
int PWM;
int SER;
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
unsigned long lastMillis = 0;
String PWMx="";
String SERx="";
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
myservo.attach(D1);
pinMode(D2,OUTPUT);
pinMode(D3,OUTPUT);
digitalWrite(D3,HIGH);
inputString.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly:

Deteccion();
serialEvent();
if (stringComplete) {
    Serial.println(inputString);
if (inputString == "beep."){
 Serial.println("recibido");
  Beep();
}
if (inputString == "unbeep."){
 Serial.println("recibido");
  UnBeep();
}
if (inputString.startsWith("F")) {
  PWMx=inputString.substring(1);
 Serial.println("recibido");
 PWM = PWMx.toInt();
  FajaPWM();

}
if (inputString.startsWith("S")) {
  SERx=inputString.substring(1);
 Serial.println("recibido");
 SER = SERx.toInt();
  myservo.write(SER);
}
     // clear the string:
    inputString = "";
    stringComplete = false;
  }
serialEvent();
}
void FajaAvanza(){
  digitalWrite(D2,HIGH);
}
void FajaStop(){
  digitalWrite(D2,LOW);
}
void Deteccion(){
  Medicion=ultra.Ranging(CM);
  String medicion = String(Medicion);
 if (millis() - lastMillis > 100) {
    lastMillis = millis();
    Serial.println(medicion);
  }
}
void Beep(){
  digitalWrite(D3,LOW);
}
void UnBeep(){
  digitalWrite(D3,HIGH);
}
void serialEvent(){
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '.') {
      stringComplete = true;
    }
    
  }
}

void BeepSec(){
  for(int x=590;x<1024;x++){
    Serial.print("Beep = ");
    Serial.println(x);
    analogWrite(D3,x);
    delay(1);
  }
}

void FajaPWM(){
  
    Serial.print("FAJA = ");
    Serial.println(PWM);
    analogWrite(D2,PWM);
}
