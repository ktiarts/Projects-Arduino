// Ultrasonic - Library for HR-SC04 Ultrasonic Ranging Module.
// Rev.4 (06/2012)
// J.Rodrigo ( www.jrodrigo.net )
// more info at www.ardublog.com

#include <Ultrasonic.h>

Ultrasonic ultraleft(10,11);   // (Trig PIN,Echo PIN)
Ultrasonic ultracenter(8,9);
Ultrasonic ultraright(6,7);  // (Trig PIN,Echo PIN)

void setup() {
  Serial.begin(9600); 
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
}

void loop()
{
  Serial.print("Left: ");
  Serial.print(ultraleft.Ranging(CM)); // CM or INC
  Serial.print(" cm     " );
  Serial.print("Center: ");
  Serial.print(ultracenter.Ranging(CM)); // CM or INC
  Serial.print(" cm     " );
  Serial.print("Right: ");
  Serial.print(ultraright.Ranging(CM)); // CM or INC
  Serial.println(" cm" );
int izq = ultraleft.Ranging(CM);
int fren = ultracenter.Ranging(CM);
int der = ultraright.Ranging(CM);
if ((der > fren) && (der > izq))
        {
          digitalWrite(2, LOW);
          digitalWrite(3, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(5, LOW);
          delay(200);
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
        }
        if ((fren > der) && (fren > izq))
        {
          digitalWrite(2, LOW);
          digitalWrite(3, HIGH);
          digitalWrite(4, LOW);
          digitalWrite(5, HIGH);
          delay(200);
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);

        }

        if ((izq > fren) && (izq > der))
        {
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, HIGH);
          delay(200);
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
        }
        if (fren <= 10  )
        {
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          digitalWrite(4, HIGH);
          digitalWrite(5, LOW);
          delay(200);
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
        }

}
