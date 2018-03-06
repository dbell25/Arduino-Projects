unsigned long LcdTimer;
// Import LCD Library
#include <LiquidCrystal.h>
LiquidCrystal LcdDriver(11, 9, 5, 6, 7, 8 );
volatile int encoderPosition = 0; 
//declares encoderPosition as a variable that can change at any moment

void MonitorA() //declares MonitorA as a function
{
  if (digitalRead(2) == digitalRead(3)) //if inputs of pins 2 and 3 equal each other
  {
    encoderPosition--; //decrements the LCD
  }
  else
  {
    encoderPosition++; //increments the LCD
  }
}
void MonitorB() //declares MonitorB as a function
{
  if (digitalRead(2) == digitalRead(3)) //if inputs of pins 2 and 3 equal each other
  {
    encoderPosition++; //increments the LCD
  }
  else
  {
    encoderPosition--; //decrements the LCD
  }
}

void setup() {
  LcdDriver.clear(); //clears the LCD
  LcdDriver.begin(16, 2); //sets up 16 columns and 2 rows
  LcdTimer = millis(); //tells the timer to count in milliseconds
  pinMode(2, INPUT); //declares pin 2 as an input
  pinMode(3, INPUT); //declares pin 3 as an input
  attachInterrupt(digitalPinToInterrupt(2), MonitorA, CHANGE); 
//attaches interrupt to pin to 2 and runs Monitor A function
  attachInterrupt(digitalPinToInterrupt(3), MonitorB, CHANGE); 
//attaches interrupt to pin to 3 and runs Monitor B function
}

void loop() {
  if (millis() - LcdTimer >= 100) //runs function every 100 milliseconds
  {
    LcdDriver.clear(); //clears LCD
    LcdDriver.print(encoderPosition); //outputs the number of current coder position
    LcdTimer += 100; //updates the LCD timer
  }
}
