#define PIR_PIN   9       // PIR human body infrared sensor signal terminal
#define LED_PIN   3       // LED light (Digital Port D3)

int PIRState = 0;         // Used to store the status of the sensor

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);     // The PIR is set as input.
  pinMode(LED_PIN, OUTPUT);    // The LED lights are set to output.
  digitalWrite(LED_PIN, LOW);  // Turn off the lights initially
}

void loop() {
  PIRState = digitalRead(PIR_PIN);  // Read the PIR status (HIGH or LOW)

  if (PIRState == HIGH) {
    Serial.println("Detected human body");
    digitalWrite(LED_PIN, HIGH);    // Detecting human presence → Light turns on
  } 
  else {
    Serial.println("No human presence was detected.");
    digitalWrite(LED_PIN, LOW);     // No detection → Light off
  }
}
