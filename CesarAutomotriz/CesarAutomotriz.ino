#include <Average.h>
#include "Nextion.h"
int sensorvalue = 0;       // sensorPin default value
int sensorvalue1 = 0;
float Vin = 5;             // Input voltage
float Vout = 0;            // Vout default value
float Rref = 1023;          // Reference resistor's value in ohms (you can give this value in kiloohms or megaohms - the resistance of the tested resistor will be given in the same units)
float R;
float V;
float Sensibilidad = 0.185;
float I;
uint32_t number = 0;
uint32_t x = 0;
uint32_t y = 0;
char temp[10] = {0};
char temp1[10] = {0};
char temp2[10] = {0};
char volx[10] = {0};
char resx[10] = {0};

NexWaveform s0 = NexWaveform(0, 7, "s0");
NexText t3 = NexText(0, 8, "t3");
NexText t1 = NexText(2, 7, "t1");
NexText t2 = NexText(2, 8, "t2");
NexText t6 = NexText(2, 7, "t6");
NexText t7 = NexText(2, 8, "t7");
NexText t8 = NexText(0, 15, "t8");
NexSlider h0 = NexSlider(0, 7, "h0");
NexSlider h1 = NexSlider(0, 7, "h1");
NexButton b24 = NexButton(0, 13, "b24");
NexButton b25 = NexButton(0, 13, "b25");
char buffer[100] = {0};
float timetotal;
float timediv1;
float timetot1;
float timex;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
 
  nexSerial.begin(9600);
  nexInit();

  b24.attachPush(b24PushCallback);
  b25.attachPush (b25PushCallback);
   Serial.begin(9600);
}

NexTouch *nex_listen_list[] =
{
  &b24,
  &b25,
  NULL
};

void b24PushCallback(void *ptr)
{
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  //    uint16_t len;
  //    uint16_t number;
  //
  //    memset(buffer, 0, sizeof(buffer));
  //    b24.getText(buffer, sizeof(buffer));
  //
  //    number = atoi(buffer);
  //    number += 1;
  //    memset(buffer, 0, sizeof(buffer));
  //    itoa(number, buffer, 10);
  //
  //    t1.setText(buffer);
}
void b25PushCallback(void *ptr)
{
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:

  ampere();
  ohms();
  volts();

  String vol = String(V);
  String res = String(R);
  vol.toCharArray(volx, 10);
  res.toCharArray(resx, 10);

  //  t1.setText(volx);
  //  t2.setText(resx);
  t6.setText(volx);
  t7.setText(resx);
  h0.getValue(&x);
  utoa(x, temp, 10);
  t3.setText(temp);
  h1.getValue(&y);
  utoa(y, temp1, 10);
  t1.setText(temp1);
  utoa(I, temp2, 10);
  t8.setText(temp2);
  nexLoop(nex_listen_list);
   if (Serial.available() > 0) {
    char recibir = Serial.read();
    if (recibir == 'b') {
      digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);

    }

  }
}
//Ricardo Coria.
void volts() {
  Average<float> volti(4);
  sensorvalue1 = analogRead(A2);
  V = map(sensorvalue1, 0, 1023, 0, 14.84251);
  //  Serial.println(V);

  s0.addValue(1, analogRead(A2) * 10);
}

void ohms() {
  Average<float> resis(4);
  sensorvalue = analogRead(A1);
  Vout = (Vin * sensorvalue) / 1023;    // Convert Vout to volts
  R = Rref * (1 / ((Vin / Vout) - 1));   // formula for calculatin resistance
  s0.addValue(0, analogRead(A1) * 10);
  //  Serial.print(R);
  //  Serial.print(" ");
}

void ampere() {
  Average<float> amper(4);
  float voltajeSensor = analogRead(A0) * (5.0 / 1023.0); //lectura del sensor
  I = (voltajeSensor - 2.5) / Sensibilidad; //EcuaciÃ³n  para obtener la corriente
  //  Serial.print(I);
  //  Serial.print(" ");
}

void secuencia1 () {
  timerx();
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(timex);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(timex);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  delay(timex);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  delay(timex);
}
void secuencia2 () {
  timerx();
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  delay(timex);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  delay(timex);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  delay(timex);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  delay(timex);
}
void timerx() {

  timetotal = map(x, 0, 5, 0, 5000); //tiempo de 0-5 segundos
  timediv1 = map(y, 0, 20, 1, 20); // mando de 1 a 20 como dividendo
  timetot1 = timediv1 / 20.0; // sobre 20
  timex = timetot1 * timetotal; // multiplicado por el tiempo total
}




