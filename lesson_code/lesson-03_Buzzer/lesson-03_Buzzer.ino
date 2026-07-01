#define Buzzer_Pin 3  // Define the digital pin connected to the active buzzer

void setup() {
  pinMode(Buzzer_Pin, OUTPUT);      // Set buzzer pin as output
}

void loop() {
  // 1. Normal beep
  digitalWrite(Buzzer_Pin, HIGH);   // Turn on buzzer (start sound)
  delay(200);                        // Keep buzzer on for 200 milliseconds
  digitalWrite(Buzzer_Pin, LOW);    // Turn off buzzer (stop sound)
  delay(500);                        // Wait 500 milliseconds before next action
  // 2. Alarm sound (repeated short beeps)
  for (int i = 0; i < 5; i++) {    // Repeat 5 times
    digitalWrite(Buzzer_Pin, HIGH); // Turn on buzzer
    delay(150);                      // Buzzer on for 150 milliseconds
    digitalWrite(Buzzer_Pin, LOW);  // Turn off buzzer
    delay(150);                      // Pause 150 milliseconds between beeps
  }
  // 3. Rhythm beep pattern (short → short → long)
  // Short beep 1
  digitalWrite(Buzzer_Pin, HIGH);   // Turn on buzzer
  delay(100);                        // Buzzer on for 100 milliseconds
  digitalWrite(Buzzer_Pin, LOW);    // Turn off buzzer
  delay(100);                        // Pause 100 milliseconds
  // Short beep 2
  digitalWrite(Buzzer_Pin, HIGH);   // Turn on buzzer
  delay(100);                        // Buzzer on for 100 milliseconds
  digitalWrite(Buzzer_Pin, LOW);    // Turn off buzzer
  delay(100);                        // Pause 100 milliseconds
  // Long beep
  digitalWrite(Buzzer_Pin, HIGH);   // Turn on buzzer
  delay(400);                        // Buzzer on for 400 milliseconds
  digitalWrite(Buzzer_Pin, LOW);    // Turn off buzzer
  delay(500);                        // Pause 500 milliseconds before next loop
  // Pause 1 second before repeating the entire loop
  delay(1000);
}
