#include <SoftwareSerial.h>
SoftwareSerial Nextion(D6,D7);

int freq=100;
int pwmx=200;

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() {
  // put your setup code here, to run once:
pinMode(D1,OUTPUT);
Serial.begin(115200);
Nextion.begin(9600);
inputString.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly:
analogWriteFreq(freq);
analogWrite(D1,pwmx);

String frecuencia = String(freq);
String pevedobleeme = String(pwmx);


 Nextion.print("t1.txt=\"" + frecuencia + " \"");
 Nextion.write(0xff);
 Nextion.write(0xff);
 Nextion.write(0xff);


 Nextion.print("t3.txt=\"" + pevedobleeme + " \"");
 Nextion.write(0xff);
 Nextion.write(0xff);
 Nextion.write(0xff);

grafica();
Serial.println(analogRead(A0));
entradaNext();
}

void subeFreq(){ freq = freq+10; }
void bajaFreq(){ freq = freq-10; }
void subePWM(){  pwmx = pwmx+10; }
void bajaPWM(){  pwmx = pwmx-10; }

void grafica(){
    int Value = map(analogRead(A0),0,1024,0,255);  //Read the pot value ann map it to 0.255 (max value of waveform=255)
  String Tosend = "add ";                                       //We send the string "add "
  Tosend += 1;                                                  //send the id of the block you want to add the value to
  Tosend += ",";  
  Tosend += 0;                                                  //Channel of taht id, in this case channel 0 of the waveform
  Tosend += ",";
  Tosend += Value;                                              //Send the value and 3 full bytes
  Nextion.print(Tosend);
  Nextion.write(0xff);
  Nextion.write(0xff);
  Nextion.write(0xff);
  //delay(10);
}


void entradaNext(){

    while (Nextion.available()) {
    // get the new byte:
    char inChar = (char)Nextion.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '*') {
      stringComplete = true;
    }
  }
  
if (stringComplete) {
   // Serial.println(inputString);
    
if (inputString.endsWith("frequp*")) {
    subeFreq();
  //  Serial.println(freq);
  }
if (inputString.endsWith("freqdn*")) {
    bajaFreq();
 //   Serial.println(freq);
  }
  if (inputString.endsWith("pwmup*")) {
    subePWM();
  //  Serial.println(pwmx);
  }
  if (inputString.endsWith("pwmdn*")) {
    bajaPWM();
   // Serial.println(pwmx);
  }

    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  
}
