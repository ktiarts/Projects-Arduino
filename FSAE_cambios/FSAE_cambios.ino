void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Programa para control de embrague y cambios");
Serial.println("Se inicializo el serial");
Serial.println("Declarando puertos: ");
  pinMode(9, OUTPUT); //Trico 1 A
  Serial.println("Puerto Digital 3");
  pinMode(10, OUTPUT); //Trico 1 B
  Serial.println("Puerto Digital 4");
  pinMode(5, OUTPUT); //Trico 2 A
  Serial.println("Puerto Digital 5");
  pinMode(6, OUTPUT); //Trico 2 B
  Serial.println("Puerto Digital 6");
Serial.print("  Listo!");
Serial.print("Inicio del Loop");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (Serial.available() > 0){    
    char recibir = Serial.read();
    switch (recibir){
    case 'w': gearboxup(); delay(100); gearboxdown(); delay(100); gearboxstop(); break;
    case 's': gearboxdown(); delay(100); gearboxup(); delay(100); gearboxstop(); break;
    
    }
  }
}
void gearboxup(){ Serial.println("cambio arriba");        digitalWrite(9, 1);digitalWrite(10, 0);}
void gearboxdown(){ Serial.println("cambio abajo");       digitalWrite(9, 0);digitalWrite(10, 1);}
//void clutchpull(){ Serial.println("embrague arriba");     digitalWrite(10, 1);digitalWrite(9, 0);}
//void clutchpush(){ Serial.println("embrague abajo");      digitalWrite(10, 0);digitalWrite(9, 1);}
void gearboxstop(){ Serial.println("stop cambio");        digitalWrite(9, 0);digitalWrite(10, 0);} 
//void clutchstop(){ Serial.println("stop embrague");       digitalWrite(5, 0);digitalWrite(6, 0);}


