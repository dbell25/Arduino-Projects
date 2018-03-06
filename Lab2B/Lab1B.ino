unsigned long LedTimer;
unsigned long LedTimer2;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  LedTimer = millis();
  LedTimer2 = millis();
}

void loop() {
  if (millis() - LedTimer >= 20) {
    if (digitalRead(13) == HIGH)
    {
      digitalWrite(13, LOW);
      digitalWrite(13, HIGH);
    }
    else
    {
      digitalWrite(13, HIGH);
    }
    LedTimer += 20;
  }
}

