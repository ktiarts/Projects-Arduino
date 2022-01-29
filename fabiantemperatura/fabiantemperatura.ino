    #include <OneWire.h> //Se importan las librerías
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display


#define Pin 2 //Se declara el pin donde se conectará la DATA
OneWire ourWire(Pin); //Se establece el pin declarado como bus para la comunicación OneWire
DallasTemperature sensors(&ourWire); //Se instancia la librería DallasTemperature


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(0x27);
  lcd.begin(16, 2); // initialize the lcd

sensors.begin();
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);

}

void loop() {

  if (Serial.available() > 0) {    // lee el bluetooth y almacena en estado
    char estado = Serial.read();
      if (estado == 'a') {
digitalWrite(4,LOW);
 delay(500);
    }
      if (estado == 'b') {
digitalWrite(4,HIGH);
    delay(500);
    }
      if (estado == 'c') {
digitalWrite(5,LOW);
delay(500);
    }
      if (estado == 'd') {
digitalWrite(5,HIGH);
    delay(500);
    }
  }

else{
automatico();
}
 
}
void automatico(){
  // put your main code here, to run repeatedly
sensors.requestTemperatures(); //Prepara el sensor para la lectura
float tempe= sensors.getTempCByIndex(0);
Serial.print(tempe); //Se lee e imprime la temperatura en grados Celsius
Serial.println("");
    lcd.setBacklight(255);
    lcd.home(); lcd.clear();
    lcd.print("Ola k aze? ");
    lcd.print(tempe);
 if(tempe < 35){
 digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
   digitalWrite(6,LOW);
}
 if ((tempe > 35)&&(tempe < 45)){
  digitalWrite(5,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(6,HIGH);
 }
 if (tempe >= 45){
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
 }

}

