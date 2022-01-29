#include <Wire.h>
#include <LiquidCrystal.h>


#define   CONTRAST_PIN   9
#define   BACKLIGHT_PIN  7
#define   CONTRAST       110
LiquidCrystal lcd(2, 3, 4, 5, 6, 7 );


// Creat a set of new characters

byte customChar[8] = {
  0b00000,
  0b01111,
  0b11110,
  0b11100,
  0b11000,
  0b11110,
  0b01111,
  0b00000
};

void setup()
{
  Serial.begin ( 57600 );

  // Switch on the backlight and LCD contrast levels
  pinMode(CONTRAST_PIN, OUTPUT);
  analogWrite ( CONTRAST_PIN, CONTRAST );

  //lcd.setBacklightPin ( BACKLIGHT_PIN, POSITIVE );
  //lcd.setBacklight ( HIGH );
  lcd.backlight();
    
  lcd.begin(16,2);               // initialize the lcd 

  lcd.createChar (0, customChar);
  // load character to the LCD
  lcd.home ();                   // go home
  lcd.print("::------LCD-------::");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print("::~~-2X20 AZUL--~~::");      
  delay(2000);
}

void loop()
{
  lcd.setCursor(0,1);
  lcd.print (char(0));
  /*// Do a little animation by writing to the same location
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~---Diodos---~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~Transistores~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~---Modulos--~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~---Arduino--~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~Raspberry Pi~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~--Sensores--~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~Resistencias~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~Condensadores~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~--Pantallas-~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~----LCD-----~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~----GLCD----~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~---Touch----~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~----TFT-----~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~---Motores--~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~Servomotores~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~Motoreductor~~::");
  delay (1000);
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~Be Happy Bro~~::");
  delay (1000);
*/}
