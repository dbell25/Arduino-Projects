#include <LiquidCrystal.h>
LiquidCrystal lcd(11, 9, 5, 6, 7, 8 );
unsigned long Time;
int buttonPin = 4;
const int Idle = 0;
const int Wait = 1;
const int Low = 2;
int buttonState = 0;
int count = 0;

void setup()
{
  lcd.begin(16, 2); //sets up lcd matrix with 16 columns and 2 rows
  pinMode(buttonPin, INPUT); //declares buttonPin as an input
  Time = millis(); //declares time being registered in milliseconds
  buttonState = Idle; //starting state
}
int ButtonNextState(int input) //sets ButtonNextState as a function
{
  switch (buttonState)
  {
    case Idle: //state when nothing is happening
      if (input == LOW)
      {
        Time = millis();
      }
      buttonState = Wait; 
      break;
    case Wait: //state after the button has been pressed
      if (input == HIGH)
      {
        buttonState = Idle; //if nothing is happening switch to idle state
      }
      else if (millis() - Time >= 5)
      {
        buttonState = Low; //if the button is being held down switch to low state
      }
      break;
    case Low: //state when the button is held down
      if (input == HIGH)
      {
        buttonState = Idle; //if the button has been released return to idle state
       return 1; //add 1 to counter
      }
      break;
  }
  return 0;
}

void loop() {
 if ( ButtonNextState(digitalRead(buttonPin))) //recognizes whether the button has been pressed
  {
    count++; //adds 1 to counter
    lcd.clear(); //clears the screen
    lcd.print(count); //displays the value after 1 has been added
  }
}

