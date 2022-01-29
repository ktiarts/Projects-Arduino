#include <nokiaLCD.h>
#include <font_6x8.h> // extra font

#define RST 2
#define CE 3
#define DC 4
#define DIN 5
#define CLK 6
// pins are in this order: reset, dc (d/c), sdin (mosi - data in), sclk (sck - clock), sce (chip enable), led (backlight)
nokiaLCD display(RST,DC,DIN,CLK,CE,7); //RST, CE, DC, DIN, CLK 

void setup(void)
{
  display.init();
  
  display.backlight(true);
  display.gotoXY(0,2); // goto 3rd line, first column
  // write first line
  display.print("Hello World!");

  // shut off the backlight after awhile
  delay(9000);
  display.backlight(false);
}

void loop(void)
{
}

