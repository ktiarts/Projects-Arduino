#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>

#define SerialMon Serial
#include <SoftwareSerial.h>
SoftwareSerial SerialAT(4, 3); // RX, TX
//SoftwareSerial SerialGPS(8, 9); // RX, TX
const char apn[]  = "entel.pe";
const char user[] = "";
const char paSerialGPS[] = "";

#include <MQTT.h>

TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
MQTTClient clientx;


//-------------------- GPS CONFIG --------------------------

#include <TinyGPS.h>
TinyGPS gps;

//-------------------- GPS CONFIG --------------------------

//----------- Pantalla---------------

unsigned long lastMillis = 0;

void connect() {

  Serial.print("\nconnecting...");
  while (!clientx.connect("GPS", "XavierCharly", "f6a01ca794fe496eb233e37d6b7b0ab9")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  clientx.subscribe("XavierCharly/feeds/recibido");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {

  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);

  // Set GSM module baud rate
  SerialAT.begin(115200);
  delay(3000);
//------------------- Pantalla----------
 
//--------------- Pantalla -------------

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  modem.restart();


  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem: ");
  SerialMon.println(modemInfo);

  
  SerialMon.print("Waiting for network...");

  if (!modem.waitForNetwork()) {
    SerialMon.println(" fail");

    while (true);
  }
  SerialMon.println(" OK");

  SerialMon.print("Connecting to ");
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, user, paSerialGPS)) {
    SerialMon.println(" fail");
    while (true);
  }
  SerialMon.println(" OK");

  clientx.begin("io.adafruit.com", client);
  clientx.onMessage(messageReceived);
  connect();


  //---------------- config GPS----------------------
//  SerialGPS.begin(9600);
  //-------------------- GPS CONFIG --------------------------
}
uint32_t x = 0;


void loop() {
  clientx.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!clientx.connected()) {
    connect();
  }
String gsmLoc = modem.getGsmLocation();
clientx.publish("XavierCharly/feeds/gpslatlng", gsmLoc);
  


  //------------------------------------------------ Nos metemos por aca con el GPS csm  --------------------------------------------------
//  bool newData = false;
//  unsigned long chars;
//  unsigned short sentences, failed;
//
//  // For one second we parse GPS data and report some key values
//  for (unsigned long start = millis(); millis() - start < 1000;)
//  {
//    while (SerialGPS.available())
//   {
//     char c = SerialGPS.read();
//     // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
//      if (gps.encode(c)) // Did a new valid sentence come in?
//       newData = true;
//    }
// }
//
//  if (newData)
//  {
//    float flat;
//    float flon;
//   unsigned long age;
//    //flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6;
//    gps.f_get_position(&flat, &flon, &age);
//    String Latitud = String(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
//    String Longitud = String(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
//    String Position = String ( Latitud + "," + Longitud );
//    Serial.print("LAT=");
//    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
//
//    Serial.print(F("\nSending GPS val LAT= "));
//    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
//    Serial.print("...");
//
//    //  clientx.publish("/hello",Latitud);
//    // flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6;
//
//    Serial.print(" LON=");
//    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
//
//    Serial.print(F("\nSending GPS val LON= "));
//    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
//    Serial.print("...");
//    clientx.publish("XavierCharly/feeds/gpslatlng", Position);
//    
//    Serial.print(" SAT=");
//    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
//    Serial.print(" PREC=");
//    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
//  }
//  String error = String(failed);
//  gps.stats(&chars, &sentences, &failed);
// Serial.print(" CHARS=");
//  Serial.print(chars);
//  Serial.print(" SENTENCES=");
//  Serial.print(sentences);
//  Serial.print(" CSUM ERR=");
//  Serial.println(failed);
//  //clientx.publish("XavierCharly/feeds/error", error);
//  if (chars == 0) {
//    Serial.println("** No characters received from GPS: check wiring **");
//  }
//  //------------------------------------------------ Nos metemos por aca con el GPS csm  --------------------------------------------------

    delay(2300);

}
