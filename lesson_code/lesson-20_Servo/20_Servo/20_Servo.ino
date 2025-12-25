#include <Servo.h>

// ====== Pin definition ======
#define Servo1_PIN 6
#define LinearPotentiometer_Pin A3

// ====== Create a servo object ======
Servo myservo1;

void setup() {
  Serial.begin(115200);

  // Bind the servo pin (with adjustable pulse width range)
  myservo1.attach(Servo1_PIN, 600, 2520);

  Serial.println("Potentiometer -> Servo Control Ready");
}

void loop() {
  // Read the sliding rheostat
  int potValue = analogRead(LinearPotentiometer_Pin);  // 0 ~ 1023

  // Value mapping: Potentiometer -> Rudder angle
  int angle = map(potValue, 0, 1023, 0, 180);

  // Control the rotation of the servo motor
  myservo1.write(angle);

  // Serial port debugging output
  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  -> Angle: ");
  Serial.println(angle);

  delay(15);  // Give the steering gear some reaction time
}
