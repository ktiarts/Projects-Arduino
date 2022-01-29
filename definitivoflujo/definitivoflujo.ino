
// this constant won't change:
const int  buttonPin1 = 2;    // the pin that the pushbutton is attached to
const int  buttonPin2 = 8;
const int  buttonPin3 = 10;
const int  buttonPin4 = 11;
const int ledPin1 = 4;       // the pin that the LED is attached to
const int ledPin2 = 5;
const int ledPin3 = 6;
const int ledPin4 = 7;


// Variables will change:
int buttonPushCounter1 = 0;   // counter for the number of button presses
int buttonPushCounter2 = 0;
int buttonPushCounter3 = 0;
int buttonPushCounter4 = 0;
int buttonState1 = 0;         // current state of the button
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int lastButtonState1 = 0;     // previous state of the button
int lastButtonState2 = 0;
int lastButtonState3 = 0;
int lastButtonState4 = 0;
int cant1;
int cant2;
int cant3;
int cant4;
int cant5;
void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin1, INPUT);
   pinMode(buttonPin2, INPUT);
    pinMode(buttonPin3, INPUT);
     pinMode(buttonPin4, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
double militros1;
double militros2;
double militros3;
double militros4;
  
 char bluetooth1 = Serial.read();
 if (bluetooth1 == 'a') {
  Serial.print("*A");
  Serial.print("ml necesitados   =");
     cant1 = Serial.parseInt();
  Serial.print("*A");
          Serial.println(cant1);
}
 if (bluetooth1 == 'b') {
    Serial.print("*B");
  Serial.print("ml necesitados   =");
     cant2 = Serial.parseInt();
       Serial.print("*B");
          Serial.println(cant2);
}
 if (bluetooth1 == 'c') {
    Serial.print("*C");
  Serial.print("ml necesitados   =");
     cant3 = Serial.parseInt();
       Serial.print("*C");
          Serial.println(cant3);
}
 if (bluetooth1 == 'd') {
    Serial.print("*D");
  Serial.print("ml necesitados   =");
     cant4 = Serial.parseInt();
       Serial.print("*D");
          Serial.println(cant4);
}
 if (bluetooth1 == 'e') {
  Serial.print("ml necesitados   =");
     cant5 = Serial.parseInt();
     cant1 = cant5;
     cant2 = cant5;
     cant3 = cant5;
     cant4 = cant5;
            Serial.print("*A");
          Serial.println(cant1);
            Serial.print("*B");
          Serial.println(cant2);
            Serial.print("*C");
          Serial.println(cant3);
            Serial.print("*D");
          Serial.println(cant4);
}
   if (bluetooth1 == 'f') {
    digitalWrite(4,HIGH);
}
   if (bluetooth1 == 'g') {
    digitalWrite(5,HIGH);
}
   if (bluetooth1 == 'h') {
    digitalWrite(6,HIGH);
}
   if (bluetooth1 == 'i') {
    digitalWrite(7,HIGH);
}
   if (bluetooth1 == 'j') {
    digitalWrite(4,LOW);
}
   if (bluetooth1 == 'k') {
    digitalWrite(5,LOW);
}
   if (bluetooth1 == 'l') {
    digitalWrite(6,LOW);
}
   if (bluetooth1 == 'm') {
    digitalWrite(7,LOW);
}
  
  // SENSOR 1
  
  buttonState1 = digitalRead(buttonPin1);
  if (buttonState1 != lastButtonState1) {
    if (buttonState1 == HIGH) {
      buttonPushCounter1++;
        Serial.print("*Aml contador:  ");
      militros1 = buttonPushCounter1*2.78;
     Serial.print("*A");
      Serial.print(militros1);
       Serial.print("*Aml necesitados   =");
     Serial.print("*A");
       Serial.println(cant1);
        if (militros1  >= cant1) {
    digitalWrite(ledPin1, LOW);
  } else {
    digitalWrite(ledPin1, HIGH);
  }
    } 
  }
  lastButtonState1 = buttonState1;


  // SENSOR 2
  
  buttonState2 = digitalRead(buttonPin2);
  if (buttonState2 != lastButtonState2) {
    if (buttonState2 == HIGH) {
      buttonPushCounter2++;
        Serial.print("*Bml contador:  ");
      militros2 = buttonPushCounter2*2.78;
      Serial.print("*B");
      Serial.print(militros2);
       Serial.print("*Bml necesitados   =");
       Serial.print("*B");
       Serial.println(cant2);
        if (militros2  >= cant2) {
    digitalWrite(ledPin2, LOW);
  } else {
    digitalWrite(ledPin2, HIGH);
  }
    } 
  }
  lastButtonState2 = buttonState2;


  // SENSOR 3

  
  buttonState3 = digitalRead(buttonPin3);
  if (buttonState3 != lastButtonState3) {
    if (buttonState3 == HIGH) {
      buttonPushCounter3++;
        Serial.print("*Cml contador:  ");
      militros3 = buttonPushCounter3*2.78;
      Serial.print("*C");
      Serial.print(militros3);
       Serial.print("*Cml necesitados   =");
       Serial.print("*C");
       Serial.println(cant3);
        if (militros3  >= cant3) {
    digitalWrite(ledPin3, LOW);
  } else {
    digitalWrite(ledPin3, HIGH);
  }
    } 
  }
  lastButtonState3 = buttonState3;


  // SENSOR 4

  
  buttonState4 = digitalRead(buttonPin4);
  if (buttonState4 != lastButtonState4) {
    if (buttonState4 == HIGH) {
      buttonPushCounter4++;
        Serial.print("*Dml contador:  ");
      militros4 = buttonPushCounter4*2.78;
      Serial.print("*D");
      Serial.print(militros4);
       Serial.print("*Dml necesitados   =");
       Serial.print("*D");
       Serial.println(cant4);
        if (militros4  >= cant4) {
    digitalWrite(ledPin4, LOW);
  } else {
    digitalWrite(ledPin4, HIGH);
  }
    } 
  }
  lastButtonState4 = buttonState4;


 
}









