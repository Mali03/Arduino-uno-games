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

## 2) 🧠 Simon Says
This is a **Simon Says** memory game built using an Arduino Uno. The game tests your ability to remember and repeat sequences of LED flashes with buttons.
### How to Play?
- The game starts by flashing a random LED.
- You must press the correct button matching the LED and playing a corresponding sound.
- If you succeed, the sequence grows longer, and you must repeat the full pattern.
- The game continues until you make a mistake and it starts from the beginning.
### Possible developments
- Different sounds could be added for each button press, associating them with the corresponding lights.
