#include <Ultrasonic.h>
int izqA = 2;
int izqB = 3;
int derA = 4;
int derB = 5;
int vel = 255;            // Velocidad de los motores (0-255)
int estado = 'g';         // inicia detenido
Ultrasonic ultrasonic(13, 12); // (Trig PIN,Echo PIN)
void setup()  {

  Serial.begin(9600);    // inicia el puerto serial para comunicacion con el Bluetooth
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);


}

void loop()  {

  int a = ultrasonic.Ranging(CM);
  analogWrite(9, (a*a) + 100);
  analogWrite(10, (a*a) + 100);

  if (Serial.available() > 0) {    // lee el bluetooth y almacena en estado
    estado = Serial.read();
  }
  if (estado == 'a') {       // Boton desplazar al Frente
    digitalWrite(derB, 0);
    digitalWrite(izqB, 0);
    digitalWrite(derA, 1);
    digitalWrite(izqA, 1);
  }
  if (estado == 'b') {      // Boton IZQ
    digitalWrite(derB, 0);
    digitalWrite(izqB, 0);
    digitalWrite(derA, 0);
    digitalWrite(izqA, 1);
  }
  if (estado == 'c') {     // Boton Parar
    digitalWrite(derB, 0);
    digitalWrite(izqB, 0);
    digitalWrite(derA, 0);
    digitalWrite(izqA, 0);
  }
  if (estado == 'd') {      // Boton DER
    digitalWrite(derB, 0);
    digitalWrite(izqB, 0);
    digitalWrite(izqA, 0);
    digitalWrite(derA, 1);
  }

  if (estado == 'e') {      // Boton Reversa
    digitalWrite(derA, 0);
    digitalWrite(izqA, 0);
    digitalWrite(derB, 1);
    digitalWrite(izqB, 1);
  }
  if (estado == 'f') {        // Boton ON se mueve sensando distancia

  }
  if  (estado == 'g') {       // Boton OFF, detiene los motores no hace nada
  }
}
