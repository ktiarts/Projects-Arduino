#include <Ultrasonic.h>
Ultrasonic ultraleft(12, 13);  // (Trig PIN,Echo PIN)
Ultrasonic ultraright(8, 9); // (Trig PIN,Echo PIN)

void setup() {
// luces del tablero
  pinMode(2, OUTPUT); //led 2m iz
  pinMode(3, OUTPUT); //led 1m iz
  
  pinMode(4, OUTPUT); //led 2m de
  pinMode(5, OUTPUT); //led 1m de
// relay para luces
  pinMode(6, OUTPUT); //relay iz
  pinMode(7, OUTPUT); //relay de

}

void loop() {
  // put your main code here, to run repeatedly:
 int a = ultraleft.Ranging(CM);
  int c = ultraright.Ranging(CM);

   if (a<200) {
    //tablero
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    //relay
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
     if (a<100) {
    //tablero
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    //relay
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
       if (b<200) {
    //tablero
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    //relay
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  }
       if (b<100) {
    //tablero
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    //relay
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  }
}
