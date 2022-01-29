void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode (5,OUTPUT);
pinMode (6,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int valor = analogRead(A0);
int conversion = map ( valor, 0, 1024, 0, 255);
int conversion1 = map ( valor, 0, 1024, 255, 0);
analogWrite(5, conversion);
analogWrite(6, conversion1);
//Serial.print(" Valor del Potenciometro  = ");
Serial.println(valor);
}
