void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(4,INPUT); //pulsador A
pinMode(3,INPUT); //pulsador B

pinMode(13,OUTPUT); //Red1
pinMode(12,OUTPUT); //Red2
pinMode(11,OUTPUT); //Red3

pinMode(10,OUTPUT); //Yellow1
pinMode(9,OUTPUT); //Yellow2
pinMode(8,OUTPUT); //Yellow3
}

void loop() {
  // put your main code here, to run repeatedly:
if (digitalRead(4)==1){
  contarA();
}
if (digitalRead(3)==1){
  
contarB();
}
Serial.println ("...Esperando");
}
void contarA(){
  for (int i = 0 ; i<8;i++){
    Serial.println(i);
    digitalWrite (13,1);//ON R1
    digitalWrite (12,1);//ON R2
    digitalWrite (11,1);//ON R3
    digitalWrite (10,0);//off Y1
    digitalWrite (9,0);//off Y2
    digitalWrite (8,0);//off Y3
  }
}
void contarB(){
    for (int i = 7 ; i>=0;i--){
    Serial.println(i);
    digitalWrite (13,0);//ON R1
    digitalWrite (12,0);//ON R2
    digitalWrite (11,0);//ON R3
    digitalWrite (10,1);//off Y1
    digitalWrite (9,1);//off Y2
    digitalWrite (8,1);//off Y3
  }
}
