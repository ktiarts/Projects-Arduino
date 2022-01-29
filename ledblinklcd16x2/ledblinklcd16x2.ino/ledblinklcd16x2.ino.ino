#include <Wire.h>
#include <LiquidCrystal.h>


#define   CONTRAST_PIN   9
#define   BACKLIGHT_PIN  7
#define   CONTRAST       110
LiquidCrystal lcd(2, 3, 4, 5, 6, 7 );


// Creat a set of new characters
byte abierto[8] = {
  0b00000,
  0b01111,
  0b11110,
  0b11100,
  0b11000,
  0b11110,
  0b01111,
  0b00000
};
byte cerrado[8] = {
  0b00000,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
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
    
  lcd.begin(16,2);
  lcd.createChar (0, abierto);
  lcd.createChar (1, cerrado); 
  lcd.home ();                   // go home
  lcd.print("LedBlink Electronica");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print("::~~---Welcome--~~::");      
  delay(2000);
}

void loop()
{
  // Do a little animation by writing to the same location
  lcd.setCursor ( 0, 0 );
  lcd.print("--------------------");
  lcd.setCursor ( 0, 0 );
  lcd.print (char(0));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~---Diodos---~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("--------------------");
  lcd.setCursor ( 1, 0 );
  lcd.print (char(1));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~Transistores~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("--------------------");
  lcd.setCursor ( 2, 0 );
  lcd.print (char(0));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~---Modulos--~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 3, 0 );
  lcd.print (char(1));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~---Arduino--~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 4, 0 );
  lcd.print (char(0));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~Raspberry Pi~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 5, 0 );
  lcd.print (char(1));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~--Sensores--~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 6, 0 );
  lcd.print (char(0));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~Resistencias~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 7, 0 );
  lcd.print (char(1));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~Condensadores~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 8, 0 );
  lcd.print (char(0));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~--Pantallas-~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 9, 0 );
  lcd.print (char(1));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~----LCD-----~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 10, 0 );
  lcd.print (char(0));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~----GLCD----~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 11, 0 );
  lcd.print (char(1));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~---Touch----~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 12, 0 );
  lcd.print (char(0));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~----TFT-----~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 13, 0 );
  lcd.print (char(1));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~---Motores--~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 14, 0 );
  lcd.print (char(0));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~Servomotores~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 15, 0 );
  lcd.print (char(1));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~Motoreductor~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 16, 0 );
  lcd.print (char(0));
  lcd.setCursor ( 0, 1 );
  lcd.print("::~~--Bluetooth-~~::");
  delay (900);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 17, 0 );
  lcd.print (char(1));
  delay(250);
  lcd.setCursor ( 0, 0 );
  lcd.print("---------------------");
  lcd.setCursor ( 18, 0 );
  lcd.print (char(0));
  delay(250);
  lcd.setCursor ( 0, 0 );
  lcd.print("----------------------");
  lcd.setCursor ( 19, 0 );
  lcd.print (char(1));
  delay(250);
  lcd.setCursor ( 0, 0 );
  lcd.print("----------------------");
  lcd.setCursor ( 20, 0 );
  lcd.print (char(0));
  delay(250);
  lcd.setCursor ( 0, 0 );
  lcd.print("----------------------");
  lcd.setCursor ( 21, 0 );
  lcd.print (char(1));
  delay(250);
  
}
