#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX


#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int show;

void setup()
{
  int error;

  Serial.begin(115200);
  mySerial.begin(9600);
  inputString.reserve(200);
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  lcd.begin(16, 2); // initialize the lcd
  show = 0;
  lcd.setBacklight(255);
  lcd.home(); lcd.clear();
  lcd.print("Hi Maryo xd");
  delay(1000);
} // setup()

void loop()
{
 if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    lcd.home(); lcd.clear();
  lcd.print(inputString);
    inputString = "";
    stringComplete = false;
  }
serialEvent();
}
void serialEvent() {
  while (mySerial.available()) {
    // get the new byte:
    char inChar = (char)mySerial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
} 
