const int s0 = 2;  
const int s1 = 3;  
const int s2 = 4;  
const int s3 = 5;  
const int out = 6;    
int rojo = 0;  
int verde = 0;  
int azul = 0;  
#include <Ultrasonic.h>
#include <math.h>
Ultrasonic ultra1(7,8);
Ultrasonic ultra2(9,10);
Ultrasonic ultra3(11,12 );
int c1;
int c2;
int c3;
int motor1=13;
int motor2=14;
int motor3=15;
void setup(){  
  Serial.begin(9600); 
  pinMode(s0,OUTPUT);  
  pinMode(s1,OUTPUT);  
  pinMode(s2,OUTPUT);  
  pinMode(s3,OUTPUT);  
  pinMode(out,INPUT);   
  pinMode(motor1,OUTPUT);  
  pinMode(motor2,OUTPUT);
  pinMode(motor3,OUTPUT);    
  digitalWrite(s0,HIGH);  
  digitalWrite(s1,HIGH);  
}  

   
void loop(){  
  color(); 
  Serial.print("   ");  
  Serial.print(rojo, DEC);  
  Serial.print("   ");  
  Serial.print(verde, DEC);  
  Serial.print("   ");  
  Serial.print(azul, DEC);  

  if (rojo < azul && verde > azul && rojo < 35) {  
   Serial.println("   Rojo");    
   seleccion1();
  }   
  else if (azul < rojo && azul < verde && verde < rojo){  
   Serial.println("   Azul");   
   seleccion2() ;    
  }  
  else if (rojo > verde && azul > verde )  {  
   Serial.println("   Verde");   
   seleccion3();    
  }  
  else{
  Serial.println("  ");  
  }
  delay(900);     
  }  
    
void color()  {    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);   
  rojo = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);   
  azul = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);    
  verde = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}

void seleccion1(){
  distancia1();
  if (c1 < 10){
    digitalWrite(motor1,HIGH);
    digitalWrite(motor2,LOW);
    digitalWrite(motor3,LOW);
  }
}

  void seleccion2(){
    distancia2();
    if (c2 < 10){
    digitalWrite(motor1,LOW);
    digitalWrite(motor2,HIGH);
    digitalWrite(motor3,LOW);
  }
  }
    void seleccion3(){
  distancia3();

  if (c3 < 10){
    digitalWrite(motor1,LOW);
    digitalWrite(motor2,LOW);
    digitalWrite(motor3,HIGH);
  }
}
void distancia1(){
  c1 = ultra1.Ranging(CM);
}
void distancia2(){
  c2 = ultra2.Ranging(CM);
}
void distancia3(){
  c3 = ultra3.Ranging(CM);
}

