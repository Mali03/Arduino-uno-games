int pinA = 11, pinB = 7, pinC = 4, pinD = 3;
int pinE = 13, pinF = 10, pinG = 5;
int D1 = 12, D2 = 9, D3 = 8, D4 = 6;

int buttonPin = A0, buzzerPin = A3;
int redLed = A2, greenLed = A1;

unsigned long previousMillis = 0;
const long interval = 500;

bool isRedLight = false;
int score = 0;
bool gameOver = false;
bool isSongPlaying = false;
int currentNote = 0;
bool gameWon = false;

unsigned long songStartTime = 0;
unsigned long redLightStartTime = 0;
unsigned long redLightDuration = 0;

int digitValues[4] = { 0, 0, 0, 0 };

void setup() {
  pinMode(buttonPin, INPUT);
  
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  
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

  // I use tone() function so don't need to write pinMode(buzzerPin, OUTPUT)

  digitalWrite(greenLed, HIGH);
  randomSeed(analogRead(0));
}

void loop() {
  if (gameWon || gameOver) {
    updateDisplay();
    return;
  }

  checkRedLightTimeout();
  updateSongAndLights();
  handleButtonPress();
  updateDisplay();
}

void checkRedLightTimeout() {
  if (isRedLight && !isSongPlaying) {
    if (millis() - redLightStartTime >= redLightDuration) {
      isRedLight = false;
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
      isSongPlaying = false;
    }
  }
}

void updateSongAndLights() {
  if (!isSongPlaying && !isRedLight) {
    startSong();
  }
  
  if (isSongPlaying) {
    playSongStep();
  }
}

void handleButtonPress() {
  int buttonState = digitalRead(buttonPin);
  
  if (isRedLight && buttonState == HIGH) {
    gameOver = true;
    resetGame();
    return;
  }
  
  if (!isRedLight && buttonState == HIGH && !gameWon) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      incrementScore();
    }
  }
}

int melody[] = { 392, 440, 494, 392, 523, 494, 440, 392, 440 };
int noteDurations[] = { 400, 300, 500, 400, 600, 500, 300, 400, 700 };

void startSong() {
  isSongPlaying = true;
  currentNote = 0;
  songStartTime = millis();
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
}

void playSongStep() {
  if (currentNote >= 9) {
    isSongPlaying = false;
    noTone(buzzerPin);
    isRedLight = true;
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    redLightStartTime = millis();
    redLightDuration = random(2000, 5000);
    return;
  }

  unsigned long currentTime = millis();
  unsigned long noteDuration = noteDurations[currentNote];
  
  if (currentTime - songStartTime >= noteDuration * 1.2) {
    currentNote++;
    songStartTime = currentTime;
    if (currentNote < 9) {
      tone(buzzerPin, melody[currentNote], noteDurations[currentNote]);
    }
  }
}

void incrementScore() {
  score++;
  digitValues[3] = score % 10;
  digitValues[2] = (score / 10) % 10;
  digitValues[1] = (score / 100) % 10;
  digitValues[0] = (score / 1000) % 10;
  
  if (score >= 100) {
    gameWon = true;
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    noTone(buzzerPin);
    playVictoryMelody();
  }
}

void playVictoryMelody() {
  int victoryMelody[] = {
    523, 523, 523, 523, 784,
    698, 698, 698,
    880, 880, 880,
    784
  };
  
  int victoryDurations[] = {
    200, 200, 200, 200, 400,
    200, 200, 400,
    200, 200, 400,
    600
  };
  
  for (int i = 0; i < 12; i++) {
    tone(buzzerPin, victoryMelody[i], victoryDurations[i]);
    delay(victoryDurations[i] * 1.3);
    noTone(buzzerPin);
  }
}

void resetGame() {
  score = 0;
  for (int i = 0; i < 4; i++) {
    digitValues[i] = -1;
  }
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  isRedLight = false;
  isSongPlaying = false;
  currentNote = 0;
  gameWon = false;
  playGameOverSound();
}

void playGameOverSound() {
  for (int i = 1000; i > 100; i -= 50) {
    tone(buzzerPin, i, 50);
    delay(20);
  }
  noTone(buzzerPin);
}

void updateDisplay() {
  for (int i = 0; i < 4; i++) {
    showDigit(i, digitValues[i]);
    delay(1);
  }
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
  if (num == -1) {
    displayDash();
    return;
  }
  
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

void displayDash() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
}

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