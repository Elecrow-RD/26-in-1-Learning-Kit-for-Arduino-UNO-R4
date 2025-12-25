// Define the LED pin connected to digital pin 3
#define LED_PIN 3

// Define the soil moisture sensor analog input pin
#define MOISTURE_PIN A0   // Analog input pin for moisture sensor

void setup() {
  // Set the LED pin as output so Arduino can turn it ON/OFF
  pinMode(LED_PIN, OUTPUT);

  // Start the Serial Monitor at 115200 baud rate
  Serial.begin(115200);
  Serial.println("Soil Moisture Sensor Demo Start");
}

void loop() {
  // Read soil moisture sensor value (range: 0 ~ 1023)
  // Lower value = more moisture, Higher value = dryer soil
  int moistureValue = analogRead(MOISTURE_PIN);

  // Print the moisture value to the Serial Monitor
  Serial.print("Soil Moisture: ");
  Serial.println(moistureValue);

  // Simple control logic:
  // If moisture value is low (soil is wet), turn ON the LED
  // If moisture value is high (soil is dry), turn OFF the LED
  if (moistureValue < 200) {  
    // When value < 200 → soil is wet → LED ON
    digitalWrite(LED_PIN, HIGH);
  } else {
    // Otherwise soil is dry → LED OFF
    digitalWrite(LED_PIN, LOW);
  }

  // Wait for 0.5 seconds before the next reading
  delay(500);
}
