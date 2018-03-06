// Timer
unsigned long LedTimer;

void setup() {
  Serial.begin(9600);
  LedTimer = millis();
}

void loop() {
  if (millis() - LedTimer >= 500)
    Serial.print('Z');
  LedTimer += 500;
}
