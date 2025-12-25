// Define hardware pins
#define MQ2Pin A2    // MQ2 smoke sensor connected to analog pin A2
#define BUZ 10       // Buzzer connected to digital pin 10

// Define smoke alarm threshold (adjust according to actual testing)
// Note: MQ2 value is about tens~200 without smoke; the higher the smoke concentration, the higher the value (need calibration via actual test)
const int smokeThreshold = 300;  

int MQ2Value = 0;  // Store the value read from MQ2 sensor

void setup() {
  // Initialize serial port (for debugging to view sensor values)
  Serial.begin(115200);
  // Initialize pin modes
  pinMode(MQ2Pin, INPUT);   // MQ2 sensor set as input mode
  pinMode(BUZ, OUTPUT);     // Buzzer set as output mode
  // Turn off the buzzer initially
  digitalWrite(BUZ, LOW);
}

void loop() {
  // Read analog value from MQ2 sensor
  MQ2Value = analogRead(MQ2Pin);
  
  // Print current sensor value to serial port (for debugging and threshold calibration)
  Serial.print("Smoke sensor value: ");
  Serial.println(MQ2Value);

  // Smoke detection logic: trigger alarm if value exceeds threshold, otherwise turn off buzzer
  if (MQ2Value > smokeThreshold) {
    digitalWrite(BUZ, HIGH);  // Turn on buzzer for alarm
    Serial.println("⚠️ Smoke detected! Buzzer alarming...");
  } else {
    digitalWrite(BUZ, LOW);   // Turn off buzzer
    Serial.println("Environment normal, no smoke detected");
  }

  delay(200);  // Detection interval (adjustable as needed, 100-500ms recommended)
}
