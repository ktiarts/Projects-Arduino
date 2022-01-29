

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(9, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
  pinMode(10, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {
    int recibir = Serial.read();

    switch (recibir) {
      
      case 'a' :
        //adelante
        digitalWrite(6, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(3, HIGH);
        break;

      case 'd':
          //atras
          digitalWrite(6, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(3, LOW);
        break;

      case 'c':
          //derecha
          digitalWrite(6, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(3, LOW);
        break;

      case 'b':
          //izquierda
          digitalWrite(6, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, HIGH);
        break;

      case 'e':
          //parar
          digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        break;
        case 'k':
          //parar
int k=Serial.parseInt();
analogWrite(9,k);     
analogWrite(10,k);      
        break;
    }
    }
}
