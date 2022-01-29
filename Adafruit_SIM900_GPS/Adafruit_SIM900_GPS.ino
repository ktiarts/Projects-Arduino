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


unsigned long lastMillis = 0;

void connect() {

  Serial.print("\nconnecting...");
  while (!clientx.connect("GPS", "XavierCharly", "f6a01ca794fe496eb233e37d6b7b0ab9")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  //clientx.subscribe("/hello");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void(* resetFunc) (void) = 0;//declare reset function at address 0

void setup() {

  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);

  // Set GSM module baud rate
  TinyGsmAutoBaud(SerialAT);
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
    resetFunc(); //call reset 
    while (true);
  }
  SerialMon.println(" OK");

  SerialMon.print("Connecting to ");
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, user, paSerial2)) {
    SerialMon.println(" fail");
    resetFunc(); //call reset 
    while (true);
  }
  SerialMon.println(" OK");

  
  clientx.begin("broker.shiftr.io", client);
  clientx.onMessage(messageReceived);
  connect();

uint32_t x = 0;
}


void loop() {
 clientx.loop();
delay(10);  // <- fixes some issues with WiFi stability

if (!clientx.connected()) {
    connect();
  }
   String gsmLoc = modem.getGsmLocation();

   
    clientx.publish("XavierCharly/feeds/gpslatlng",gsmLoc);
    delay(200);
}
