#define TINY_GSM_MODEM_SIM900
#include <TinyGsmClient.h>

#define SerialMon Serial
#define SerialAT Serial1
const char apn[]  = "entel.pe";
const char user[] = "";
const char paSerial2[] = "";

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "XavierCharly"
#define AIO_KEY         "9a50cd4c378e420f9f41fd9451837f27"


TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/recibido");
Adafruit_MQTT_Publish photocellx = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/recibido1");
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff");

#define LED_PIN 13
int ledStatus = LOW;

long lastReconnectAttempt = 0;


//-------------------- GPS CONFIG --------------------------

#include <TinyGPS.h>
TinyGPS gps;

//-------------------- GPS CONFIG --------------------------
void setup() {
  pinMode(LED_PIN, OUTPUT);

  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);

  // Set GSM module baud rate
  SerialAT.begin(115200);
  delay(3000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  modem.restart();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem: ");
  SerialMon.println(modemInfo);

  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");

  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println(" fail");
    while (true);
  }
  SerialMon.println(" OK");

  SerialMon.print("Connecting to ");
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, user, paSerial2)) {
    SerialMon.println(" fail");
    while (true);
  }
  SerialMon.println(" OK");

  mqtt.subscribe(&onoffbutton);

  //---------------- config GPS----------------------
  Serial2.begin(9600);
  //-------------------- GPS CONFIG --------------------------
}



uint32_t x = 0;


void loop() {

  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
    }
  }


  //------------------------------------------------ Nos metemos por aca con el GPS csm  --------------------------------------------------
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial2.available())
    {
      char c = Serial2.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    //flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);

    Serial.print(F("\nSending GPS val LAT= "));
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print("...");
    if (! photocell.publish(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6)) {
      Serial.println(F("Failed"));
    } 
    else {
      Serial.println(F("OK!"));
    }
   // flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6;

    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    
    Serial.print(F("\nSending GPS val LON= "));
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print("...");
    if (! photocellx.publish(flon)) {
      Serial.println(F("Failed"));
    } 
    else {
      Serial.println(F("OK!"));
    }
    
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  }

  gps.stats(&chars, &sentences, &failed);
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
  
  if (chars == 0){
    Serial.println("** No characters received from GPS: check wiring **");
  }
//Serial.print(F("\nCodigo de error "));
//    Serial.print("** No characters received from GPS: check wiring **");
//    Serial.print("...");
//    if (! photocell.publish("** No characters received from GPS: check wiring **")) {
//      Serial.println(F("Failed"));
//    } 
//    else {
//      Serial.println(F("OK!"));
//    }

    
  //------------------------------------------------ Nos metemos por aca con el GPS csm  --------------------------------------------------

}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 10;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}

