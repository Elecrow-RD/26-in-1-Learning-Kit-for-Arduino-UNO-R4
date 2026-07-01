#include <BH1750.h>      // Include BH1750 light sensor library
#include <Wire.h>       // Include I2C communication library

// Create a BH1750 sensor object with I2C address 0x5C
BH1750 lightMeter(0x5c);

// Variable to store the measured light intensity (lux)
float lux;

/************* LED Settings *************/
// Define the digital pin connected to the LED
#define LED_PIN 3

// Define the light intensity threshold (in lux)
// When light level is higher than this value, the LED will turn OFF
#define LUX_THRESHOLD 300

void setup() {
  // Initialize serial communication for debugging and monitoring
  Serial.begin(115200);

  // Initialize I2C communication (required for BH1750)
  Wire.begin();

  // Initialize the BH1750 sensor in continuous high resolution mode
  // Resolution: 1 lux
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x5c, &Wire)) {
    Serial.println(F("BH1750 Advanced begin"));   // Initialization successful
  } else {
    Serial.println(F("Error initialising BH1750")); // Initialization failed
  }

  // Configure the LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Turn ON the LED at startup (default state)
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  // Check if a new light measurement is ready
  // 'true' means the function will wait (blocking) until data is ready
  if (lightMeter.measurementReady(true)) {

    // Read the current light level in lux
    lux = lightMeter.readLightLevel();

    // Print the measured light value to the Serial Monitor
    Serial.print("[-] Light: [");
    Serial.print(lux);
    Serial.println("] lx");

    // -------- LED Control Logic --------
    // If the environment is bright enough
    if (lux > LUX_THRESHOLD) {
      // Turn OFF the LED when light is strong
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF (Too Bright)");
    } 
    // If the environment is dark
    else {
      // Turn ON the LED when light is weak
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON (Dark)");
    }
  }

  // Small delay to reduce serial output frequency
  delay(100);
}
