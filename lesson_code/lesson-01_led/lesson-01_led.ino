#define LED_RED 3      // Define LED_RED as pin 3

void setup() {
  pinMode(LED_RED, OUTPUT);   // Set pin 3 as an output pin
}

void loop() {
  digitalWrite(LED_RED, HIGH);  // Turn the LED on
  delay(500);                   // Wait for 500 ms
  digitalWrite(LED_RED, LOW);   // Turn the LED off
  delay(500);                   // Wait for 500 ms
}
