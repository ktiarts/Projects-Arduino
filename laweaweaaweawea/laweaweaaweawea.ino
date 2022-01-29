unsigned long previousMillis = 0;
const long interval = 1000;
int segundos;
int minutos1;
int minutos2;
int minutosX;

void setup() {
//--------[ Modo Dios ]-------//
  Serial.begin(115200);
  int error;
  pinMode(13,OUTPUT);
  pinMode(10,INPUT);
}

void loop() {

  digitalWrite(13,LOW);
  segundos = 0;
  minutos1 = 0;
  minutos2 = 0;
  minutosX = 0;
  
while ( digitalRead(10)==HIGH){
  delay(100);
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    segundos++;
   }
  if (segundos == 60){segundos = 0; minutos1++; if (minutos1 == 2){minutosX = 1;minutos1 = 0;}}
   if (minutosX == 1){digitalWrite(13,HIGH); if (minutos1 == 1){minutosX == 0;minutos1==0; minutos2==0;}}
   if (minutosX == 0){digitalWrite(13,LOW);}
float sensor= analogRead(A0);
float voltaje= map(sensor,0,1023,0.0000,5.0000);
printX(segundos,minutos1,voltaje);
}

float sensor= analogRead(A0);
float voltaje= map(sensor,0,1023,0.0000,5.0000);
printX(0,0,voltaje);
delay(100);
}




void printX(int segx,int minx,float heman){
  Serial.print("Tiempo = ");
  Serial.print(minx);
  Serial.print(":");
  Serial.print(segx);
  Serial.print(" Voltaje= ");
  Serial.println(heman);
}
