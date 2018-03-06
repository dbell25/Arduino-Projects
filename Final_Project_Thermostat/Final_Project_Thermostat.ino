unsigned long Time;
unsigned long Time1;
unsigned long Time2;
#include <EEPROM.h> //includes EEPROM library
#include <LiquidCrystal.h>// includes LCD library
LiquidCrystal lcd(11, 9, 5, 6, 7, 8 ); //set lcd pins
int tempPin = A1; //sets tempPin to analog pin 1
int fan = 12; //sets fan to pin 3
float temp;
volatile float setTemp;
int button = 4;
int hours = 17;
int minutes = 59;
int seconds = 0;

void setup()
{
  Serial.begin (9600); // sets serial baud rate
  setTemp = EEPROM.read(1); //reads saved temp value
  lcd.begin(16, 2); // sets up display (16 columns, 2 rows)
  Time = millis(); //counts Time1 in milliseconds
  Time1 = millis(); //counts Time1 in milliseconds
   Time2 = millis(); //tells the timer to count in milliseconds
  pinMode(button, INPUT); //sets button pin as an input
  pinMode(fan, OUTPUT); //sets fan as an output
  pinMode(2, INPUT); //declares pin 2 as an input
  pinMode(3, INPUT); //declares pin 3 as an input
  attachInterrupt(digitalPinToInterrupt(2), MonitorA, CHANGE); //attaches interrupt to pin to 2 and runs Monitor A function
  attachInterrupt(digitalPinToInterrupt(3), MonitorB, CHANGE); //attaches interrupt to pin to 3 and runs Monitor B function
}

void MonitorA() //declares MonitorA as a function
{
  if (digitalRead(2) == digitalRead(3)) //if inputs of pins 2 and 3 equal each other
  {
    setTemp++; //decrements the LCD
  }
  else
  {
    setTemp--; //increments the LCD
  }
}
void MonitorB() //declares MonitorB as a function
{
  if (digitalRead(2) == digitalRead(3)) //if inputs of pins 2 and 3 equal each other
  {
    setTemp--; //increments the LCD
  }
  else
  {
    setTemp++; //decrements the LCD
  }
}

void approachTemp()
{
  if (millis() - Time2 >= 100) //runs function every 100 milliseconds
  {
    lcd.clear(); //clears LCD
    lcd.print(setTemp); //outputs the number of current coder position
    Time2 += 100; //updates the LCD timer
  }
}

void Thermo()
{
  float temp = (5.0 * analogRead(tempPin) * 100.0) / 1024.0; //converts reading from millivolts to fahrenheit
  lcd.setCursor (0, 0); // set the cursor to 1st row, 1st column
  if (millis() - Time1 >= 1000)
  {
    lcd.print (temp); //Print the current temp in f
    lcd.print ('F'); //Prints the letter F
    lcd.print (' '); //Prints a space
    lcd.print (setTemp); //Prints the preset temperature
    lcd.print ('F'); //Prints the letter F
    if (digitalRead(button) == LOW) //if button has been pressed
    {
      approachTemp();
    }
    EEPROM.write (1, setTemp); //writes preset temperature to EEPROM
    if ((hours >= 18) or (hours < 6))
    {
      setTemp = 78; //night time preset temperature
    }
    Time1 += 1000;
  }
  if (temp > setTemp) //if reading is greater than preset temperature
  {
    digitalWrite (fan, HIGH); //turns the fan on
  }
  else
  {
    digitalWrite (fan, LOW); //turns the fan off
  }
  lcd.setCursor (0, 1); // set the cursor to 1st column, second row
  runClock(); //runs the runClock function
}


void runClock ()
{
  if (millis() - Time >= 1000)
  {
    if (hours == 24)
    {
      hours = 0; //sets hours to 0
    }
    if (minutes == 60)
    {
      minutes = 0; //sets minutes to 0
      hours++; //increments hours by 1
    }
    if (seconds == 60)
    {
      minutes++; //increments minutes by 1
      seconds = 0; //sets minutes to 0
    }
    if (hours < 10)
    {
      lcd.print("0"); //prints a leading zero
    }
    lcd.print(hours); //prints the value of hours
    lcd.print(":"); //prints a colon
    if (minutes < 10)
    {
      lcd.print("0"); //prints a leading zero
    }
    lcd.print(minutes); //prints the value of minutes
    lcd.print(":"); //prints a colon
    if (seconds < 10)
    {
      lcd.print("0"); //prints a leading zero
    }
    lcd.print(seconds); //prints the value of seconds
    ++seconds; //increments seconds by 1
    Time += 1000;
  }
}

void loop()
{
  Thermo(); //runs Thermo function
}

