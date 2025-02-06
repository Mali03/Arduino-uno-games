#include <OLED_I2C.h>
#define joystick A3 // 1023 - 0 middle is 509
#define buzzer 4

OLED display(A4, A5, 8); // 128x64 oled screen
extern uint8_t SmallFont[];

int joystickValue, score = 0, speed = 2;

int vehicle[21][2] = {
  { 60, 48 }, { 61, 48 }, { 62, 48 }, { 63, 48 }, { 64, 48 }, { 65, 48 }, { 66, 48 }, { 67, 48 }, { 68, 48 }, { 69, 48 }, { 70, 48 },  // base - vehicle[4] is the middle
  { 61, 47 }, { 62, 46 }, { 63, 45 }, { 64, 44 }, { 65, 43 }, { 66, 44 }, { 67, 45 }, { 68, 46 }, { 69, 47 }, { 70, 48 }
};

unsigned long lastFireTime = 0;
unsigned long lastEnemyTime = 0;

const int interval = 30;
const int maxBullets = 5;

const int enemyInterval = 150;
const int maxEnemies = 4;

const int enemyMoveInterval = 20;

bool isGameOver = false;

struct Bullet {
  int x;
  int y;
  bool active;
};

struct Enemy {
  int x;
  int y;
  bool active;
  unsigned long lastMoveTime;
};

Bullet bullets[maxBullets];
Enemy enemies[maxEnemies];

void setup() {
  display.begin();
  display.setFont(SmallFont);
  display.clrScr();

  display.printNumI(score, 62, 52);

  // draw the curlycue
  display.drawLine(0, 41, 5, 41);
  display.drawLine(5, 40, 10, 40);
  display.drawLine(10, 41, 20, 41);
  display.drawLine(20, 42, 25, 42);
  display.drawLine(25, 40, 35, 40);
  display.drawLine(35, 41, 40, 41);
  display.drawLine(40, 40, 45, 40);
  display.drawLine(45, 41, 55, 41);
  display.drawLine(55, 42, 60, 42);
  display.drawLine(60, 40, 70, 40);
  display.drawLine(70, 41, 75, 41);
  display.drawLine(75, 40, 80, 40);
  display.drawLine(80, 41, 90, 41);
  display.drawLine(90, 42, 95, 42);
  display.drawLine(95, 40, 105, 40);
  display.drawLine(105, 41, 110, 41);
  display.drawLine(110, 40, 127, 40);

  for (int i = 0; i < 21; i++) {
    display.setPixel(vehicle[i][0], vehicle[i][1]);
  }

  for (int i = 0; i < maxBullets; i++) {
    bullets[i].active = false;
  }

  for (int i = 0; i < maxEnemies; i++) {
    enemies[i].active = false;
    enemies[i].lastMoveTime = 0;
  }

  display.update();

  pinMode(buzzer, OUTPUT);

  randomSeed(analogRead(A0));
}

void loop() {
  if (isGameOver) {
    display.clrScr();
    display.fillScr();

    display.invertText(true);
    display.print("Game Over", CENTER, 30);
    display.update();
    
    return;
  }

  // clear all pixels
  for (int i = 0; i < 21; i++) {
    display.clrPixel(vehicle[i][0], vehicle[i][1]);
  }
  
  for (int i = 0; i < maxBullets; i++) {
    if (bullets[i].active) {
      display.clrPixel(bullets[i].x, bullets[i].y);
    }
  }

  // clear enemy pixels
  for (int i = 0; i < maxEnemies; i++) {
    if (enemies[i].active) {
      display.clrPixel(enemies[i].x + 1, enemies[i].y);
      display.clrPixel(enemies[i].x + 2, enemies[i].y);

      for (int j = 0; j < 4; j++) {
        display.clrPixel(enemies[i].x + j, enemies[i].y + 1);
        display.clrPixel(enemies[i].x + j, enemies[i].y + 2);
      }

      display.clrPixel(enemies[i].x + 1, enemies[i].y + 3);
      display.clrPixel(enemies[i].x + 2, enemies[i].y + 3);
    }
  }

  joystickValue = analogRead(joystick);
  
  if (joystickValue < 300) {  // to the right
    if (vehicle[10][0] < 127) {
      for (int i = 0; i < 21; i++) {
        vehicle[i][0] += speed;
      }
    }
  } 
  else if (joystickValue > 700) {  // to the left
    if (vehicle[0][0] > 0) {
      for (int i = 0; i < 21; i++) {
        vehicle[i][0] -= speed;
      }
    }
  }

  // fire bullet
  unsigned long currentTime = millis();

  if (currentTime - lastFireTime >= interval) {
    for (int i = 0; i < maxBullets; i++) {
      if (!bullets[i].active) {
        bullets[i].x = vehicle[4][0];
        bullets[i].y = vehicle[4][1] - 9;
        bullets[i].active = true;
        lastFireTime = currentTime;
        break;
      }
    }
  }

  // create a enemy
  if (currentTime - lastEnemyTime >= enemyInterval) {
    for (int i = 0; i < maxEnemies; i++) {
      if (!enemies[i].active) {
        enemies[i].x = random(30, 100);
        enemies[i].y = 0;
        enemies[i].active = true;
        enemies[i].lastMoveTime = currentTime;
        lastEnemyTime = currentTime;
        break;
      }
    }
  }

  // update bullet
  for (int i = 0; i < maxBullets; i++) {
    if (bullets[i].active) {
      bullets[i].y--;
      if (bullets[i].y < 0) {
        bullets[i].active = false;
      } else {
        for (int j = 0; j < maxEnemies; j++) {
          if (enemies[j].active) {
            bool isHit = false;
            
            if ((bullets[i].x == enemies[j].x + 1 && bullets[i].y == enemies[j].y) ||
                (bullets[i].x == enemies[j].x + 2 && bullets[i].y == enemies[j].y)) {
              isHit = true;
            }
            
            for (int k = 0; k < 4; k++) {
              if ((bullets[i].x == enemies[j].x + k && bullets[i].y == enemies[j].y + 1) ||
                  (bullets[i].x == enemies[j].x + k && bullets[i].y == enemies[j].y + 2)) {
                isHit = true;
                break;
              }
            }
            
            if ((bullets[i].x == enemies[j].x + 1 && bullets[i].y == enemies[j].y + 3) ||
                (bullets[i].x == enemies[j].x + 2 && bullets[i].y == enemies[j].y + 3)) {
              isHit = true;
            }
            
            if (isHit) { // if enemy is hit
              for (int m = 3; m<6; m++) {
                display.setPixel(enemies[j].x+m,enemies[j].y);
                display.setPixel(enemies[j].x-m,enemies[j].y);
                display.setPixel(enemies[j].x,enemies[j].y+m);
                display.setPixel(enemies[j].x,enemies[j].y-m);
              }

              display.update();
              
              for (int m = 3; m<6; m++) {
                display.clrPixel(enemies[j].x+m,enemies[j].y);
                display.clrPixel(enemies[j].x-m,enemies[j].y);
                display.clrPixel(enemies[j].x,enemies[j].y+m);
                display.clrPixel(enemies[j].x,enemies[j].y-m);
              }

              enemies[j].active = false;
              bullets[i].active = false; 
              score += 1;
              playHitSound();
              display.printNumI(score, 62, 52);
              break;
            }
          }
        }
      }
    }
  }

  for (int i = 0; i < maxEnemies; i++) {
    if (enemies[i].active) {
      unsigned long currentTime = millis();
      if (currentTime - enemies[i].lastMoveTime >= enemyMoveInterval) {
        enemies[i].y++;
        if (enemies[i].y > 37) {
          playGameOverSound();
          isGameOver = true;
        }
        enemies[i].lastMoveTime = currentTime;
      }
    }
  }

  // update pixels of vehicle
  for (int i = 0; i < 21; i++) {
    display.setPixel(vehicle[i][0], vehicle[i][1]);
  }

  // update pixels of bullet
  for (int i = 0; i < maxBullets; i++) {
    if (bullets[i].active) {
      display.setPixel(bullets[i].x, bullets[i].y);
    }
  }

  // update pixels of enemy
  for (int i = 0; i < maxEnemies; i++) {
    if (enemies[i].active) {
      display.setPixel(enemies[i].x + 1, enemies[i].y);
      display.setPixel(enemies[i].x + 2, enemies[i].y);

      for (int j = 0; j < 4; j++) {
        display.setPixel(enemies[i].x + j, enemies[i].y + 1);
        display.setPixel(enemies[i].x + j, enemies[i].y + 2);
      }

      display.setPixel(enemies[i].x + 1, enemies[i].y + 3);
      display.setPixel(enemies[i].x + 2, enemies[i].y + 3);
    }
  }

  display.update();
}

void playHitSound() {
  tone(buzzer, 1000, 30);
  delay(30);
  tone(buzzer, 700, 30);
  delay(30);
  tone(buzzer, 500, 30);
  delay(30);
  noTone(buzzer);
}

void playGameOverSound() {
  for (int i = 1000; i > 100; i -= 50) {
    tone(buzzer, i, 50);
    delay(20);
  }
  noTone(buzzer);
}