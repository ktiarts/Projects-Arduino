void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
/*
 * A1 = Piso 1 estatico
 * A2 = Piso 2 estatico
 * A3 = Piso 3 estatico
 * S1 = Subiendo Piso 1
 * S2 = Subiendo Piso 2
 * S3 = Subiendo Piso 3
 * B1 = Bajando Piso 1
 * B2 = Bajando Piso 2
 * B3 = Bajando Piso 3
 */
char recibir = Serial.read();
if (recibir == 'A'){
  int numero = Serial.parseInt();
  if (numero == 1){
   numero1(); 
   estatico();
  }
  if (numero == 2){
    numero2();
    estatico();
  }
  if (numero == 3){
    numero3();
    estatico();
  }
  
}
if (recibir == 'S'){
  int numero = Serial.parseInt();
  if (numero == 1){
   numero1(); 
  subir();
  }
  if (numero == 2){
    numero2();
    subir();
  }
  if (numero == 3){
    numero3();
    subir();
  }
}
if (recibir == 'B'){
  int numero = Serial.parseInt();
  if (numero == 1){
   numero1();
   bajar(); 
  }
  if (numero == 2){
    numero2();
    bajar();
  }
  if (numero == 3){
    numero3();
    bajar();
  }
}

}


void numero1(){
  
digitalWrite(2,1);//a
digitalWrite(3,0);//b
digitalWrite(4,0);//c
digitalWrite(5,1);//d
digitalWrite(6,1);//e
digitalWrite(7,1);//f
digitalWrite(8,1);//g

}
void numero2(){

digitalWrite(2,0);//a
digitalWrite(3,0);//b
digitalWrite(4,1);//c
digitalWrite(5,0);//d
digitalWrite(6,0);//e
digitalWrite(7,1);//f
digitalWrite(8,0);//g
}
void numero3(){

digitalWrite(2,0);//a
digitalWrite(3,0);//b
digitalWrite(4,0);//c
digitalWrite(5,0);//d
digitalWrite(6,1);//e
digitalWrite(7,1);//f
digitalWrite(8,0);//g
}
void subir(){
digitalWrite(9,1);//Flecha para arriba
digitalWrite(10,0);//Flecha para abajo
}
void bajar(){
digitalWrite(9,0);//Flecha para arriba
digitalWrite(10,1);//Flecha para abajo
}
void estatico(){
digitalWrite(9,0);//Flecha para arriba
digitalWrite(10,0);//Flecha para abajo
}
