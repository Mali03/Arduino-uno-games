int pinA = 11, pinB = 7, pinC = 4, pinD = 3;
int pinE = 13, pinF = 10, pinG = 5;
int D1 = 12, D2 = 9, D3 = 8, D4 = 6;

int buttonPin = A0, buzzerPin = A3;
int redLed = A2, greenLed = A1;

// cathod display: high -> light on | anot display: low -> light on

int melody[] = { 392, 440, 494, 392, 523, 494, 440, 392, 440 };
int noteDurations[] = { 400, 300, 500, 400, 600, 500, 300, 400, 700 };

unsigned long previousMillis = 0;
const long interval = 500;

int digitValues[4] = { 0, 0, 0, 0 };
int total;

int buttonInfo;

void setup() {
  pinMode(buttonPin, INPUT);

  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
}

void loop() {
  buttonInfo = digitalRead(buttonPin);

  if (total == 10 || total == 23 || total == 30 || total == 39 || total == 45 || total == 52 || total == 59 || total == 65 || total == 70 || total == 80 || total == 92 || total == 98) {
    playSong();
  } else {
    if (buttonInfo == HIGH) {
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= interval) {

        previousMillis = currentMillis;

        digitValues[3]++;
        if (digitValues[3] > 9) {
          digitValues[3] = 0;
          digitValues[2]++;
          if (digitValues[2] > 9) {
            digitValues[2] = 0;
            digitValues[1]++;
            if (digitValues[1] > 9) {
              digitValues[1] = 0;
              digitValues[0]++;
              if (digitValues[0] > 9) {
                digitValues[0] = 0;
              }
            }
          }
        }
      }
    }

    for (int i = 0; i < 4; i++) {
      showDigit(i, digitValues[i]);
      delay(1);
    }

    total = digitValues[1] * 100 + digitValues[2] * 10 + digitValues[3];
  }
}

void playSong() {
  digitalWrite(redLed, HIGH);

  for (int i = 0; i < 9; i++) {
    tone(buzzerPin, melody[i], noteDurations[i]);
    delay(noteDurations[i] * 1.2);  // Nota çalma süresi
    noTone(buzzerPin);
  }

  digitalWrite(redLed, LOW);
}

void playWinMelody() {
  int winMelody[] = { 262, 330, 392, 503, 523 };
  int durations[] = { 150, 150, 150, 400, 700 };

  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, winMelody[i], durations[i]);
    delay(durations[i] * 1.3);
    noTone(buzzerPin);
  }

  tone(buzzerPin, winMelody[3], durations[3]);
  delay(durations[3] * 1.3);
  noTone(buzzerPin);

  delay(150);

  tone(buzzerPin, winMelody[4], durations[4]);
  delay(durations[4] * 1.3);
  noTone(buzzerPin);
}


void showDigit(int digit, int value) {
  turnOffAllDigits();

  switch (digit) {
    case 0: digitalWrite(D1, HIGH); break;
    case 1: digitalWrite(D2, HIGH); break;
    case 2: digitalWrite(D3, HIGH); break;
    case 3: digitalWrite(D4, HIGH); break;
  }

  displayNumber(value);
}

void turnOffAllDigits() {
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}

void displayNumber(int num) {
  switch (num) {
    case 0: zero(); break;
    case 1: one(); break;
    case 2: two(); break;
    case 3: three(); break;
    case 4: four(); break;
    case 5: five(); break;
    case 6: six(); break;
    case 7: seven(); break;
    case 8: eight(); break;
    case 9: nine(); break;
    default: turnOffAllSegments(); break;
  }
}

//functions representing numbers 0-9
void zero() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
}

void one() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}

void two() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
}

void three() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
}

void four() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}

void five() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}

void six() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}

void seven() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}

void eight() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}

void nine() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}

void turnOffAllSegments() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}

void all4Digits() {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
}