

//#define MIN_T 1000                         // minima duracion del periodo de la onda en milisegundos (1 segundo)
//#define MAX_T 10000                        // maxima duracion del periodo de la onda en milisegundos (10 segundos)
//#define POT A0                             // pin analogico del potenciometro

unsigned long T;                           // periodo de la onda
unsigned long _delay;                      // duracion de un paso
double angulo;                             // angulo en radianes de 0 a 2pi
double deltaAngulo;                        // incremento del angulo en un paso
double pasos;                              // cantidad de particiones de un ciclo de onda

double minimo = 4.70987570626182;
double maximo = 7.89168074581756;
double paso = 0.00502654824574367;



void setup() {
  Serial.begin(115200);                    // iniciamos puerto serie a 115200 baudios
                                           // si utilizan el mismo graficador que yo modificar los baudios en el script python(viene 9600 por defecto)
pinMode(0,INPUT);
}

void loop() {
  
  angulo = 0;                                             // ponemos el angulo a cero 
  T = 10000;        // leemos T del potenciometro cambiando al rango definido
  pasos = T/80.0;                                         // ajustamos la cantidad de pasos a T para obtener una mejor grafica
                                                          // en este caso uso un factor de 80.0 pero va a depender del rango de T
  _delay = T / pasos;                                     // calculamos el delay de acuerdo al T medido y a los pasos
  deltaAngulo = 2.0 * PI / pasos;                         // calculamos el angulo incremental  

if(digitalRead(0) == false){
   
  for (angulo=4.70987570626182 ;angulo < 7.89168074581756; angulo= angulo + 0.00502654824574367 ) {                                // mientras no haya completado un ciclo
    
    //las siguientes dos lineas deben ser modificadas de acuerdo al graficador que utilicen o si quieren sacar por PWM o un DAC
   double x=(sin(angulo)*2048+2047);
   String xstring = String(x,10);
    Serial.println(xstring);               // calculamos el seno y lo mapeamos a un valor de 0 a 255
                               // incrementamos el angulo en un delta correspondiente a un paso
    delay(_delay);                                        // esperamos el tiempo que dura un paso
  }
}
  
}
