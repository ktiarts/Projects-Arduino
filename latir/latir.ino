void setup() {
  // put your setup code here, to run once:

}
int t1 = 6;
int t2 = 3;
int low = 0;
int med = 20;
int hi  = 255;

void loop() {
  int fadeValue1;
  // put your main code here, to run repeatedly:
  // fade out from max to min in increments of 5 points:
  for (int fadeValue = hi ; fadeValue >= low; fadeValue--)
  {
    analogWrite(9, fadeValue);
    fadeValue1 = fadeValue - 100;
    if (fadeValue1 < 1 ) {
      fadeValue1 = 1;
    }
    analogWrite(6, fadeValue1);

    delay(t1);
  }
  for (int fadeValue = low; fadeValue <= hi; fadeValue++)
  {
    analogWrite(9, fadeValue);
    fadeValue1 = fadeValue - 100;
    if (fadeValue1 < 1 ) {
      fadeValue1 = 1;
    }
    analogWrite(6, fadeValue1);
    delay(t2);
  }
  for (int fadeValue = hi ; fadeValue >= med; fadeValue--)
  {
    analogWrite(9, fadeValue);    
    fadeValue1=fadeValue-25;
       if (fadeValue1 < 1 ){
       fadeValue1=1; 
       }
       analogWrite(6, fadeValue1);
    delay(t2);
  }

  for (int fadeValue = med ; fadeValue <= hi; fadeValue++)
  {
    analogWrite(9, fadeValue);    
    fadeValue1=fadeValue-100;
       if (fadeValue1 < 1 ){
       fadeValue1=1; 
       }
       analogWrite(6, fadeValue1);
    delay(t1);
  }

}
