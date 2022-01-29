
#include <avr/wdt.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(2, 3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void(* resetFunc) (void) = 0;//declare reset function at address 0

void setup()
{
  wdt_disable();
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  pinMode(5,OUTPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  digitalWrite(5,LOW);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  myDFPlayer.begin(mySoftwareSerial);
  delay(3000);
//  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
//    Serial.println(F("Unable to begin:"));
//    Serial.println(F("1.Please recheck the connection!"));
//    Serial.println(F("2.Please insert the SD card!"));
//    resetFunc(); //call reset
//    while(true);
//  }
  Serial.println(F("DFPlayer Mini online."));
  digitalWrite(5,HIGH);
  
    myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  wdt_enable(WDTO_1S);
}

void loop()
{
int pot = analogRead(A0); 
int vol = map(pot,0,1023,0,30);
myDFPlayer.volume(vol);  //Set volume value (0~30)
wdt_reset();

if((digitalRead(6)==1)&& (digitalRead(7)==1)){
  myDFPlayer.play(1);  //Play the first mp3
  Serial.println("Reproducete che pelutudo");
  wdt_reset();
  delay(500);
}
}


