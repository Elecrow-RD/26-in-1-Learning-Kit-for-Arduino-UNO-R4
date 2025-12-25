#include <Wire.h>
#include "Adafruit_LiquidCrystal.h"

// ========== Pin Definitions ==========
#define POT_PIN A0

// ========== LCD Object ==========
Adafruit_LiquidCrystal lcd(0);

// ========== Variables ==========
int targetValue = 0;
int currentValue = 0;
int score = 0;

// ========== Setup ==========
void setup() {
  randomSeed(analogRead(A1));   // Random seed

  lcd.begin(16, 2);
  lcd.setBacklight(1);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Pot Guess Game");
  delay(1500);
  lcd.clear();
}

// ========== Main Loop ==========
void loop() {

  // Generate target value
  targetValue = random(0, 1024);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Target:");
  lcd.print(targetValue);

  lcd.setCursor(0, 1);
  lcd.print("Adjust in 3s");

  delay(3000);   // Give player time to adjust potentiometer

  // Read potentiometer value
  currentValue = analogRead(POT_PIN);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Now:");
  lcd.print(currentValue);

  lcd.setCursor(0, 1);
  lcd.print("Score:");
  lcd.print(score);

  // Compare values
  if (abs(currentValue - targetValue) <= 10) {
    score++;
    lcd.setCursor(10, 1);
    lcd.print("OK");
  } else {
    lcd.setCursor(10, 1);
    lcd.print("NO");
  }

  delay(2000);
}
