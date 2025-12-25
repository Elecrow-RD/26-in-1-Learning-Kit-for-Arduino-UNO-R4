#define LED_PIN 3
#define SWITCH_PIN 0

void setup() {
  pinMode(LED_PIN, OUTPUT);
Serial.begin(9600);

  // Use internal pull-up: default state is HIGH (OFF), 
  //becomes LOW when switch is ON
  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

void loop() {
  int switchState = digitalRead(SWITCH_PIN);
  Serial.println(switchState);
  // When the switch is turned ON, the signal goes LOW
  if (switchState == HIGH) {
    digitalWrite(LED_PIN, HIGH);   // Turn on the LED
  } else {
    digitalWrite(LED_PIN, LOW);    // Turn off the LED
  }

}

