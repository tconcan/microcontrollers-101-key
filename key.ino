#include <LiquidCrystal_I2C.h>

#define BUZZER_PIN 25   // GPIO for PWM buzzer
#define LCD_SCL_PIN 22  // GPIO for LCD SCL
#define LCD_SDA_PIN 21  // GPIO for LCD SDA
#define BUTTON_PIN 32   // GPIO for button

LiquidCrystal_I2C lcd(0x27,16,2);

void end_game () {
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("GAME OVER");
  lcd.setCursor(4,1);
  lcd.print("Score: ");
  lcd.print(score);
  while(1); // stall execution
}

void buzzer_beep () {
  analogWrite(BUZZER_PIN, 24);
  delay(75);
  analogWrite(BUZZER_PIN, 0);
}

void check_jump_button () {
  if (digitalRead(BUTTON_PIN) == LOW && !isDinoJumping) {
    isDinoJumping = true;
    jumpStartTime = millis();
    buzzer_beep();
  }
}

void update_dino_position () {
  if (isDinoJumping && millis() - jumpStartTime > jumpDuration) {
    isDinoJumping = false;
  }
  dinoRow = isDinoJumping ? 0 : 1;
}

void increment_score () {
  score++;
}

void update_obstacle_position () {
  // put your code to update the obstacle position here
  if (millis() - lastMove > moveInterval) {
    obstacleCol--;
    if (obstacleCol < 0) {
      obstacleCol = 15; // reset to right
      increment_score();
    }
    lastMove = millis();
  }
}

void check_dino_collision () {
  if (obstacleCol == 0 && dinoRow == 1) {
    buzzer_beep();
    end_game();
  }
}

void update_lcd () {
  lcd.clear();
  lcd.setCursor(0,dinoRow);
  lcd.print("D");           // dinosaur
  lcd.setCursor(obstacleCol,1);
  lcd.print("C");           // cactus
  lcd.setCursor(12,0);
  lcd.print(score);         // score
  delay(50);
}

// Game variables
int dinoRow = 1;                  // 0 = top row, 1 = bottom row
bool isDinoJumping = false;       // is the dino currently jumping?
unsigned long jumpStartTime = 0;  // time at which the dinosaur last jumped (ms)
const int jumpDuration = 750;     // duration of a jump (ms)

int obstacleCol = 15;       // // start at far right
int moveInterval = 300;     // // ms per move
unsigned long lastMove = 0; //

int score = 0;

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);
  pinMode(SOUND_PIN, OUTPUT); // PWM
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("ES@P T-rex Game");

  // Intro beeps
  buzzer_beep();
  delay(50);
  buzzer_beep(); 
  delay(50);
  buzzer_beep();
  delay(500);
}

void loop() {

  // update move interval based on score
  moveInterval = moveInterval / (1 + (score/10));

  // check jump button
  check_jump_button();

  // update dinosaur position
  update_dino_position();

  // update obstacle position
  update_obstacle_position();

  // check dino collision
  check_dino_collision();

  // draw to lcd
  update_lcd();
}
