/*
  Quick demo of major drawing operations on a single DMD
 */

//#include <SPI.h>
#include "DMD2.h"
#include "SystemFont5x7.h"

//SoftDMD dmd(1,1);  // DMD controls the entire display
// Hardware SPI - by default, nOE=A0, A=D4, B=D3, SCK=D2, MOSI=A5, SCK=A3
SPIDMD dmd(1,1);  // DMD controls the entire display

// the setup routine runs once when you press reset:
void setup() {
  dmd.setBrightness(255);
  dmd.selectFont(SystemFont5x7);
  dmd.begin();

  // Circle with a line at a tangent to it
  dmd.drawCircle(24,8,5);
  dmd.drawLine(14,9,28,15);

  // Outline box containing a filled box
  dmd.drawBox(6,10,11,15);
  dmd.drawFilledBox(8,12,9,13);
}

int n = 123;

// the loop routine runs over and over again forever:
void loop() {
  dmd.drawString(0,0,String(n));
  n = n + 1;
  delay(1000);

  if(n % 2 == 0) {
    dmd.drawFilledBox(0,11,4,15, false); // Passing false here clears the box
    dmd.drawBox(0,11,4,15);
  } else {
    dmd.drawFilledBox(0,11,4,15);
  }
}
