// Define LED connected to digital pin 3 (PWM pin)
#define LED_PIN 3
// Define the potentiometer analog input pin
#define POT_PIN A0

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Read potentiometer value (0~1023)
  int potValue = analogRead(POT_PIN);

  // Map 0~1023 to 0~255 (LED brightness)
  int brightness = map(potValue, 0, 1023, 0, 255);

  // Output PWM to LED
  analogWrite(LED_PIN, brightness);

  // Print values to Serial Monitor
  Serial.print("Pot Value: ");
  Serial.print(potValue);
  Serial.print("   Brightness: ");
  Serial.println(brightness);

  delay(10);
}
