
// This example uses an Adafruit Huzzah ESP8266
// to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

#include <ESP8266WiFi.h>
#include <MQTTClient.h>

const char *ssid = "team";
const char *pass = "volvitorojo";

WiFiClientSecure net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect(); // <- predefine connect() for setup()

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  client.begin("broker.shiftr.io", 8883, net); // MQTT brokers usually use port 8883 for secure connections
  connect();
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
}
  //Declaracion de Variables
  void connect() {
    Serial.print("checking wifi...");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(1000);
    }

    Serial.print("\nconnecting...");
    while (!client.connect("oka", "5c6cbb7a", "53c3b38f645c9d61")) {
      Serial.print(".");
      delay(1000);
    }

    Serial.println("\nconnected!");

    client.subscribe("/lampa");
    // client.unsubscribe("/example");
  }
  void loop() {
    client.loop();
    delay(10); // <- fixes some issues with WiFi stability

    if (!client.connected()) {
      connect();
    }

    // publish a message roughly every second.
    if (millis() - lastMillis > 1) {
      lastMillis = millis();
      client.publish("/valores.n", "holi");
    }


  }

  void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
    Serial.print("Valor Neto :     ");
    //  Serial.print(topic);
    //  Serial.print(" - ");
    Serial.print(payload);
    Serial.println();

    int a = payload.toInt();
    if (a == 1) {
      digitalWrite(4, LOW);
    }
    if (a == 0) {
      digitalWrite(4, HIGH);
    }

  }
