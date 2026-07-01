#define LED_PIN 3
#define BUTTON_PIN 0

void setup() {
  pinMode(LED_PIN, OUTPUT);

  // Use internal pull-up resistor so the button reads HIGH when not pressed
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // Read the button state (pressed = LOW)
  int buttonState = digitalRead(BUTTON_PIN);

  // Simple debounce: wait 10ms after detecting a press, then check again
  if (buttonState == LOW) {
    delay(10);  // Debounce delay
    if (digitalRead(BUTTON_PIN) == LOW) {
      digitalWrite(LED_PIN, HIGH);  // Turn on the LED
    }
  } else {
    digitalWrite(LED_PIN, LOW);     // Turn off the LED when released
  }
}
