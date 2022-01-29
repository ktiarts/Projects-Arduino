void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print( analogRead(34 ));
Serial.print(" ");
Serial.print( analogRead(35));
Serial.print(" ");
Serial.print( analogRead(32));
Serial.print(" ");
Serial.print(analogRead(25));
Serial.print(" ");
float timon = analogRead(35);
int acel = analogRead(34);
float angulo = map (timon, 0,4095,12.01,14.01);
float poder = map (acel,0,4095,0,100);
Serial.print(" ");
Serial.print(angulo);
Serial.print(" ");
Serial.print(poder);
Serial.print(" ");
  int bot1 = analogRead(32);
  int bot2 = analogRead(25);
if((bot1 > 4000)&&(bot2 < 10)){
  Serial.print("D");
}
if((bot2 > 4000)&&(bot1 < 2)){
  Serial.print("R");
}
if((bot2 < 4000)&&(bot1 > 2)){
  Serial.print("N");
}

Serial.println("  ");
}
