float tempC;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
digitalWrite(13, HIGH);
digitalWrite(2, HIGH);
digitalWrite(3, HIGH);
digitalWrite(4, HIGH);
digitalWrite(5, HIGH);
delay(300);
digitalWrite(13, LOW);
digitalWrite(2, LOW);
digitalWrite(3, LOW);
digitalWrite(4, LOW);
digitalWrite(5, LOW);
delay(300);
}

// the loop function runs over and over again forever
void loop() {
  logica();
}

void sensorT(){
  tempC = analogRead(A0);
  tempC = (5.0 * tempC * 100.0)/1024.0;
  Serial.print("temp :");
  Serial.println(tempC);
  delay(100);
}
void ledexceso(bool x ) {
digitalWrite(2,x);
}
void lednormal(bool x ) {
digitalWrite(3,x);
}
void ventilador(bool x) {
digitalWrite(4,x);
}
void lampara(bool x) {
digitalWrite(5,x);
}

void logica(){
  sensorT();
if(tempC < 40 ){
  lampara(true);
  ventilador(false);
  lednormal(true);
  ledexceso(false);
}
if (tempC > 40 ){
                  while(tempC >35){
                                    sensorT();
                                    lampara(false);
                                    ventilador(true);
                                    if (tempC > 40 ){
                                                     ledexceso(true);
                                                     lednormal(false);
                                                    }
                                    if(tempC < 40 ){
                                                     ledexceso(false);
                                                     lednormal(true);
 
                                                    }
  
                                   }
  
}
  
}
