#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
float distancia;
long tiempo;
void setup() {
  Serial.begin(9600);
  pinMode(12,OUTPUT);
  pinMode(11,INPUT);
  // put your setup code here, to run once:
 lcd.begin(16, 2);              // Inicializar el LCD
 int t = 150;
      lcd.setCursor(0,0);
      lcd.print("Iniciando Skynet");// print a simple message
      lcd.setCursor(0,1);
      lcd.print(".");
      delay (t);
      lcd.setCursor(0,1);
      lcd.print("...");
      delay (t);
      lcd.setCursor(0,1);
      lcd.print(".....");
      delay (t);
      lcd.setCursor(0,1);
      lcd.print(".......");
      delay (t);
      lcd.setCursor(0,1);
      lcd.print(".........");
      delay (t);
      lcd.clear();
}


void loop() {
   lcd.begin(16, 2);  
  float der;
  // put your main code here, to run repeatedly:
digitalWrite(12, LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
  digitalWrite(12, HIGH); /* envío del pulso ultrasónico*/
  delayMicroseconds(10);
  tiempo = pulseIn(11, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
  del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
  deja de hacerlo, LOW, la longitud del pulso entrante*/
  distancia = (0.017 * tiempo); /*fórmula para calcular la distancia obteniendo un valor entero*/
  /*Monitorización en centímetros por el monitor serial*/
  der = distancia;
  lcd.setCursor(0,0);
    lcd.print("Distancia = ");
    lcd.setCursor(2,1);
  lcd.print(der);
  lcd.print(" cm");
  Serial.print("Distancia = ");
  Serial.print(der);
  Serial.print(" cm");
  delay (10);
}
