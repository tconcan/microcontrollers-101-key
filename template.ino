#include <LiquidCrystal_I2C.h>

#define BUZZER_PIN 25   // GPIO for PWM buzzer
#define LCD_SCL_PIN 22  // GPIO for LCD SCL
#define LCD_SDA_PIN 21  // GPIO for LCD SDA
#define BUTTON_PIN 32   // GPIO for button

// game variables
LiquidCrystal_I2C lcd(0x27, 16, 2);  // lcd
int dinoRow = 1;                     // 0 = top row, 1 = bottom row
bool isDinoJumping = false;          // is the dino currently jumping?
const int jumpDuration = 750;        // duration of a jump (ms)
unsigned long lastJumpTime = 0;      // time at which the dino last jumped (ms)
int obstacleCol = 15;                // start at 15th coloumn
int moveInterval = 300;              // ms per move, controls the speed of the game
unsigned long lastMoveTime = 0;      // time at which the obstacle last moved (ms)

void end_game () {
  // put your code to indefinitely stall the game here

}

void buzzer_beep () {
  // put your buzzer beep code here

}

void check_jump_button () {
  // put your code to check the button state here

}

void update_dino_position () {
  // put your code to update the dino position here

}

void update_obstacle_position () {
  // put your code to update the obstacle position here

}

void check_dino_collision () {
  // put your code to check the dino collision here

}

void update_lcd () {
  // put your lcd display control code here

}

void setup () {
  // put your setup code here, to run once:

}

void loop () {
  // put your main code here, to run repeatedly:

}
