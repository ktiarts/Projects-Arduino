int state0;
int contador = 0;
int before;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(9,INPUT);
pinMode(10,INPUT);
pinMode(11,INPUT);
}

void loop() {
    // put your main code here, to run repeatedly:
  int state6 = digitalRead(9);
  int state7 = digitalRead(10);
  int state8 = digitalRead(11);
  delay(200);
  if (state7==1){
  do {
  Serial.print(contador);
  while (contador <10){Serial.println("       Tu estas subiendo al segundo piso"); countermagnetposi();  if (contador == 0){
    Serial.println("Estas en el Primer piso");
  }
  if (contador == 10){
    Serial.println("Estas en el Segundo piso");
  }
  if (contador == 20){
    Serial.println("Estas en el Tercer piso");
  }}
  while (contador >10){Serial.println("       Tu estas bajando al segundo piso"); countermagnetnega();
    if (contador == 0){
    Serial.println("Estas en el Primer piso");
  }
  if (contador == 10){
    Serial.println("Estas en el Segundo piso");
  }
  if (contador == 20){
    Serial.println("Estas en el Tercer piso");
  }}
  }while ((contador < 10)&(contador > 10));
  }
  if (state6==1){
  do {
  Serial.print(contador);
  while (contador >0){Serial.println("       Tu estas bajando al primer piso"); countermagnetnega();
    if (contador == 0){
    Serial.println("Estas en el Primer piso");
  }
  if (contador == 10){
    Serial.println("Estas en el Segundo piso");
  }
  if (contador == 20){
    Serial.println("Estas en el Tercer piso");
  }}
  }while ((contador < 0));
  }
  
  if (state8==1){
  do {
  Serial.print(contador);
  while (contador <20){Serial.println("       Tu estas subiendo al tercer piso"); countermagnetposi();
    if (contador == 0){
    Serial.println("Estas en el Primer piso");
  }
  if (contador == 10){
    Serial.println("Estas en el Segundo piso");
  }
  if (contador == 20){
    Serial.println("Estas en el Tercer piso");
  }}
  }while ((contador > 20));
  }
  
  
  if (contador == 0){
    Serial.println("Estas en el Primer piso");
  }
  if (contador == 10){
    Serial.println("Estas en el Segundo piso");
  }
  if (contador == 20){
    Serial.println("Estas en el Tercer piso");
  }

}


void countermagnetposi(){
Serial.println(contador);
state0 = digitalRead(3);
while(state0 == 1){
  state0 = digitalRead(3);
  while(state0 == 0){
    state0 = digitalRead(3);
  contador++;
  state0=3;
  }
}
Serial.println(contador);
}
void countermagnetnega(){
Serial.println(contador);
state0 = digitalRead(3);
while(state0 == 1){
  state0 = digitalRead(3);
  while(state0 == 0){
    state0 = digitalRead(3);
  contador--;
  state0=3;
  }
}
Serial.println(contador);
}

