// Timer
char letter = 65;
int number = 0;
unsigned long LedTimer;

void setup() {
  Serial.begin(9600);
  LedTimer = millis();
}

void loop() {
  if (millis() - LedTimer >= 500) {
    Serial.print (letter);
    Serial.print (number);
    if (letter < 90) {
      letter++;
    }
      else
     {
      letter = 65;
    }
    if (number < 9) {
      number++;
    }
    else
    {
    number = 0;
    }
    LedTimer += 500;
  }
  if (Serial.available())
    if (Serial.read() == 'R') {
      letter = 65;
      number = 0;
    }
  }

