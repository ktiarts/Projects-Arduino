#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define TINY_GSM_MODEM_SIM900
#include <TinyGPS.h>
#include <TinyGsmClient.h>

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "XavierCharly"
#define AIO_KEY         "9a50cd4c378e420f9f41fd9451837f27"


#define OLED_RESET 13
#define SerialMon Serial
#define SerialAT Serial1

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


TinyGPS gps;
TinyGsm modem(SerialAT);
TinyGsmClient client(modem);

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/recibido");
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff");

Adafruit_SSD1306 display(OLED_RESET);
const char apn[]  = "entel.pe";
const char user[] = "";
const char pass[] = "";


long lastReconnectAttempt = 0;

void setup() {

  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);

  // Set GSM module baud rate
  SerialAT.begin(115200);
  delay(3000);

  Serial2.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(500);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Initializing modem...");
  display.display();
  SerialMon.println("Initializing modem...");

  modem.restart();

  String modemInfo = modem.getModemInfo();
  display.print("Modem...");
  display.display();
  SerialMon.print("Modem: ");
  SerialMon.println(modemInfo);
  display.println(modemInfo);
  display.display();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  SerialMon.print("Waiting for network...");
  display.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    display.println("Fail");
    display.display();
    SerialMon.println(" fail");
    while (true);
  }
  display.println("Ok");
  display.display();
  SerialMon.println(" OK");
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  SerialMon.print("Connecting to ");
  display.print("Connecting to ");
  display.display();
  display.print(apn);
  display.display();
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, user, pass)) {
    SerialMon.println(" fail");
    display.println("Fail ");
    display.display();
    while (true);
  }

  SerialMon.println(" OK");
  display.println("Ok");
  display.display();
  // MQTT Broker setup
  mqtt.subscribe(&onoffbutton);

}
uint32_t x = 0;



void loop() {
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &onoffbutton) {
      SerialMon.print(F("Got: "));
      SerialMon.println((char *)onoffbutton.lastread);
    }
  }

  for (unsigned long start = millis(); millis() - start < 1000;) {
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
    gps.f_get_position(&flat, &flon, &age);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("LAT= ");
    display.display();
    Serial.print("LAT=");
    display.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    display.display();
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    display.print("LON= ");
    display.display();
    Serial.print(" LON=");
    display.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    display.display();
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
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
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("CSUM ERR= ");
  display.display();
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
  display.println("failed");
  display.display();
  if (chars == 0) {
    Serial.println("** No characters received from GPS: check wiring **");
  }
  SerialMon.print(F("\nSending photocell val "));
  SerialMon.print(x);
  SerialMon.print("...");
  if (! photocell.publish(x++)) {
    SerialMon.println(F("Failed"));
  } else {
    SerialMon.println(F("OK!"));
  }
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Connecting to MQTT... ");
  display.display();
  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    SerialMon.println(mqtt.connectErrorString(ret));
    SerialMon.println("Retrying MQTT connection in 5 seconds...");
    display.println("Retrying MQTT connection in 5 seconds...");
    display.display();
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  SerialMon.println("MQTT Connected!");
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("MQTT Connected! ");
  display.display();
}
