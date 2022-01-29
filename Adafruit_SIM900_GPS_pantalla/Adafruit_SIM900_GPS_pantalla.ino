#define TINY_GSM_MODEM_SIM900
#include <TinyGsmClient.h>

#define SerialMon Serial
#define SerialAT Serial1
const char apn[]  = "entel.pe";
const char user[] = "";
const char paSerial2[] = "";

#include <MQTT.h>

TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
MQTTClient clientx;


//-------------------- GPS CONFIG --------------------------

#include <TinyGPS.h>
TinyGPS gps;

//-------------------- GPS CONFIG --------------------------

//-------------------- Pantalla --------------------------

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//--------------------- Pantalla --------------------------

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
  if (!modem.gprsConnect(apn, user, paSerial2)) {
    SerialMon.println(" fail");
    while (true);
  }
  SerialMon.println(" OK");

  
  clientx.begin("io.adafruit.com", client);
  clientx.onMessage(messageReceived);
  connect();


  //---------------- config GPS----------------------
  Serial2.begin(9600);
  //-------------------- GPS CONFIG --------------------------

//---------------- Pantalla ------------------

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();
  display.clearDisplay();
  

}



uint32_t x = 0;


void loop() {
 clientx.loop();
delay(10);  // <- fixes some issues with WiFi stability

if (!clientx.connected()) {
    connect();
  }
     String gsmLoc = modem.getGsmLocation();
  clientx.publish("XavierCharly/feeds/recibido",gsmLoc);
//
//  //------------------------------------------------ Nos metemos por aca con el GPS csm  --------------------------------------------------
//  bool newData = false;
//  unsigned long chars;
//  unsigned short sentences, failed;
//
//  // For one second we parse GPS data and report some key values
//  for (unsigned long start = millis(); millis() - start < 1000;)
//  {
//    while (Serial2.available())
//    {
//      char c = Serial2.read();
//      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
//      if (gps.encode(c)) // Did a new valid sentence come in?
//        newData = true;
//    }
//  }
//
//  if (newData)
//  {
//    float flat;
//    float flon;
//    unsigned long age;
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
//  //  
//
//   // flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6;
//
//    Serial.print(" LON=");
//    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
//    
//    Serial.print(F("\nSending GPS val LON= "));
//    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
//    Serial.print("...");
//    clientx.publish("XavierCharly/feeds/recibido",Position);
//    
//    Serial.print(" SAT=");
//    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
//    Serial.print(" PREC=");
//    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
//  }
// String error = String(failed);
//  gps.stats(&chars, &sentences, &failed);
//  Serial.print(" CHARS=");
//  Serial.print(chars);
//  Serial.print(" SENTENCES=");
//  Serial.print(sentences);
//  Serial.print(" CSUM ERR=");
//  Serial.println(failed);
//  clientx.publish("XavierCharly/feeds/error",error);
//  if (chars == 0){
//    Serial.println("** No characters received from GPS: check wiring **");
//  }
//  //------------------------------------------------ Nos metemos por aca con el GPS csm  --------------------------------------------------
delay(4000);
}
