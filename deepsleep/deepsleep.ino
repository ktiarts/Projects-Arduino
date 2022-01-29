void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);
pinMode(D4,OUTPUT);
  // Wait for serial to initialize.
  while(!Serial) { }
  
  Serial.println("I'm awake.");

  Serial.println("Going into deep sleep for 20 seconds");
digitalWrite(D4,LOW);
delay(200);
digitalWrite(D4,HIGH);
delay(200);
digitalWrite(D4,LOW);
delay(200);
digitalWrite(D4,HIGH);
delay(200);
digitalWrite(D4,LOW);
delay(200);
digitalWrite(D4,HIGH);
delay(200);
digitalWrite(D4,LOW);
delay(200);
digitalWrite(D4,LOW);
delay(200);
digitalWrite(D4,HIGH);
delay(200);
digitalWrite(D4,LOW);
delay(200);
digitalWrite(D4,HIGH);
delay(200);
digitalWrite(D4,LOW);
delay(200);
digitalWrite(D4,HIGH);
delay(200);
digitalWrite(D4,LOW);
delay(200);
digitalWrite(D4,HIGH);
delay(3000);

  
  ESP.deepSleep(0,WAKE_RF_DISABLED); // 20e6 is 20 microseconds
}

void loop() {
}
