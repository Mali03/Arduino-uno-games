#define redLed 3
#define yellowLed 4
#define blueLed 5
#define greenLed 6

#define redButton 8
#define yellowButton 9
#define blueButton 10
#define greenButton 11

#define buzzerPin 13

int tour = 1, tourNumber = 5, buttonPressed;

bool gameFinished = false;

int leds[4] = { redLed, yellowLed, blueLed, greenLed };
int buttons[4] = { redButton, yellowButton, blueButton, greenButton };
int game[20];

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  pinMode(redButton, INPUT);
  pinMode(yellowButton, INPUT);
  pinMode(blueButton, INPUT);
  pinMode(greenButton, INPUT);

  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  randomSeed(analogRead(0));

  for (int i = 0; i < 20; i++) {
    game[i] = random(0, 4);
  }
}

void loop() {
  if (gameFinished) return;

  if (tour - 1 == tourNumber) {
    for (int i = 2000; i < 5000; i += 1000) {
      tone(buzzerPin, i);
      delay(200);
      noTone(buzzerPin);
      delay(200);
    }

    gameFinished = true;

    return;
  }

  for (int i = 0; i < tour; i++) {
    digitalWrite(leds[game[i]], HIGH);
    delay(500);
    digitalWrite(leds[game[i]], LOW);
    delay(500);
  }

  for (int i = 0; i < tour; i++) {
    buttonPressed = -1;

    while (buttonPressed == -1) {
      for (int j = 0; j < 4; j++) {
        if (digitalRead(buttons[j]) == HIGH) {
          buttonPressed = j;
          break;
        }
      }
    }

    if (buttonPressed != game[i]) {
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
      delay(1000);
      tour = 1;
      return;
    }

    tone(buzzerPin, 500);
    delay(300);
    noTone(buzzerPin);
  }

  delay(1000);

  tour++;
}
