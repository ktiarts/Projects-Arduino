int boton = 7;
int led = 9;

void setup() {
  // put your setup code here, to run once:
pinMode(7,INPUT);
pinMode(9,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int botonx = digitalRead(boton);
if(botonx == 1 ){
delay(500);
for( int x = 0 ; x <=255 ; x = x + 1){
   analogWrite(led,x);
   delay(10);
}
  
}


}
