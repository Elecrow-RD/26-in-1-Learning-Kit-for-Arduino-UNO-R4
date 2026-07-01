#include "Adafruit_LiquidCrystal.h"   // Library for I2C LCD1602

#define BUTTON_PIN 3                  // Digital pin connected to the button

// Create an LCD object (I2C address is handled internally by the library)
Adafruit_LiquidCrystal lcd(0);

// ---------------- Variable Definitions ----------------

// Time when the button is pressed down
unsigned long pressStartTime = 0;

// Time when the button is released
unsigned long lastReleaseTime = 0;

// Flag to indicate whether the button is currently pressed
bool buttonPressed = false;

// String to store the Morse code sequence ('.' and '-')
String morseCode = "";

// ---------------- Setup Function ----------------
void setup() {
  Serial.begin(115200);               // Start serial communication for debugging

  // Set button pin as input with internal pull-up resistor
  // Default state: HIGH, Pressed: LOW
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initialize the LCD (16 columns, 2 rows)
  // Retry until initialization is successful
  while (!lcd.begin(16, 2)) {
    Serial.println("LCD init failed");
    delay(50);
  }

  lcd.setBacklight(1);                // Turn on LCD backlight
  lcd.clear();

  // Display welcome message
  lcd.setCursor(0, 0);
  lcd.print("Morse Game");
  delay(1500);
  lcd.clear();
}

// ---------------- Main Loop ----------------
void loop() {
  int buttonState = digitalRead(BUTTON_PIN);  // Read button state

  // -------- Detect button press --------
  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;             // Mark button as pressed
    pressStartTime = millis();        // Record press start time
  }

  // -------- Detect button release --------
  if (buttonState == HIGH && buttonPressed) {
    buttonPressed = false;            // Mark button as released
    unsigned long pressDuration = millis() - pressStartTime;

    // Short press → dot (.)
    // Long press → dash (-)
    if (pressDuration < 300) {
      morseCode += ".";
    } else {
      morseCode += "-";
    }

    lastReleaseTime = millis();       // Record release time
    displayMorse();                   // Update Morse code display
  }

  // -------- Check for end of one letter --------
  // If no button activity for more than 1 second,
  // treat the current Morse sequence as one complete letter
  if (morseCode.length() > 0 && millis() - lastReleaseTime > 1000) {
    char letter = decodeMorse(morseCode);  // Decode Morse to letter
    displayLetter(letter);                 // Display decoded letter
    morseCode = "";                        // Clear buffer for next letter
  }
}

// ---------------- Display Functions ----------------

// Display the current Morse code input
void displayMorse() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Morse:");
  lcd.setCursor(0, 1);
  lcd.print(morseCode);
}

// Display the decoded letter on the LCD
void displayLetter(char letter) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Letter:");
  lcd.setCursor(0, 1);
  lcd.print(letter);
  delay(1500);                        // Keep the letter visible
  lcd.clear();
}

// ---------------- Morse Code Decoder ----------------
// Convert Morse code string into an English letter
char decodeMorse(String code) {
  if (code == ".-") return 'A';
  if (code == "-...") return 'B';
  if (code == "-.-.") return 'C';
  if (code == "-..") return 'D';
  if (code == ".") return 'E';
  if (code == "..-.") return 'F';
  if (code == "--.") return 'G';
  if (code == "....") return 'H';
  if (code == "..") return 'I';
  if (code == ".---") return 'J';
  if (code == "-.-") return 'K';
  if (code == ".-..") return 'L';
  if (code == "--") return 'M';
  if (code == "-.") return 'N';
  if (code == "---") return 'O';
  if (code == ".--.") return 'P';
  if (code == "--.-") return 'Q';
  if (code == ".-.") return 'R';
  if (code == "...") return 'S';
  if (code == "-") return 'T';
  if (code == "..-") return 'U';
  if (code == "...-") return 'V';
  if (code == ".--") return 'W';
  if (code == "-..-") return 'X';
  if (code == "-.--") return 'Y';
  if (code == "--..") return 'Z';

  // Unknown or invalid Morse code
  return '?';
}
