void setup() {
  // put your setup code here, to run once:

  for (int pin = 2; pin < 14; pin++) {
    // turn the pin on:
 pinMode(pin, OUTPUT);
  }
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
}

void loop() {
  int pot= analogRead(A5);
  int sen1=analogRead(A6);
  int sen2=analogRead(A6);
    
    int timer= pot;

if (sen1<=700){
  // cODIGO DE UN SENTIDO ASCENDENTE

  for (int thisPin = 2; thisPin < 14; thisPin++) {
    // turn the pin on:
    digitalWrite(thisPin, HIGH);
    delay(timer);
    // turn the pin off:
  }
    digitalWrite(A0, HIGH);
    delay(timer);
    digitalWrite(A1, HIGH);
    delay(timer);
    digitalWrite(A2, HIGH);
    delay(timer);
    digitalWrite(A3, HIGH);
    delay(timer);
    for (int thisPin = 2; thisPin < 14; thisPin++) {
    // turn the pin on:
    digitalWrite(thisPin, LOW);
    delay(timer);
    // turn the pin off:
  }
      digitalWrite(A0, LOW);
    delay(timer);
    digitalWrite(A1, LOW);
    delay(timer);
    digitalWrite(A2, LOW);
    delay(timer);
    digitalWrite(A3, LOW);
    delay(timer);
    //FIN DE ASCENDENTE 
}
    
 
if (sen2<=700){
  // cODIGO DE UN SENTIDO ASCENDENTE


     // CODIGO DE UN SENTIDO DESCENDENTE
    digitalWrite(A3, HIGH);
    delay(timer);
    digitalWrite(A2, HIGH);
    delay(timer);
    digitalWrite(A1, HIGH);
    delay(timer);
    digitalWrite(A0, HIGH);
    delay(timer);
  for (int thisPin = 14; thisPin > 2; thisPin--) {
    // turn the pin on:
    digitalWrite(thisPin, HIGH);
    delay(timer);
    // turn the pin off:
  }
      digitalWrite(A3, LOW);
    delay(timer);
    digitalWrite(A2, LOW);
    delay(timer);
    digitalWrite(A1, LOW);
    delay(timer);
    digitalWrite(A0, LOW);
    delay(timer);
    for (int thisPin = 14; thisPin > 2; thisPin--) {
    // turn the pin on:
    digitalWrite(thisPin, LOW);
    delay(timer);
    // turn the pin off:
  }
}
    //FIN DE ASCENDENTE
}
