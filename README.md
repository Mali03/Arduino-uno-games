# Arduino Uno Game Projects

## 1) 🐍 Snake with Joystick
This is a simple **Snake Game** controlled with a joystick and enhanced with a buzzer for a better gaming experience.
### How to Play?
- Control the snake using the joystick.
- Alternatively, you can use buttons (requires modifications in the code).
### Why a Buzzer?
- The buzzer beeps when the snake eats food and when it collides with itself, ending the game, providing auditory feedback.
- The snake's speed increases after eating food, making the game more difficult.
### Limitations
- Scores can be displayed using a **5161AS** (7-segment display), but the Arduino Uno runs out of available pins in this project.
### Requirements
- **Hardware**: 8x8 Matrix (1088AS), jumper wires, breadboard, resistors, passive buzzer, joystick.
- **Software**: Arduino IDE (2.3.4).

## 2) 🧠 Simon Says
This is a **Simon Says** memory game built using an Arduino Uno. The game tests your ability to remember and repeat sequences of LED flashes with buttons.
### How to Play?
- The game starts by flashing a random LED.
- You must press the correct button matching the LED and playing a corresponding sound.
- If you succeed, the sequence grows longer, and you must repeat the full pattern.
- The game continues until you make a mistake and it starts from the beginning.
### Possible developments
- Different sounds could be added for each button press, associating them with the corresponding lights.
### Requirements
- **Hardware**: 4 push buttons, 4 leds, jumper wires, breadboard, resistors, passive buzzer.
- **Software**: Arduino IDE (2.3.4).

## 3) 🚦 Green Light, Red Light
This is a **Green Light, Red Light** game built using an Arduino Uno. The game tests your reaction and timing skills with a button and LED system, enhanced with sound effects with buzzer.
### How to Play?
- When the green light is on (music is playing), hold the button to earn points.
- When the red light is on (no music), pressing the button results in losing the game.
- The game continues until you make a mistake.
### Possible developments
- A timer could be added to finish the game within a specific time limit.
- The song's speed can randomly increase, preventing players from memorizing a fixed rhythm.
## Requirements
- **Hardware**: 4-digit 7-segment display (5461BS-1), LED (red & green), push button, jumper wires, breadboard, resistors, passive buzzer.
- **Software**: Arduino IDE (2.3.4).

## 4) 🌌 Space Wars
This is a space-themed asteroid shooter game built with an Arduino Uno, controlled using a joystick for a more comfortable gameplay experience.
## How to play?
- Control the spacecraft with joystick
- The spacecraft is shooting continuously.
- If an asteroid is hit, it breaks into places with effect.
- If an asteroid reaches the boundary line near your position, the game is over.
## Sounds
- The buzzer beeps when asteroid is hit and when game is over.
## Requirements
- **Hardware**: OLED screen (128x64), joystick, mini breadboard, jumper wires, resistor, passive buzzer.
- **Software**: Arduino IDE (2.3.4).
