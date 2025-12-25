#define RainSensor 11     // Rain sensor digital output
#define LED_RED     3     // Red LED (D3)

void setup() {
  Serial.begin(115200);

  pinMode(RainSensor, INPUT);    // Rain sensor signal input
  pinMode(LED_RED, OUTPUT);      // LED as output
  digitalWrite(LED_RED, LOW);    // Turn off LED at startup
}

void loop() {
  int sensorState = digitalRead(RainSensor);

  // LOW → Raining
  if (sensorState == LOW) {
    Serial.println("Rain detected! Please CLOSE the window.");
    digitalWrite(LED_RED, HIGH);   // Rain → LED ON
  } 
  // HIGH → No rain
  else {
    Serial.println("No rain detected. You can OPEN the window.");
    digitalWrite(LED_RED, LOW);    // No rain → LED OFF
  }

  delay(200);
}
