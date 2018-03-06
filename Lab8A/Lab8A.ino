#include <SPI.h>
unsigned long Time;
float Temperature;
int CS = 10; //declares chip select variable on pin 10
byte val1; //declares val 1 as a variable
byte val2; //declares val 2 as a variable
byte UpperByte; //declares UpperByte as a variable
byte LowerByte; //declares LowerByte as a variable

float ReadTemperature() //begin float
{
  digitalWrite (CS, LOW); //sets CS pin low
  val1 = SPI.transfer(0); //transmits 1st SPI value
  val2 = SPI.transfer(0); //transmits 2nd SPI value
  digitalWrite (CS, HIGH); //sets CS pin high
  SPI.endTransaction(); //ends SPI transfer
  int TempBits = ((val1 << 5 & 0x0fe0) + (val2 >> 3 & 0x001f));
  Temperature = 0.25 * (float) TempBits; // Converts bits to degrees Celsius
  Temperature = 1.8 * Temperature + 32.0;  // Converts Celsius to Fahrenheit
  return Temperature; //returns the temperature value in Fahrenheit
} //end float

void setup() {
  Serial.begin(9600); //sets serial connection at 9600 baud
  SPI.begin(); //initializes SPI
  SPI.setClockDivider(SPI_CLOCK_DIV2); //sets the SPI clock interval
  SPI.setDataMode(SPI_MODE0); //sets SPI clock data mode
  pinMode(CS, OUTPUT); // sets CS as an outputs:
  Time = millis(); //sets timer to milliseconds
}

void loop() {
  if (millis() - Time >= 1000) 
  {
    Serial.println(ReadTemperature()); 
//if 1 second has passed, print the value of ReadTemperature
    Time += 1000; //update timer
  }
}

