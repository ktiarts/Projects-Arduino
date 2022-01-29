// The setup() function runs once each time the micro-controller starts
void setup()
{
	//wdt_disable();
	pinMode(2, OUTPUT); //led1
	pinMode(3, OUTPUT); //led2
  pinMode(4, OUTPUT);
}

// Add the main program code into the continuous loop() function
void loop()
{
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  delay(300);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  delay(10000);
  }

