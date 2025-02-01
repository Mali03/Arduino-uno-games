#define joystickX A4
#define joystickY A5
#define buzzerPin A3

int X[] = { 1, 2, 3, 4, 5, 6, 7, 8 };         // Rows
int Y[] = { 9, 10, 11, 12, 13, A0, A1, A2 };  // Columns

// snake's settings
int snakeX[64] = {3};
int snakeY[64] = {3};
int snakeLength = 1;
int direction = 0;

int foodX;
int foodY;

bool gameOver = false;
unsigned long lastMoveTime;
int gameSpeed = 300;

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(X[i], OUTPUT);
    pinMode(Y[i], OUTPUT);
  }
  
  pinMode(joystickX, INPUT);
  pinMode(joystickY, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  randomSeed(analogRead(0));

  placeFood();
}

void loop() {
  if (!gameOver) {
    readJoystick();
    if (millis() - lastMoveTime >= gameSpeed) {
      moveSnake();
      checkGameOver();
      checkFood();
      lastMoveTime = millis();
    }
  }

  // activate all the leds
  for (int i = 0; i < 8; i++) {
    digitalWrite(X[i], HIGH);
    digitalWrite(Y[i], LOW);
  }
  
  // snake's move
  for (int i = 0; i < snakeLength; i++) {
    digitalWrite(X[snakeX[i]], LOW);
    digitalWrite(Y[snakeY[i]], HIGH);
    delayMicroseconds(100);
    digitalWrite(X[snakeX[i]], HIGH);
    digitalWrite(Y[snakeY[i]], LOW);
  }
  
  // food
  digitalWrite(X[foodX], LOW);
  digitalWrite(Y[foodY], HIGH);
  delayMicroseconds(100);
  digitalWrite(X[foodX], HIGH);
  digitalWrite(Y[foodY], LOW);
}

void readJoystick() {
  int x = analogRead(joystickX);
  int y = analogRead(joystickY);

  if (x < 300 && direction != 2) direction = 0; // To the right
  if (x > 700 && direction != 0) direction = 2; // To the left
  if (y < 300 && direction != 1) direction = 3; // To the bottom
  if (y > 700 && direction != 3) direction = 1; // To the top
}

void moveSnake() {
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i-1];
    snakeY[i] = snakeY[i-1];
  }
  
  switch (direction) {
    case 0: snakeX[0]--; break; // Right
    case 1: snakeY[0]--; break; // Top
    case 2: snakeX[0]++; break; // Left
    case 3: snakeY[0]++; break; // Bottom
  }
  
  if (snakeX[0] >= 8) snakeX[0] = 0;
  if (snakeX[0] < 0) snakeX[0] = 7;
  if (snakeY[0] >= 8) snakeY[0] = 0;
  if (snakeY[0] < 0) snakeY[0] = 7;
}

void checkGameOver() {
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver = true;

      tone(buzzerPin,600);
      delay(100);
      tone(buzzerPin,500);
      delay(100);
      tone(buzzerPin,600);
      delay(100);
      tone(buzzerPin,500);
      delay(100);
      noTone(buzzerPin);
      delay(100);

      return;
    }
  }
}

void checkFood() {
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLength++;

    tone(buzzerPin,1000);
    delay(100);
    noTone(buzzerPin);
    delay(100);

    placeFood();

    if (gameSpeed > 100) {
      gameSpeed -= 10; // Speed increases 10 
    }
  }
}

void placeFood() {
  boolean validPosition;
  do {
    validPosition = true;
    foodX = random(8);
    foodY = random(8);
    
    for (int i = 0; i < snakeLength; i++) {
      if (foodX == snakeX[i] && foodY == snakeY[i]) {
        validPosition = false;
        break;
      }
    }
  } while (!validPosition); // if false choose another location
}