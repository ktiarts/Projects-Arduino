#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial14.h>
#include <fonts/Droid_Sans_24.h>
#include <fonts/NuevaLetra.h>
#include <fonts/letrax.h>
#include <fonts/letra3.h>

volatile byte half_revolutions;
unsigned int rpm;
unsigned long timeold;
String payload = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete
SPIDMD dmd(3, 3); // DMD controls the entire display
DMD_TextBox box(dmd);  // "box" provides a text box to automatically write to/scroll the display
int count = 0;

void messageReceived( String &payload) {
  dmd.clearScreen();
//  noInterrupts();
int rpmfin= rpm ;
//  Serial.println(payload);

int pos1=payload.lastIndexOf('!');
int pos2=payload.lastIndexOf('+');
int pos3=payload.lastIndexOf('#');
int pos4=payload.lastIndexOf('$');
int pos5=payload.lastIndexOf('%');
int pos6=payload.lastIndexOf('&');
int pos7=payload.lastIndexOf('/');
int pos8=payload.lastIndexOf('(');
int pos9=payload.lastIndexOf(')');
int pos10=payload.lastIndexOf('=');
int pos11=payload.lastIndexOf('?');
int pos12=payload.lastIndexOf('¡');
int pos13=payload.lastIndexOf('¿');
int pos14=payload.lastIndexOf('*');
int pos15=payload.lastIndexOf('{');

//Serial.println("termina de posicionar los INT");
String fuentex = payload.substring(pos1+1,pos2);   
String fuentex1 = payload.substring(pos2+1,pos3);
String fuentex2 = payload.substring(pos3+1,pos4);

String xv1 = payload.substring(pos4+1,pos5);
String yv1 = payload.substring(pos5+1,pos6);
String xv2 = payload.substring(pos6+1,pos7);
String yv2 = payload.substring(pos7+1,pos8);
String xv3 = payload.substring(pos8+1,pos9);
String yv3 = payload.substring(pos9+1,pos10);

String value1 = payload.substring(pos10+1,pos11);
String value2 = payload.substring(pos11+1,pos12);
String value3 = payload.substring(pos12+1,pos13);

String brillox = payload.substring(pos13+1,pos14);
String Refreshed = payload.substring(pos14+1,pos15);
int brillo = brillox.toInt();
int refresh = Refreshed.toInt();

int fuente = fuentex.toInt();
int fuente1 = fuentex1.toInt();
int fuente2 = fuentex2.toInt();

int x1= xv1.toInt();
int y1= yv1.toInt();
int x2= xv2.toInt();
int y2= yv2.toInt();
int x3= xv3.toInt();
int y3= yv3.toInt();

//Serial.println("termina iniciar y asignar variables");
dmd.setBrightness(brillo);
//Serial.print("Le doy brillo  ");
//Serial.println(brillo);
  box.clear();
//  Serial.println("Es el BoxClear");
  if ( fuente == 1) {
    dmd.selectFont(Arial14);
  }
  if ( fuente == 2) {
    dmd.selectFont(Droid_Sans_24);
  }
  if ( fuente == 3) {
    dmd.selectFont(nuevaletra);
  }
  if ( fuente == 4) {
    dmd.selectFont(new_Font);
  }
  if ( fuente == 5) {
    dmd.selectFont(letra3);
  }
  if ( fuente == 6) {
    dmd.selectFont(letra3);
  }
  if ( fuente == 7) {
    dmd.selectFont(letra3);
  }
//Serial.println("Fuente1");
   dmd.drawString(x1,y1,value1);
//  Serial.println("Dibuja la primera sentencia");

  if ( fuente1 == 1) {
    dmd.selectFont(Arial14);
  }
  if ( fuente1 == 2) {
    dmd.selectFont(Droid_Sans_24);
  }
  if ( fuente1 == 3) {
    dmd.selectFont(nuevaletra);
  }
  if ( fuente1 == 4) {
    dmd.selectFont(new_Font);
  }
  if ( fuente1 == 5) {
    dmd.selectFont(letra3);
  }
  if ( fuente1 == 6) {
    dmd.selectFont(letra3);
  }
  if ( fuente1 == 7) {
    dmd.selectFont(letra3);
  }
  
//Serial.println("Fuente2");
   dmd.drawString(x2,y2,value2);
//  Serial.println("Segunda Sentencia");
  if ( fuente2 == 1) {
    dmd.selectFont(Arial14);
  }
  if ( fuente2 == 2) {
    dmd.selectFont(Droid_Sans_24);
  }
  if ( fuente2 == 3) {
    dmd.selectFont(nuevaletra);
  }
  if ( fuente2 == 4) {
    dmd.selectFont(new_Font);
  }
  if ( fuente2 == 5) {
    dmd.selectFont(letra3);
  }
  if ( fuente2 == 6) {
    dmd.selectFont(letra3);
  }
  if ( fuente2 == 7) {
    dmd.selectFont(letra3);
  }
//Serial.println("Fuente 3");
   dmd.drawString(x3,y3,value3);
//  Serial.println("Tercerca sentencia");
//  attachInterrupt(5,rpm_fun, RISING);
//  interrupts();
delay(100);
//Serial.println("termina recibido e impresion");

//if (rpmfin =! rpm ){
//  dmd.clearScreen();
//}
}
void setup() {
  
  Serial.begin(115200);
//  Serial.println("Serial Activado");
//Serial.println("Inicia el DMD BEGIN");
dmd.begin();
//Serial.println("Termina de iniciar DMD Begin");
delay(1000);
  attachInterrupt(5,rpm_fun, RISING);
  payload.reserve(200);
}
void loop() {

if (half_revolutions >= 2) {
//  noInterrupts();
      rpm = 30 * 1000 / (millis() - timeold) * half_revolutions;
      timeold = millis();
      half_revolutions = 0;
      Serial.println(rpm, DEC);
      String errepeeme = String(rpm);
      delay(100);
       }
       
Serial.println(rpm, DEC);
  delay(100);
  
         if (stringComplete) {
//    Serial.println(payload);
     messageReceived(payload);
    // clear the string:
    payload = "";
    stringComplete = false;
  }
  
  serialEvent();
  count++;
  if (count == 200){
    count = 0;
    rpm = 0;
  }
}

void rpm_fun(){
  half_revolutions++;
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    payload += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '{') {
      stringComplete = true;
    }
  }
}

