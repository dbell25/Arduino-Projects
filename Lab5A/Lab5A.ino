unsigned long Time;
int buttonPin = 4;
const int Idle = 0;
const int Wait = 1;
const int Low = 2;
int buttonState = 0;

void setup()
{
  Serial.begin(9600); //sets baud rate
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
        return 1;
      }
      break;
    case Low: //state when the button is held down
      if (input == HIGH)
      {
        buttonState = Idle; //if the button isn’t being pressed return to idle state
      }
      break;
  }
  return 0;
}

void loop() {
  if ( ButtonNextState(digitalRead(buttonPin)))  //recognizes whether the button has been pressed
  {
    Serial.print("The Button has been pressed "); //displays the message in a serial monitor
  }
}

