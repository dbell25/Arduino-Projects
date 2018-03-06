unsigned long LcdTimer;
// Import LCD Library
#include <LiquidCrystal.h>
LiquidCrystal LcdDriver(11, 9, 5, 6, 7, 8 );
int seconds;
int minutes;
int hours;

void setup()
{
  LcdDriver.begin(16, 2); //sets up 16 columns and 2 rows
  LcdTimer = millis();  // counts in milliseconds
  LcdDriver.clear(); //clears the screen
  seconds = 0; //zero’s the count
}
void loop()
{
  LcdDriver.setCursor(0, 2); //sets cursor to 1st column, 2nd row
  if (millis() - LcdTimer >= 1000) {

    LcdDriver.clear();
    LcdDriver.print(seconds);
    LcdDriver.print(minutes);
    LcdDriver.print(hours);
    ++seconds;
    LcdTimer += 1000; //every 1000 milliseconds the seconds count increases by 1

    if (seconds == 60)    
    { 
      minutes++; //when seconds equal 60 the count resets and adds 1 to minutes
      seconds = 0;
    }

    if (minutes == 60)    
    {
      minutes = 0; //when minutes equal 60 the count resets and adds 1 to hours
      hours++;
    }
    if (hours == 24)    
      hours = 0; //when hours equal 24 the count resets
  }
}

