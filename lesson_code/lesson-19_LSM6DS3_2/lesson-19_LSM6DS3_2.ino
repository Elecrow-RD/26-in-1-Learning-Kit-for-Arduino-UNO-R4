#include <Arduino_LSM6DS3.h>
#include <MadgwickAHRS.h>

#define BUZ 10                  // Buzzer pin
#define SAMPLE_RATE 10          // IMU sampling rate (Hz)
#define TILT_THRESHOLD 30.0     // Inclination alarm threshold (degree)

Madgwick filter;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  pinMode(BUZ, OUTPUT);
  digitalWrite(BUZ, LOW);

  Serial.print("Initializing LSM6DS3 IMU... ");
  if (!IMU.begin()) {
    Serial.println("FAILED");
    while (1);
  }
  Serial.println("OK");

  filter.begin(SAMPLE_RATE);
}

void loop() {
  static unsigned long lastTime = 0;
  unsigned long now = millis();

  if (now - lastTime >= 1000 / SAMPLE_RATE) {
    checkTilt();
    lastTime = now;
  }
}

void checkTilt() {
  float ax, ay, az;
  float gx, gy, gz;

  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()
      && IMU.readAcceleration(ax, ay, az)
      && IMU.readGyroscope(gx, gy, gz)) {

    // Update attitude calculation
    filter.updateIMU(gx, gy, gz, ax, ay, az);

    float roll  = filter.getRoll();
    float pitch = filter.getPitch();

    Serial.print("Roll: ");a
    Serial.print(roll);
    Serial.print("°, Pitch: ");
    Serial.print(pitch);
    Serial.print("°  ");

    // Tilt detection
    if (abs(roll) > TILT_THRESHOLD || abs(pitch) > TILT_THRESHOLD) {
      digitalWrite(BUZ, HIGH);
      Serial.println("!!! TILT ALARM !!!");
    } else {
      digitalWrite(BUZ, LOW);
      Serial.println("Status: SAFE");
    }
  }
}
