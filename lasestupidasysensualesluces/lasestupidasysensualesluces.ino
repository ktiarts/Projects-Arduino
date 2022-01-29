/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(10,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    if (results.value == 16753245){// 1
      analogWrite(10,255);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16736925){// 2
      analogWrite(5,255);
    irrecv.resume(); // Receive the next value
    }
    if (results.value == 16769565){// 3
      analogWrite(6,255);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16720605){// 4
      analogWrite(10,170);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16712445){// 5
      analogWrite(5,170);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16761405){// 6
      analogWrite(6,170);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16769055){// 7
      analogWrite(10,85);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16754775){// 8
      analogWrite(5,85);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16748655){// 9
      analogWrite(6,85);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16738455){// *
      analogWrite(10,0);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16750695){// 0
      analogWrite(5,0);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16756815){// #
      analogWrite(6,0);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16718055 ){// up
      analogWrite(9,255);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16734885 ){// right
      analogWrite(9,170);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16730805 ){// down
      analogWrite(9,85);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16716015 ){// left
      analogWrite(9,0);
      irrecv.resume(); // Receive the next value
    }
    if (results.value == 16726215 ){// left
//      analogWrite(9,0);
    secuenciapsico();
   //   irrecv.resume(); // Receive the next value
    }


    
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}

int t = 50;
void secuenciapsico(){
  irrecv.resume();
  apaga();

  delay(1000);
  for (int x= 0; x<255; x++){
    analogWrite(10,x);
     if (irrecv.decode(&results)) goto salir;
    delay(t);
  }
  for (int x= 0; x<255; x++){
    analogWrite(5,x);
    analogWrite(10,255-x);
     delay(t);
  }
  for (int x= 0; x<255; x++){
    analogWrite(6,x);
    analogWrite(5,255-x);
     delay(t);
  }
  for (int x= 0; x<255; x++){
    analogWrite(9,x);
     delay(t);
  }
  for (int x= 0; x<255; x++){
    analogWrite(10,x);
    delay(t);
  }
  for (int x= 0; x<255; x++){
    analogWrite(5,x);
     analogWrite(9,255-x);
    delay(t);
  }
  for (int x= 0; x<255; x++){
    analogWrite(6,x);
    delay(t);
  }

salir:
  apaga();
  Serial.println("salida");
  
}


void apaga()
{
  analogWrite(10,0);
  analogWrite(5,0);
  analogWrite(6,0);
  analogWrite(9,0);  
}
