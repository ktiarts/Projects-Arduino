
#include <ESP32Encoder.h>
#include <PID_v1.h>

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

#include <WiFi.h>
#include <MQTT.h>

int revx= 0;

const char ssid[] = "MOVISTAR_1B18";
const char pass[] = "mariovolvitorojo9940";

WiFiClient net;
MQTTClient client;

ESP32Encoder encoder1;
ESP32Encoder encoder2;
ESP32Encoder encoder3;
ESP32Encoder encoder4;

unsigned long previousMillis = 0; 

String one = "";
String two = "";
String three = "";
String four = "";

 int RPM1 = 0;
 int RPM2 = 0;
 int RPM3 = 0;
 int RPM4 = 0;
 
double Setpoint1, Input1, Output1;
double Setpoint2, Input2, Output2;
double Setpoint3, Input3, Output3;
double Setpoint4, Input4, Output4;

double Kp1=150, Ki1=900, Kd1=0.15;
double Kp2=150, Ki2=900, Kd2=0.15;
double Kp3=150, Ki3=900, Kd3=0.15;
double Kp4=150, Ki4=900, Kd4=0.15;

PID myPID1(&Input1, &Output1, &Setpoint1, Kp1, Ki1, Kd1, DIRECT);
PID myPID2(&Input2, &Output2, &Setpoint2, Kp2, Ki2, Kd2, DIRECT);
PID myPID3(&Input3, &Output3, &Setpoint3, Kp3, Ki3, Kd3, DIRECT);
PID myPID4(&Input4, &Output4, &Setpoint4, Kp4, Ki4, Kd4, DIRECT);

int peve1;
int peve2;
int peve3;
int peve4;

const int freq = 12000;
const int ledChannel = 0;
const int resolution = 12;
unsigned long currentMillis;

String inputString = "";
bool stringComplete = false;

int angulo;
int vmax;
int pax;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("BAT-CAR", "", "")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");
  client.subscribe("/a");
  client.subscribe("/mov1");
  client.subscribe("/mov2");
  client.subscribe("/mov3");
  client.subscribe("/mov4");

  
  //client.subscribe("/a");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
 if (topic == "/a"){
 revx = payload.toInt();
 }

  if (topic == "/mov1"){

angulo = payload.toInt();


  }

  
}

void setup(){
	
	Serial.begin(115200);
   WiFi.begin(ssid, pass);
  client.begin("192.168.1.100", net);
  client.onMessage(messageReceived);
  connect();
  ESP32Encoder::useInternalWeakPullResistors=UP;
  
	encoder1.attachHalfQuad(27, 14);
	encoder2.attachHalfQuad(26, 25);
  encoder3.attachHalfQuad(32, 33);
  encoder4.attachHalfQuad(34, 35);
		
	// set starting count value after attaching
  encoder1.setCount(0);
  encoder2.setCount(0);
  encoder3.setCount(0);
  encoder4.setCount(0);

  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);
  ledcSetup(2, freq, resolution);
  ledcSetup(3, freq, resolution);

  ledcSetup(4, freq, resolution);
  ledcSetup(5, freq, resolution);
  ledcSetup(6, freq, resolution);
  ledcSetup(7, freq, resolution);
  
  ledcAttachPin(19, 0);
  ledcAttachPin(18, 1);
  ledcAttachPin(5,  2);
  ledcAttachPin(4,  3);
  
  ledcAttachPin(2,  4);
  ledcAttachPin(15, 5);
  ledcAttachPin(13, 6);
  ledcAttachPin(12, 7);

myPID1.SetOutputLimits(0,4095);
myPID2.SetOutputLimits(0,4095);
myPID3.SetOutputLimits(0,4095);
myPID4.SetOutputLimits(0,4095);

myPID1.SetSampleTime(1);
myPID2.SetSampleTime(1);
myPID3.SetSampleTime(1);
myPID4.SetSampleTime(1);

myPID1.SetMode(AUTOMATIC);
myPID2.SetMode(AUTOMATIC);
myPID3.SetMode(AUTOMATIC);
myPID4.SetMode(AUTOMATIC);


}

void loop(){
  client.loop();
  delay(5);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
  if (stringComplete) {
    Serial.println(inputString);
    // 012345678
    String string1 =inputString.substring(0,2);
    String string2 =inputString.substring(3,5);
    String string3 =inputString .substring(6,8);
    String string4 =inputString .substring(9,11);
     //Setpoint = string1.toDouble();
     //Setpoint = string2.toDouble();
     //Setpoint = string3.toDouble();
     //Setpoint = string4.toDouble();
    // clear the string:
    inputString = "";
    
    stringComplete = false;
  } 
  
    serialEvent();
    
    currentMillis = millis();
    
    int xc1 = abs (encoder1.getCount());
    int xc2 = abs (encoder2.getCount());
    int xc3 = abs (encoder3.getCount());
    int xc4 = abs (encoder4.getCount());
    
    int interval = 8; // 100 ms
    
    int CPR = 200; // calculated counts per revolutions

  //analogWrite(PIN_OUTPUT, Output);
    
    if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  
    RPM1 = ((xc1) / interval *(60*8)) / CPR;
    RPM2 = ((xc2) / interval *(60*8)) / CPR;
    RPM3 = ((xc3) / interval *(60*8)) / CPR;
    RPM4 = ((xc4) / interval *(60*8)) / CPR;
    
    encoder1.clearCount();
    encoder2.clearCount();
    encoder3.clearCount();
    encoder4.clearCount();
    }

if ((angulo >= 0)&&(angulo < 45)){
pax = map(angulo, 0, 45, revx, 0);
RR1(revx,"up");
RR2(pax,"down");
RR3(revx,"up");
RR4(pax,"down");
}

if ((angulo > 45)&&(angulo < 90)){
pax = map(angulo, 45, 90, 0, revx);
RR1(revx,"up");
RR2(pax,"up");
RR3(revx,"up");
RR4(pax,"up");
}

if (angulo == 90){
RR1(revx,"up");
RR2(revx,"up");
RR3(revx,"up");
RR4(revx,"up");
}
if ((angulo > 90)&&(angulo < 135)){
pax = map(angulo, 90, 135, revx, 0);
RR1(pax,"up");
RR2(revx,"up");
RR3(pax,"up");
RR4(revx,"up");
}
if ((angulo > 135)&&(angulo <= 180)){
pax = map(angulo, 135, 180, 0, revx);
RR1(pax,"down");
RR2(revx,"up");
RR3(pax,"down");
RR4(revx,"up");
}
    


 Serial.print ( RPM1);
 Serial.print ("  ");
 Serial.print (Output1);
 Serial.print ("  ");
 
 Serial.print ( RPM2);
 Serial.print ("  ");
 Serial.print (Output2);
 Serial.print ("  ");

 Serial.print ( RPM3);
 Serial.print ("  ");
 Serial.print (Output3);
 Serial.print ("  ");
 
 Serial.print ( RPM4);
 Serial.print ("  ");
 Serial.print (Output4);
 Serial.println ("  ");

}


void RR1(int rev,String sense){
  Setpoint1=rev;
  Input1 = RPM1;
 myPID1.Compute();
  Serial.print ( rev);
 Serial.print ("  ");
 Serial.print ( RPM1);
 Serial.print ("  ");
 Serial.print (Output1);
 Serial.print ("  ");
if (sense == "up")  {ledcWrite(0, Output1); ledcWrite(1, 0);}
if (sense == "down"){ledcWrite(0, 0      ); ledcWrite(1, Output1);}
  
}

void RR2(int rev,String sense){
  Setpoint2=rev;
Input2 = RPM2;
myPID2.Compute();
  Serial.print ( rev);
 Serial.print ("  ");
  Serial.print ( RPM2);
 Serial.print ("  ");
 Serial.print (Output2);
 Serial.print ("  ");
if (sense == "down"){ledcWrite(2, Output2); ledcWrite(3, 0);}
if (sense == "up")  {ledcWrite(2, 0      ); ledcWrite(3, Output2);}
  
}

void RR4(int rev,String sense){
  Setpoint4=rev;
Input4 = RPM4;
myPID4.Compute();
  Serial.print ( rev);
 Serial.print ("  ");
 Serial.print ( RPM4);
 Serial.print ("  ");
 Serial.print (Output3);
 Serial.print ("  ");
if (sense == "down"){ledcWrite(4, Output4); ledcWrite(5, 0);    }
if (sense == "up")  {ledcWrite(4, 0      ); ledcWrite(5, Output4);}
  
}

void RR3(int rev,String sense){
  Setpoint3=rev;
Input3 = RPM3;
myPID3.Compute();
  Serial.print ( rev);
 Serial.print ("  ");
 Serial.print ( RPM3);
 Serial.print ("  ");
 Serial.print (Output4);
 Serial.println ("  ");
if (sense == "down"){ledcWrite(6, Output3); ledcWrite(7, 0);    }
if (sense == "up")  {ledcWrite(6, 0      ); ledcWrite(7, Output3);}
  
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
