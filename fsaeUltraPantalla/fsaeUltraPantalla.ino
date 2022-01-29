#include <Average.h>
Average<float> ave(5);
// UTFT_Demo_480x320 (C)2013 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of how to use most of the functions
// of the library with a supported display modules.
//
// This demo was made for modules with a screen resolution 
// of 480x320 pixels.
//
// This program requires the UTFT library.
//

#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>
UTFTGLUE myGLCD(0x09488,A2,A1,A3,A4,A0);

// Declare which fonts we will be using
//#if !defined(SmallFont)
//extern uint8_t SmallFont[];    //.kbv GLUE defines as GFXFont ref
//#endif
#if !defined(SevenSegNumFont)
extern uint8_t SevenSegNumFont[];    //.kbv GLUE defines as GFXFont ref     |
#endif
int contador=0;
int valor;
float anterior;
void setup()
{
  randomSeed(analogRead(5));   //.kbv Due does not like A0
    pinMode(A0, OUTPUT);       //.kbv mcufriend have RD on A0
    digitalWrite(A0, HIGH);
  
// Setup the LCD
  myGLCD.InitLCD();
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.invertDisplay(true);
  myGLCD.clrScr();
  myGLCD.setRotation(3);

}
void loop()
  {

ave.push(analogRead(A5));

for (int i = 0; i < 5; i++) {
        ave.get(i);
        
}
int valorsh = analogRead(A5);
valor = map (ave.mean(), 0 , 1023, 0,18000);
myGLCD.invertDisplay(true);
  myGLCD.setTextSize(25);
  myGLCD.setColor(255, 255, 255);
if ( contador == 0){
    myGLCD.print("N", 180, 60);
}
if ( contador == 1){
    myGLCD.print("1", 180, 60);
}

if ( contador == 2){
    myGLCD.print("2", 180, 60);
}

if ( contador == 3){
    myGLCD.print("3", 180, 60);
}

if ( contador == 4){
    myGLCD.print("4", 180, 60);
}

if ( contador == 5){
    myGLCD.print("5", 180, 60);
}

if ( contador == 6){
    myGLCD.print("6", 180, 60);
    contador = 0;
}

contador++;


if ( valor < 10000){
  myGLCD.setColor(0, 180, 0);
//myGLCD.invertDisplay(true);

}
if (( valor > 10000)&& (valor < 11600)){
  myGLCD.setColor(250, 250, 0);
//myGLCD.invertDisplay(true);

}
if (( valor > 11600)&& (valor < 15000)){
  myGLCD.setColor(250, 0, 0);
//myGLCD.invertDisplay(true);

}
if (( valor > 15000)&& (valor < 18000)){
  myGLCD.setColor(0, 0, 250);
}
if ( valor >17200){
//myGLCD.invertDisplay(false);
//    myGLCD.clrScr();
}
int grueso = map ( valor, 0,18000, 0 , 480);
int reversex = map ( valor, 0,18000, 480 , 0);
  myGLCD.setTextSize(5);
  String numerox = String(valor);
    myGLCD.print(numerox, 10, 60);
    myGLCD.fillRect(0, 0, grueso, 50);
  myGLCD.setColor(0, 0, 0);
    myGLCD.fillRect(grueso, 0, 500, 50);
  float xmen = ave.mean();
  if (xmen < anterior){
  myGLCD.setColor(0, 0, 0);
    myGLCD.fillRect(0, 60, 180, 250);
  }
    anterior = xmen;
}



