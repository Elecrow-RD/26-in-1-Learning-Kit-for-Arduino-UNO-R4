// ================== Pin Definitions ==================
#define LED1 11
#define LED2 9
#define LED3 8

#define BTN1 10
#define BTN2 3
#define BTN3 0

// ================== Game Settings ==================
int levelLength = 5;        // Sequence length (difficulty)
int flashDelay = 400;       // LED flash speed (ms)

// ================== Variables ==================
int ledSequence[10];
int userIndex = 0;

// ================== Setup ==================
void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);

  randomSeed(analogRead(A0));
  startGame();
}

// ================== Main Loop ==================
void loop() {
  int button = readButton();

  if (button != 0) {
    flashSingleLED(button);

    if (button == ledSequence[userIndex]) {
      userIndex++;

      // All correct
      if (userIndex >= levelLength) {
        successLED();
        delay(500);
        startGame();
      }
    } else {
      failLED();
      delay(500);
      startGame();
    }
  }
}

// ================== Game Functions ==================

void startGame() {
  userIndex = 0;
  generateSequence();
  showSequence();
}

// Generate random LED order
void generateSequence() {
  for (int i = 0; i < levelLength; i++) {
    ledSequence[i] = random(1, 4); // 1~3
  }
}

// Show LED flashing sequence
void showSequence() {
  delay(500);
  for (int i = 0; i < levelLength; i++) {
    flashSingleLED(ledSequence[i]);
    delay(200);
  }
}

// Read button input
int readButton() {
  if (digitalRead(BTN1) == LOW) return 1;
  if (digitalRead(BTN2) == LOW) return 2;
  if (digitalRead(BTN3) == LOW) return 3;
  return 0;
}

// Flash a single LED
void flashSingleLED(int num) {
  int ledPin = (num == 1) ? LED1 : (num == 2) ? LED2 : LED3;
  digitalWrite(ledPin, HIGH);
  delay(flashDelay);
  digitalWrite(ledPin, LOW);
}

// ================== Success Effect ==================
void successLED() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  delay(1000);   // All LEDs ON for 1 second
  allLEDOff();
}

// ================== Fail Effect (5Hz for 2 seconds) ==================
void failLED() {
  for (int i = 0; i < 10; i++) {   // 2 seconds / 200ms = 10 times
    allLEDOn();
    delay(100);
    allLEDOff();
    delay(100);
  }
}

// Utility functions
void allLEDOn() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
}

void allLEDOff() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}
