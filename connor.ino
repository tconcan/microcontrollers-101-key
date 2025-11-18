#include <LiquidCrystal_I2C.h>

#define SOUND_PIN 25  // GPIO25 PWM for sound
#define SCL_PIN 22
#define SDA_PIN 21
#define BUTTON_PIN 32 // GPIO for jump button

LiquidCrystal_I2C lcd(0x27,16,2);

void beep() {
  analogWrite(SOUND_PIN, 24);
  delay(75);
  analogWrite(SOUND_PIN, 0);
}

// Game variables
int dinoRow = 1;         // 0 = top, 1 = bottom
bool isJumping = false;
unsigned long jumpStart = 0;
const int jumpDuration = 750; // ms

int obstacleCol = 15;    // start at far right
int moveInterval = 300; // ms per move
unsigned long lastMove = 0;

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
  beep();
  delay(50);
  beep(); 
  delay(50);
  beep();
  delay(500);
}

void loop() {
  // Update move interval based on score
  moveInterval = moveInterval / (1 + (score/10));

  // Check jump button
  if (digitalRead(BUTTON_PIN) == LOW && !isJumping) {
    isJumping = true;
    jumpStart = millis();
    beep();
  }

  // Update dinosaur position
  if (isJumping && millis() - jumpStart > jumpDuration) {
    isJumping = false;
  }
  dinoRow = isJumping ? 0 : 1;

  // Move obstacle
  if (millis() - lastMove > moveInterval) {
    obstacleCol--;
    if (obstacleCol < 0) {
      obstacleCol = 15; // reset to right
      score++;
    }
    lastMove = millis();
  }

  // Check collision
  if (obstacleCol == 0 && dinoRow == 1) {
    beep(); // collision beep
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("GAME OVER");
    lcd.setCursor(4,1);
    lcd.print("Score: ");
    lcd.print(score);
    while(1); // stop game
  }

  // Draw game
  lcd.clear();
  lcd.setCursor(0,dinoRow);
  lcd.print("D");           // dinosaur
  lcd.setCursor(obstacleCol,1);
  lcd.print("C");           // cactus
  lcd.setCursor(12,0);
  lcd.print(score);         // score
  delay(50);
}
