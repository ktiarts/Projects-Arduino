#include "Nokia_5110.h"
#define RST 3
#define CE 4
#define DC 5
#define DIN 6
#define CLK 7

Nokia_5110 lcd = Nokia_5110(RST, CE, DC, DIN, CLK);

int estadoActual1=0;
int estadoActual2=0;
int estadoUltimo=0;
int contador=0;
float radioEnCm=36.83;   //INGRESAR radio de la rueda en cm
float pi=3.1416;
float perimetroRueda=2*pi*(radioEnCm/100);  //Calcula Perimetro en metros
float distRecorrida=0;
float distKM=0;
int tiempo1=0;
int tiempo2=0;
int tiempo3=0;
float tiempo4=0;
float velocidad=0;

void setup(){
        pinMode(13,OUTPUT);
        pinMode(2,INPUT);
        Serial.begin(9600);
    lcd.println("  Bienvenido ");
    lcd.print("    Batman");
    delay(1000);
    lcd.clear();


}

void loop(){
        estadoActual1=digitalRead(2);
        delay(10);
        estadoActual2=digitalRead(2);
//Si los estados no son iguales, el sketch no hace gran cosa
        if (estadoActual1 == estadoActual2) {
              if (estadoActual1 != estadoUltimo){
                    if (estadoActual1 == HIGH) {
                        contador = contador + 1;
                        lcd.setCursor(0,0);
                        lcd.print ("Vueltas ");
                        lcd.println(contador);
                        distancia();
                        VEL();
                    }
              }
        }
        estadoUltimo= estadoActual1;
              
        if (contador%2 == 0 ) {
              digitalWrite(13, LOW);
        }
        else {
              digitalWrite(13, HIGH);
        }
        lcd.setCursor(0,3);
        lcd.print("Voltaje ");
        int sensorv = analogRead(0);
        float volt = 0.0048828125 * sensorv;
        lcd.println(volt);
       // PantallaLCD();
}


void distancia(){
                        distRecorrida=perimetroRueda*contador;
                        distKM=distRecorrida/1000;
                        if(distRecorrida<=999){
                        lcd.setCursor(0,1);
                                lcd.print("DistM = ");
                                lcd.println(distRecorrida);
                        }
                        else{
                          lcd.setCursor(0,1);
                                lcd.print("DistKm= ");
                                lcd.println(distKM);
                        }
                        }

void VEL(){
        if (contador%2 == 0 ) {
              tiempo1=millis();
        }
        else {
              tiempo2=millis();
        }
        tiempo3=abs(tiempo2-tiempo1); //hay que pasar el tiempo a hrs
        tiempo4=(((tiempo3/1000.0)/60)/60);
        velocidad=((perimetroRueda/1000)/tiempo4);
        lcd.setCursor(0,2);
        lcd.print("vel= ");
        lcd.print(velocidad);
        lcd.println(" Km/h");        
}


 void PantallaLCD(){
            lcd.clear();
            lcd.print("Veloc = ");
            lcd.print(velocidad);
            lcd.print("Kms");
            lcd.setCursor(0,1);
                        if(distRecorrida<=999){
                                lcd.print("Dist = ");
                                lcd.print(distRecorrida);
                                lcd.print(" m");
                        }
                        else{
                                lcd.print("Dist = ");
                                lcd.print(distKM);
                                lcd.print(" Km");
                        }
           lcd.setCursor(0,2);
           lcd.print("Vueltas = ");
           lcd.print(contador);
            return;
}

