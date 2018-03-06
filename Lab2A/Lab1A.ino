unsigned long LedTimer;
unsigned long LedTimer2;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  LedTimer = millis();
  LedTimer2 = millis();
}

void loop() {
  if (millis() - LedTimer >= 10) {
    if (digitalRead(13) == HIGH)
    {
      digitalWrite(13, LOW);
    }
    else
    {
      digitalWrite(13, HIGH);
    }
    LedTimer += 10;
  }

  if (millis() - LedTimer2 >= 20) {
    if (digitalRead(10) == HIGH)
    {
      digitalWrite(10, LOW);
    }
    else
    {
      digitalWrite(10, HIGH);
    }
    LedTimer2 += 20;
  }
}
