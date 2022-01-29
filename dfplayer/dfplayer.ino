#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
//Pulsadores
const int s1 = 2; // pulsadores
const int s2 = 3;
const int led = 13; // led
int state1 = 0; // estados para las entradas digitales
int last1 = 1;
int state2 = 0;
int last2 = 1;
SoftwareSerial mySoftwareSerial(7, 8); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
String stringOne="";
int contadori;

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
       //  audiofile  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34
int MamaniAudios[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //segun array     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 

int vtime = 3000;
void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  inputString.reserve(200);
//  Serial.println();
//  Serial.println(F("DFRobot DFPlayer Mini Demo"));
//  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
//    Serial.println(F("Unable to begin:"));
//    Serial.println(F("1.Please recheck the connection!"));
//    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
//  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  //----Set volume----
  myDFPlayer.volume(30);  //Set volume value (0~30).
  //myDFPlayer.volumeUp(); //Volume Up
  //myDFPlayer.volumeDown(); //Volume Down
  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  //----Set device we use SD as default----
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  pinMode(s1, INPUT_PULLUP);
  pinMode(s2, INPUT_PULLUP);
  pinMode(led, OUTPUT);

delay(240000);
  
  Serial.println("confirma");
}
void loop()
{
  contadori=0;
  
if (stringComplete) {
//    Serial.println(inputString);
    Serial.println("desconfirma");
//   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0   1   2   3
// / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 / 1 *
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6
// 0                  10                  20                  30                  40                  50                  60      

   
    for (int x = 1; x < 66 ; x= x+2){
     stringOne=inputString.substring(x);
//     Serial.print(x);
//     Serial.print("  ");
//     Serial.print(stringOne);
//     Serial.print(" = ");
//     Serial.println(stringOne.toInt());


contadori++;

MamaniAudios[contadori]=stringOne.toInt();

     
    }

    // clear the string:
    inputString = "";
    stringComplete = false;


    for( int i =0; i <21; i++){
//        Serial.println(MamaniAudios[i]);
if (MamaniAudios[i] == 0){

if((i<10)&&(i<20)&&(i<30)){
          vtime=1000;
          if (i==0){
            vtime=3000;
          }
        }
        if((i>10)&&(i<20)&&(i<30)){
          vtime=2000;
        }
        if((i>10)&&(i>20)&&(i<30)){
          vtime=2000;
        }
        if((i>10)&&(i>20)&&(i>30)){
          vtime=2500;
        }
        
        myDFPlayer.play(i);
//        Serial.println(i);
      digitalWrite(led, 1);
      delay(vtime);

}
        
      }

for (int xplot = 0; xplot<34;xplot++){
MamaniAudios[
  
}
      
      myDFPlayer.play(34);
      delay(3000);

      
      Serial.println("confirma");
  }
serialEvent();

     
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '*') {
      stringComplete = true;
    }
  }
}
