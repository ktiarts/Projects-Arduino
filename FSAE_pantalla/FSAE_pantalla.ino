#include "DHT.h"
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
const int DHTPin = 10;
DHT dht(DHTPin, DHTTYPE); 
#define TOUCH_ORIENTATION  LANDSCAPE
#define USE_UTOUCH         0

#if !(USE_UTOUCH)
#define TITLE "TouchScreen.h Calibration"
#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>            //we are using UTFT display methods
extern unsigned short fsae1[];
UTFTGLUE myGLCD(0x9481, A2, A1, A3, A4, A0);

#include <TouchScreen.h>

// MCUFRIEND UNO shield shares pins with the TFT.   Due does NOT work
#define YP A1   //A3 for ILI9320
#define YM 7    //9
#define XM A2
#define XP 6    //8  

#define MINPRESSURE 10
#define MAXPRESSURE 1000
TouchScreen myTouch(XP, YP, XM, YM, 300);
TSPoint tp;                      //Touchscreen_due branch uses Point
void readResistiveTouch(void)
{
    tp = myTouch.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);
    digitalWrite(XM, HIGH);
}

bool ISPRESSED(void)
{
    readResistiveTouch();
    return tp.z > 20 && tp.z < 1000;
}

void showpoint(void)
{
    Serial.print("\r\nx="); Serial.print(tp.x);
    Serial.print(" y="); Serial.print(tp.y);
    Serial.print(" z="); Serial.print(tp.z);
}

#else
#define TITLE "UTouch.h Calibration"
#include <SPI.h>
#include <UTFT.h>
#include <UTouch.h>
UTFT    myGLCD(ILI9486, 38, 39, 40, 41);
UTouch  myTouch( 6, 5, 4, 3, 2);

#define ISPRESSED() myTouch.dataAvailable()
extern void fail();

#endif

// Declare which fonts we will be using
extern uint8_t BigFont[];

uint32_t cx, cy;
uint32_t rx[8], ry[8];
int32_t clx, crx, cty, cby;
float px, py;
int dispx, dispy, text_y_center, swapxy;
uint32_t calx, caly, cals;
char buf[13];


void setup()
{
 Serial.begin(9600);
 pinMode(11, OUTPUT);
 pinMode(12, OUTPUT);
 digitalWrite(11,HIGH);
 digitalWrite(12,HIGH);
 
 dht.begin();
    Serial.println("UTouch_Calibr_kbv");
    digitalWrite(A0, HIGH);
    pinMode(A0, OUTPUT);
    myGLCD.InitLCD(TOUCH_ORIENTATION);
    myGLCD.clrScr();
    myGLCD.setFont(BigFont);
#if (USE_UTOUCH)
    myTouch.InitTouch(TOUCH_ORIENTATION);
#endif
    dispx = myGLCD.getDisplayXSize();
    dispy = myGLCD.getDisplayYSize();
    text_y_center = (dispy / 2) - 6;

}

void waitForTouch()
{
    while (ISPRESSED() == true) {}
    while (ISPRESSED() == false) {}
    while (ISPRESSED() == true) {}
}


void loop()
{
 myGLCD.setBackColor(255,255, 255); 
 //  myGLCD.setColor(64, 64, 64);
// myGLCD.setBackColor(255, 0, 0);
 myGLCD.drawBitmap(85,60,150,100,fsae1);
 
  //delay(2000);
  
 
   myGLCD.setTextSize(3);
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   String hum = String(h);
   String tem = String(t);
   if (t>24){
    digitalWrite(12,LOW);
   }
   if(t<24){
    digitalWrite(12,HIGH);
   }
   myGLCD.setColor(255, 0, 0);
    myGLCD.fillRect(0, 0, dispx - 1, 13);
    myGLCD.setColor(255, 255, 255);
 //   myGLCD.setBackColor(255, 0, 0);
   // myGLCD.drawLine(0, 14, dispx - 1, 14);
   // myGLCD.print(TITLE, 1, 30);
    //myGLCD.setBackColor(0, 0, 0); 
    myGLCD.print("Test 1", 1, 160);
     myGLCD.print("Formula SAE", 1,220);
    myGLCD.setColor(0, 255, 255);
    myGLCD.print("UTP", 350,220);
     //delay(2000);
     
 /*   myGLCD.print("Temperatura C ", 1, 112);
    myGLCD.print(tem,300,112);
    myGLCD.print("C", 365, 112);
    myGLCD.print("Humedad", 1, 154);
    myGLCD.print(hum,300,154);
    myGLCD.print("%", 365, 154);
  //myGLCD.drawCircle(x,y,radio);
    myGLCD.drawCircle(220,220,50);
    myGLCD.setColor(255, 255, 255);
    myGLCD.fillCircle(220,220,48);
    myGLCD.drawCircle(220,220,40);
    myGLCD.setColor(0, 255, 255);
   myGLCD.fillCircle(220,220,38);
     //waitForTouch();
      if (ISPRESSED() == true) {

    myGLCD.print("Has prendido la luz", 30, 200);

    myGLCD.clrScr();
    myGLCD.fillScr(255,255,255);   
   myGLCD.print("Has prendido la luz", 30, 200);
   myGLCD.print("Toca para apagar", 30, 250);
   Serial.print("X = "); Serial.print(tp.x);
     Serial.print("\tY = "); Serial.println(tp.y);
   digitalWrite(11,LOW);
   waitForTouch(); 
   myGLCD.clrScr();
   digitalWrite(11,HIGH);
    */  }

