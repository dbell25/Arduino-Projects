#include "DecodeFloat.h" //file for math functions
#include <LiquidCrystal.h> //file for LCD functions
LiquidCrystal LcdDriver(11, 9, 5, 6, 7, 8 ); //assigns LCD display pins

int CalcState = 1;
const int First = 1;
const int Second = 2;
const int Operation = 3;
float FirstNumber = 0;
float SecondNumber = 0;
const int numDigits = 4;

void setup() {
  Serial.begin(9600); //sets up serial port at 9600 baud
  LcdDriver.clear(); //clears the display
  LcdDriver.begin(16, 2); // sets the screen matrix at 16 columns and 2 rows
  DecodeReset(); //resets decoder
}

void LcdPrintFloat(float input, int digits) //start LcdPrintFloat function
{
  int negativeFlag = 0; //declares negativeFlag as a variable
  int exponent = 0; //declares exponent as a variable
  if (input < 0) //if input is negative, make it positive and mark the variable as negative 
  {
    input = input * -1;
    negativeFlag = 1;
  }
  while (input > 10) //converts the input into scientific notation and increases the exponent
  {
    exponent++;
    input = input / 10;
  }
  while (input < 1) //converts the input into scientific notation and decreases the exponent
  {
    exponent--;
    input = input * 10;
  }
  if (negativeFlag == 1) //if negativeFlag is checked, display a negative sign
  {
    LcdDriver.print("-");
  }

  LcdDriver.print(input, digits); //displays the input and designated number of digits

  if (exponent != 0) //if exponent is not equal to 0, print “e” and then the exponent
  {
    LcdDriver.print("e");
    LcdDriver.print(exponent);
  }
} //end of LcdPrintFloat function

void loop () {
  if ( Serial.available() ) //if input is available in the serial port, set input as Ch
  {
    char Ch = Serial.read();
    switch (CalcState)
    {
      case First:
        if ( DecodeFloat( Ch ) ) //runs input through DecodeFloat function
        {
          LcdDriver.clear(); //clears the screen
          FirstNumber = ResultingFloat; //output of DecodeFloat becomes 1st number
          LcdPrintFloat(FirstNumber, numDigits); //runs FirstNumber through LcdPrintFloat and displays output on the LCD display
          DecodeReset(); //resets decoder
          CalcState = Second; //sets switch state to Second
        }
        break;
      case Second:
        if ( DecodeFloat( Ch ) ) //runs input through DecodeFloat function
        {
          SecondNumber = ResultingFloat; //output of DecodeFloat becomes 2nd number
          LcdDriver.setCursor(0, 1); //sets cursor to 2st row, 1st column
          LcdPrintFloat(SecondNumber, numDigits); //runs 2nd number through LcdPrintFloat and displays output on the Lcd display
          DecodeReset();
          CalcState = Operation; //sets switch state to Operation
        }
        break;
      case Operation:
        switch ( Ch ) {
          case '+':
            LcdDriver.clear(); //clears the display
            LcdPrintFloat(FirstNumber + SecondNumber, numDigits); //adds 1st and 2nd number, runs the resulting value through LcdPrintFloat, displays output and number of digits on the Lcd display
            break;
          case '-':
            LcdDriver.clear(); //clears the display
            LcdPrintFloat(FirstNumber - SecondNumber, numDigits); //subtracts 1st and 2nd number, runs the resulting value through LcdPrintFloat, displays output and number of digits on the Lcd display
            break;
          case '*':
            LcdDriver.clear(); //clears the display
            LcdPrintFloat(FirstNumber * SecondNumber, numDigits); //multiplies 1st and 2nd number, runs the resulting value through LcdPrintFloat, displays output and number of digits on the Lcd display
            break;
          case '/':
            LcdDriver.clear(); //clears the display
            LcdPrintFloat(FirstNumber / SecondNumber, numDigits); //divides 1st and 2nd number, runs the resulting value through LcdPrintFloat, displays output and number of digits on the Lcd display
            break;
        }
        CalcState = First; //sets the switch state back to the beginning
        break;
    }
  }
}

