unsigned long Time;
void setup()
{
  Serial.begin(9600); //sets baud rate to 9600.
  Time = millis(); //measures time in milliseconds.
}

void loop() {
  if (millis() - Time >= 500)  //if 500 milliseconds have passed
  {
    int sensorValue = analogRead(0); //reads analog value of pin A0.
    float voltage = sensorValue * (5.0 / 1023.0); // Converts analog reading to voltage.
    Serial.println(voltage); //prints voltage value in serial monitor.
    Time += 500; //updates timer.
  }
}
