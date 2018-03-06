unsigned long LcdTimer;
// Import LCD Library
#include <LiquidCrystal.h>
LiquidCrystal LcdDriver(11, 9, 5, 6, 7, 8 );
int count;

void setup()
{
  LcdDriver.begin(16, 2); //sets up 16 columns and 2 rows
  LcdTimer = millis();  //counts in milliseconds
  LcdDriver.clear(); //clears the screen
  count = 0; //zero’s the count
}
void loop()
{
  LcdDriver.setCursor(0, 0); //sets cursor to the 1st row, 1st column
  if (millis() - LcdTimer >= 500) { 
    ++count; 
    LcdDriver.clear();
    LcdDriver.print(count);
    LcdTimer += 500; //every 500 milliseconds the count increases by 1
  }
}
