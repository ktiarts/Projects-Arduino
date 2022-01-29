/*

  Demonstrates simple RX and TX operation.
  Please read the notes in NRFLite.h for a description of all library features.

  Radio    Arduino
  CE    -> 9
  CSN   -> 10 (Hardware SPI SS)
  MOSI  -> 11 (Hardware SPI MOSI)
  MISO  -> 12 (Hardware SPI MISO)
  SCK   -> 13 (Hardware SPI SCK)
  IRQ   -> No connection
  VCC   -> No more than 3.6 volts
  GND   -> GND

*/

#include <SPI.h>
#include <NRFLite.h>

const static uint8_t RADIO_ID = 1;             // Our radio's id.
const static uint8_t DESTINATION_RADIO_ID = 0; // Id of the radio we will transmit to.
const static uint8_t PIN_RADIO_CE = 9;
const static uint8_t PIN_RADIO_CSN = 10;

void(* resetFunc) (void) = 0;//declare reset function at address 0

struct RadioPacket // Any packet up to 32 bytes can be sent.
{
  uint8_t FromRadioId;
  uint32_t OnTimeMillis;
  uint32_t FailedTxCount;
};

NRFLite _radio;
RadioPacket _radioData;
int counter;
int fail;
void setup()
{
  Serial.begin(115200);
Serial.println("Si inicia");
  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
  {
    Serial.println("Cannot communicate with radio");
    resetFunc(); //call reset
    while (1); // Wait here forever.
  }

  _radioData.FromRadioId = RADIO_ID;
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
    digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
    delay(200);
     digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
}

void loop()
{
  _radioData.OnTimeMillis = millis();

if ((digitalRead(6)==1)&& (digitalRead(7)==1)){
  Serial.println("Estado 3");
  counter = 3;
  digitalWrite(4,1);
  digitalWrite(3,0);
  digitalWrite(2,0);
}

if ((digitalRead(6)==0)&& (digitalRead(7)==1)){
  Serial.println("Estado 1");
  counter = 1;
  digitalWrite(4,0);
  digitalWrite(3,0);
  digitalWrite(2,1);
}
if ((digitalRead(6)==1)&& (digitalRead(7)==0)){
  Serial.println("Estado 2");
  counter = 2;
  digitalWrite(4,0);
  digitalWrite(3,1);
  digitalWrite(2,0);
}

  Serial.println("Sending ");


  if (_radio.send(DESTINATION_RADIO_ID, &counter, sizeof(_radioData))) // Note how '&' must be placed in front of the variable name.
  {

    Serial.print(counter);
    Serial.println("...Success");
  }
  else
  {
    Serial.println("...Failed");
    _radioData.FailedTxCount++;
    fail++;
    if (fail > 10) {
      resetFunc(); //call reset
    }

  }

  delay(100);

}
