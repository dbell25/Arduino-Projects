//included libraries
#include <math.h>
#include <TimerOne.h>
#include <MsTimer2.h>
float Time = 0.0;
float frequency = 0.5;
float Period = 1.0 / frequency;
int LEDpin = 13;
int PWMpin = 10;

void Interupt()
{
  digitalWrite(LEDpin, HIGH); //sets pin 13 high
  Time += 10e-3;  // Advance time interval
  if ( Time > Period ) // if time goes past Period = 1/frequency
  {
    Time -= Period;  // Wrap by Period, prevents Time from growing too large.
  }
  int x = 511 * sin( 6.2831853 * frequency * Time) + 512; //sine wave formula
  Timer1.setPwmDuty(PWMpin, x); //writes the above formula to pin 10
  digitalWrite(LEDpin, LOW); //sets pin 13 low
}


void setup()
{
  pinMode(10, OUTPUT); //sets pin 10 as an output
  pinMode(13, OUTPUT); //sets pin 13 as an output
  MsTimer2::set(10, Interupt); //runs ISR function every 10 milliseconds
  MsTimer2::start(); //starts MsTimer2
  Timer1.initialize(500); // Sets period to 500 microseconds
  Timer1.pwm(PWMpin, 512); //Sets a PWM signal on pin 10
}

void loop()
{
  //nothing happens
}

