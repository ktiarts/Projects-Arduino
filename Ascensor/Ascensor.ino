#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);

int finS = 4; // Fin de carrera Subida
int finB = 3; // Fin de carrera Bajada
int Sensor = 2; // Sensor contador magnetico
int boton1 = 6; // Boton 1 Piso
int boton2 = 7; // Boton 2 Piso 2
int boton3 = 8; // Boton 3 Piso 3
int interrumpir = 9; //Boton interrumpir switch
int subida = 11; // Subida manual
int bajada = 12; // Bajada manual

int state0;
int state1;
int state2;
int state3;
int state4;
int state5;
int state6;
int state7;
int state8;

int relay1 = 14; // Relay 1 Alta/Baja velocidad
int relay2 = 15; // Relay 2 Subir
int relay3 = 16; // Relay 3 Bajar

int contador = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Estatus: Setup");
  Serial.println("Estatus: Reconocimiento de pines");
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(5, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
Serial.println("Estatus: Reconocimiento de pines Finalizado");
Serial.println("Estatus: Inicializado de LCD");
  lcd.begin(16, 2);
  Wire.begin();
  Wire.beginTransmission(0x27);
  lcd.begin(16, 2); // initialize the lcd
  lcd.setBacklight(255);
  lcd.home(); lcd.clear();
  Serial.println("Estatus: Inicializando LCD Finalizado");
  state1 = digitalRead(finB);
  Serial.println("Estatus: Lectura de Fin de Carrera");
  Serial.println("Estatus: Inicializando Autocalibracion");
  // Autocalibración
  do {
    Serial.println("Estatus: Bucle Do");
    digitalWrite(relay1, LOW);
    digitalWrite(relay3, LOW);
    digitalWrite(relay2, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Autocalibracion");
    lcd.setCursor(0, 1);
    lcd.print("Esperar");
    delay(200);
     state1 = digitalRead(finB);
     Serial.println("Estatus: Esperando Fin de carrera de bajada");
  }
  while (state1 == 0);
  Serial.println("Estatus: Autocalibracion Finalizado");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Autocalibracion");
  lcd.setCursor(0, 1);
  lcd.print("Listo");
    digitalWrite(relay1, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay2, HIGH);
  delay(200);
  contador = 0;

}

void loop() {
  Serial.println("Ya empezo el loop");
  // put your main code here, to run repeatedly:
  state0 = digitalRead(Sensor);
  state1 = digitalRead(finB);
  state2 = digitalRead(finS);
  state3 = digitalRead(interrumpir);
  state4 = digitalRead(subida);
  state5 = digitalRead(bajada);
  state6 = digitalRead(boton1);
  state7 = digitalRead(boton2);
  state8 = digitalRead(boton3);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ascensor");
  lcd.setCursor(0, 1);
  lcd.print("Inicializado");

  do  {
  state0 = digitalRead(Sensor);
  state1 = digitalRead(finB);
  state2 = digitalRead(finS);
  state3 = digitalRead(interrumpir);
  state4 = digitalRead(subida);
  state5 = digitalRead(bajada);
  state6 = digitalRead(boton1);
  state7 = digitalRead(boton2);
  state8 = digitalRead(boton3);

    Serial.println("Entro al modo servicio");
      lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicializado");
  lcd.setCursor(0, 1);
  lcd.print("Modo Servicio");
    if (state4 == 1) {
      digitalWrite(relay2, LOW);
      digitalWrite(relay3, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Modo Servicio");
      lcd.setCursor(0, 1);
      lcd.print("Estas Subiendo");
      Serial.println("Estas Subiendo");
      delay(500);
    }
    if (state5 == 1) {
      digitalWrite(relay3, LOW);
      digitalWrite(relay2, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Modo Servicio");
      lcd.setCursor(0, 1);
      lcd.print("Estas Bajando");
      Serial.println("Estas Bajando");
      delay(500);
    }
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
  }
  while (state3 == 1);
  do{
    state0 = digitalRead(Sensor);
  state1 = digitalRead(finB);
  state2 = digitalRead(finS);
  state3 = digitalRead(interrumpir);
  state4 = digitalRead(subida);
  state5 = digitalRead(bajada);
  state6 = digitalRead(boton1);
  state7 = digitalRead(boton2);
  state8 = digitalRead(boton3);
    Serial.println("Modo Automatico");

    parada();
  delay(200);
  if (state7==1){
  do {
  Serial.print(contador);
  while (contador <5){Serial.println("       Tu estas subiendo al segundo piso");
    lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Estas Subiendo");
  lcd.setCursor(0, 1);
  lcd.print("2do Piso");
  subirSlow() ;  countermagnetposi();  
  if ((contador >= 0)&(contador <5)){
    Serial.println("Estas en el Primer piso");
    Serial1.write("S1");
      lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Estas Subiendo");
  lcd.setCursor(0, 1);
  lcd.print("al 2do | 1 piso");
  }
  if (contador == 5){
    Serial.println("Estas en el Segundo piso");
    Serial1.write("A2");
         lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Ya llegaste");
  lcd.setCursor(0, 1);
  lcd.print("al 2do | 2 piso");
  }
 }
  while (contador >5){Serial.println("       Tu estas bajando al segundo piso");
          lcd.clear();
  lcd.setCursor(0, 0);
    lcd.print("Estas Bajando");
  lcd.setCursor(0, 1);
  lcd.print("al 2do piso");
  bajadaSlow() ; countermagnetnega();
 
  if (contador == 5){
    Serial.println("Estas en el Segundo piso");
    Serial1.write("A2");
         lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Ya llegaste");
  lcd.setCursor(0, 1);
  lcd.print("al 2do | 2 piso");
  }
  if ((contador >= 11)&(contador <= 10)){
    Serial.println("Estas en el Tercer piso");
    Serial1.write("B3");
        lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Estas Bajando");
  lcd.setCursor(0, 1);
  lcd.print("al 2do | 3 piso");}
  }}
  while ((contador < 5)&(contador > 5));
  }
  if (state6==1){
  do {
  Serial.print(contador);
  while (contador >0){Serial.println("       Tu estas bajando al primer piso"); bajadaSlow(); countermagnetnega();
        lcd.clear();
  lcd.setCursor(0, 0);
    lcd.print("Estas Bajando");
  lcd.setCursor(0, 1);
  lcd.print("al 1er piso");
    if (contador == 0){
    Serial.println("Estas en el Primer piso");
    Serial1.write("A1");
         lcd.clear();
  lcd.setCursor(0, 0);
    lcd.print("Ya llegaste");
  lcd.setCursor(0, 1);
  lcd.print("al 1er | 1 piso");
  }
 
  if ((contador >= 1)&(contador <= 5)){
    Serial.println("Estas en el 1er piso");
    Serial1.write("B2");
         lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Bajando ");
  lcd.setCursor(0, 1);
  lcd.print("al 1do | 2 piso");
  }
  if ((contador >= 11)&(contador <= 10)){
    Serial.println("Estas en el Tercer piso");
    Serial1.write("B3");
        lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Estas Bajando");
  lcd.setCursor(0, 1);
  lcd.print("al 1do | 3 piso");
 
 
 }
  }}while ((contador < 0));
  }
  if (state8==1){
  do {
  Serial.print(contador);
  while (contador <10){Serial.println("       Tu estas subiendo al tercer piso"); subirSlow(); countermagnetposi();
          lcd.clear();
  lcd.setCursor(0, 0);
    lcd.print("Estas Subiendo");
  lcd.setCursor(0, 1);
  lcd.print("al 3er piso");
    if ((contador >= 0)&(contador < 5)){
    Serial.println("Estas en el Primer piso");
    Serial1.write("S1");
          lcd.clear();
  lcd.setCursor(0, 0);
    lcd.print("Estas Subiendo");
  lcd.setCursor(0, 1);
  lcd.print("al 3er | 1 piso");
  }
  if ((contador >= 5)&(contador < 10)){
    Serial.println("Estas en el Segundo piso");
    Serial1.write("S2");
          lcd.clear();
  lcd.setCursor(0, 0);
    lcd.print("Estas Subiendo");
  lcd.setCursor(0, 1);
  lcd.print("al 3er | 2 piso");
  }
  if (contador == 10){
    Serial.println("Estas en el Tercer piso");
    Serial1.write("A3");
        lcd.clear();
  lcd.setCursor(0, 0);
      lcd.print("Ya llegaste");
  lcd.setCursor(0, 1);
  lcd.print("al 3er | 3 piso");
  }}
  }  while ((contador > 10));
  }
  
  if (contador == 0){
    Serial.println("Estas en el Primer piso");
    Serial1.write("A1");       
           lcd.clear();
  lcd.setCursor(0, 0);
      lcd.print("Estas en el");
  lcd.setCursor(0, 1);
  lcd.print("al 1er piso");
  }
  if (contador == 5){
    Serial.println("Estas en el Segundo piso");
    Serial1.write("A2");
           lcd.clear();
  lcd.setCursor(0, 0);
      lcd.print("Estas en el");
  lcd.setCursor(0, 1);
  lcd.print("al 2do piso");
  }
  if (contador == 10){
    Serial.println("Estas en el Tercer piso");
    Serial1.write("A3");
          lcd.clear();
  lcd.setCursor(0, 0);
        lcd.print("Estas en el");
  lcd.setCursor(0, 1);
  lcd.print("al 3er piso");
  }

  }
  while  (state3 == 0 );

}

void countermagnetposi(){
Serial.println(contador);
state0 = digitalRead(2);
while(state0 == 1){
  state0 = digitalRead(2);
  while(state0 == 0){
    state0 = digitalRead(2);
  contador++;
  digitalWrite(13,HIGH);
  state0=3;
  }
  digitalWrite(13,LOW);
}
Serial.println(contador);
}
void countermagnetnega(){
Serial.println(contador);
state0 = digitalRead(2);
while(state0 == 1){
  state0 = digitalRead(2);
  while(state0 == 0){
    state0 = digitalRead(2);
  contador--;
  digitalWrite(13,HIGH);
  state0 = 3;
  }
  digitalWrite(13,LOW);
}
Serial.println(contador);
}

void subirFast(){
digitalWrite(relay1, LOW);
digitalWrite(relay2, LOW);
digitalWrite(relay3, HIGH);
}
void subirSlow(){
digitalWrite(relay1, HIGH);
digitalWrite(relay2, LOW);
digitalWrite(relay3, HIGH);
}
void bajadaFast(){
digitalWrite(relay1, LOW);
digitalWrite(relay2, HIGH);
digitalWrite(relay3, LOW);
}
void bajadaSlow(){
digitalWrite(relay1, HIGH);
digitalWrite(relay2, HIGH);
digitalWrite(relay3, LOW);
}
void parada(){
digitalWrite(relay1, HIGH);
digitalWrite(relay2, HIGH);
digitalWrite(relay3, HIGH);
}
