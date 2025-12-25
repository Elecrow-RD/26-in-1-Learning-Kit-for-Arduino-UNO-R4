// Define the digital pin used to control the relay module
#define RELAY_PIN 3   // Relay control signal connected to digital pin D3

void setup() {
  // Configure the relay pin as an OUTPUT
  // This allows Arduino to send HIGH / LOW signals to control the relay
  pinMode(RELAY_PIN, OUTPUT);

  // Initialize serial communication between Arduino and the computer
  // 115200 is the baud rate (communication speed)
  Serial.begin(115200);
  Serial.println("Relay Auto Control Demo Start");

  // Make sure the relay is OFF when Arduino starts
  // LOW means the relay is not energized (LED OFF)
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  // Turn the relay ON
  // HIGH energizes the relay coil and closes the NO contact
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println("Relay ON (LED ON)");

  // Keep the relay ON for 2 seconds (2000 milliseconds)
  delay(2000);

  // Turn the relay OFF
  // LOW de-energizes the relay coil and opens the contact
  digitalWrite(RELAY_PIN, LOW);
  Serial.println("Relay OFF (LED OFF)");

  // Keep the relay OFF for 2 seconds
  delay(2000);
}
