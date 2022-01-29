
volatile int pulsos; // Cantidad de pulsos del sensor. Como se usa dentro de una interrupcion debe ser volatile
#define sensorDeFlujo 2 //Pin al que se conecta el sensor. DEBE ser 2 porque es unico que acepta interrpciones en el Arduino UNO
double milis;
void flujo () // Funcion de interrupcion

{
  pulsos++; // Simplemente sumar el numero de pulsos

}

void setup()

{
  Serial.begin(9600);
    pinMode(sensorDeFlujo, INPUT);
  pinMode(4, OUTPUT);
  
  attachInterrupt(0, flujo, RISING);
  
}

void loop ()
{
int cant= 500;
  Serial.print("mililitros: ");
  milis = pulsos * 1.77304965;
  Serial.println(milis);
  Serial.print("      need: ");
  Serial.println(cant);

  // 500ml es aprox 282 pulsaciones +-2

  if (cant <= milis) {
    digitalWrite (4, LOW);
  }
  if (cant > milis) {
    digitalWrite(4, HIGH);
  }

}
