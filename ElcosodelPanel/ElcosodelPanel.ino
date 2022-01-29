#include <ESP8266WiFi.h>
#include <MQTT.h>

//const char ssid[] = "PanelY2K";
//const char pass[] = "87654321";

const char ssid[] = "TezlaX";
const char pass[] = "RataInmunda2018";

WiFiClient net;
MQTTClient client;
#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial14.h>
#include <fonts/Droid_Sans_24.h>
#include <fonts/NuevaLetra.h>
#include <fonts/letrax.h>
#include <fonts/letra3.h>
volatile byte half_revolutions;
unsigned int rpm;
unsigned long timeold;
int reseteobro = 0;
SPIDMD dmd(3, 3); // DMD controls the entire display
DMD_TextBox box(dmd);  // "box" provides a text box to automatically write to/scroll the display

void connect() {
  reseteobro = 0;
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
    
  }
  Serial.print("\nconnecting...");
  while (!client.connect("ZBgtR84y", "", "")) {
    Serial.print(".");
    delay(1000);
    reseteobro++;
    if (reseteobro == 2){
      ESP.reset();
    }
  }
  Serial.println("\nconnected!");
    client.subscribe("/quefome34");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
Serial.println("incoming: " + topic + " - " + payload);
  
int pos1=payload.lastIndexOf('!');
int pos2=payload.lastIndexOf('+');
int pos3=payload.lastIndexOf('#');
int pos4=payload.lastIndexOf('$');
int pos5=payload.lastIndexOf('%');
int pos6=payload.lastIndexOf('&');
int pos7=payload.lastIndexOf('/');
int pos8=payload.lastIndexOf('(');
int pos9=payload.lastIndexOf(')');
int pos10=payload.lastIndexOf('=');
int pos11=payload.lastIndexOf('?');
int pos12=payload.lastIndexOf('¡');
int pos13=payload.lastIndexOf('¿');
int pos14=payload.lastIndexOf('*');

String fuentex = payload.substring(pos1+1,pos2);   
String fuentex1 = payload.substring(pos2+1,pos3);
String fuentex2 = payload.substring(pos3+1,pos4);

String xv1 = payload.substring(pos4+1,pos5);
String yv1 = payload.substring(pos5+1,pos6);
String xv2 = payload.substring(pos6+1,pos7);
String yv2 = payload.substring(pos7+1,pos8);
String xv3 = payload.substring(pos8+1,pos9);
String yv3 = payload.substring(pos9+1,pos10);

String value1 = payload.substring(pos10+1,pos11);
String value2 = payload.substring(pos11+1,pos12);
String value3 = payload.substring(pos12+1,pos13);

String brillox = payload.substring(pos13+1,pos14);
int brillo = brillox.toInt();

int fuente = fuentex.toInt();
int fuente1 = fuentex1.toInt();
int fuente2 = fuentex2.toInt();

int x1= xv1.toInt();
int y1= yv1.toInt();
int x2= xv2.toInt();
int y2= yv2.toInt();
int x3= xv3.toInt();
int y3= yv3.toInt();
dmd.setBrightness(brillo);
  box.clear();
  
  if ( fuente == 1) {
    dmd.selectFont(Arial14);
  }
  if ( fuente == 2) {
    dmd.selectFont(Droid_Sans_24);
  }
  if ( fuente == 3) {
    dmd.selectFont(nuevaletra);
  }
  if ( fuente == 4) {
    dmd.selectFont(new_Font);
  }
  if ( fuente == 5) {
    dmd.selectFont(letra3);
  }
  if ( fuente == 6) {
    dmd.selectFont(letra3);
  }
  if ( fuente == 7) {
    dmd.selectFont(letra3);
  }

  dmd.drawString(x1, y1, value1);

  if ( fuente1 == 1) {
    dmd.selectFont(Arial14);
  }
  if ( fuente1 == 2) {
    dmd.selectFont(Droid_Sans_24);
  }
  if ( fuente1 == 3) {
    dmd.selectFont(nuevaletra);
  }
  if ( fuente1 == 4) {
    dmd.selectFont(new_Font);
  }
  if ( fuente1 == 5) {
    dmd.selectFont(letra3);
  }
  if ( fuente1 == 6) {
    dmd.selectFont(letra3);
  }
  if ( fuente1 == 7) {
    dmd.selectFont(letra3);
  }
  
  dmd.drawString(x2, y2 ,value2);
  
  if ( fuente2 == 1) {
    dmd.selectFont(Arial14);
  }
  if ( fuente2 == 2) {
    dmd.selectFont(Droid_Sans_24);
  }
  if ( fuente2 == 3) {
    dmd.selectFont(nuevaletra);
  }
  if ( fuente2 == 4) {
    dmd.selectFont(new_Font);
  }
  if ( fuente2 == 5) {
    dmd.selectFont(letra3);
  }
  if ( fuente2 == 6) {
    dmd.selectFont(letra3);
  }
  if ( fuente2 == 7) {
    dmd.selectFont(letra3);
  }

  dmd.drawString(x3, y3, value3);
  
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  client.begin("192.168.0.106", net);
  client.onMessage(messageReceived);
  connect();
  dmd.begin();
  pinMode(5,INPUT);
  attachInterrupt(5,rpm_fun, RISING);
  half_revolutions = 0;
  rpm = 0;
  timeold = 0;
  //  Serial.println("Inicio de pantalla");
  //  box.print("Listo");
  //  delay(1000);
  //  box.clear();
  //  dmd.clearScreen();
  //  int n = 000;
  //  box.print(n);
  //  dmd.selectFont(Arial14);
  //  dmd.drawString(30, 15, "/rpm");

}
void loop()
{
  client.loop();
    delay(50);
  if (!client.connected()) {
    connect();
  }
    if (half_revolutions >= 2) {
      rpm = 30 * 1000 / (millis() - timeold) * half_revolutions;
      timeold = millis();
      half_revolutions = 0;
      Serial.println(rpm, DEC);
      String errepeeme = String(rpm);
      client.publish("/OqgRS7ZRLoF6I2s", errepeeme);
       }
  
}
void rpm_fun()
{
  half_revolutions++;
}

