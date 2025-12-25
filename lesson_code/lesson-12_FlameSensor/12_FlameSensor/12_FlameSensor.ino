#define Flame A1     // Flame sensor analog pin
#define LED_RED 3    // LED pin
#define BUZ 10       // Buzzer pin

int sensorValue = 0;

void setup() {
  Serial.begin(115200);

  pinMode(Flame, INPUT);   // Flame sensor input
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZ, OUTPUT);

  digitalWrite(LED_RED, LOW);  // LED off at start
  digitalWrite(BUZ, LOW);      // Buzzer off at start
}

void loop() {
  sensorValue = analogRead(Flame);  // Read flame sensor

  // Flame detected (value < 100)
  if (sensorValue < 100) {
    Serial.println("--- Flame detected! Warning!");

    digitalWrite(LED_RED, HIGH); // LED ON
    digitalWrite(BUZ, HIGH);     // Buzzer ON
  }
  else {
    Serial.println("Safe. No flame detected.");

    digitalWrite(LED_RED, LOW); // LED OFF
    digitalWrite(BUZ, LOW);     // Buzzer OFF
  }

  delay(100);
}
