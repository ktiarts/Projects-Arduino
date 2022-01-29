#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);
unsigned long previousMillis = 0;
const long interval = 1000;
int segundos;
int minutos1;
int minutos2;
int minutosX;
void setup() {
//--------[ Modo Dios ]-------//
  Serial.begin(115200);
  int error;
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  pinMode(13,OUTPUT);
  pinMode(10,INPUT);
    lcd.clear();
}

void loop() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Feliz Cumpleaños!");
  lcd.setCursor(0, 1);
  lcd.print("Azulita :D");

}
