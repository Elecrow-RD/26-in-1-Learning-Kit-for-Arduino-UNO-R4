#include <HCSR04.h>

// Ultrasonic sensor pins
const byte triggerPin = 8;
const byte echoPin = 2;

// Buzzer pin
#define BUZZER 10

UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

// Alarm threshold (unit: cm)
const int dangerDistance = 15;

void setup()
{
  Serial.begin(115200);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
}

void loop()
{
  float distance = distanceSensor.measureDistanceCm();

  Serial.print((int)distance);
  Serial.println(" cm");

  // If the distance is too close → alarm
  if (distance > 0 && distance < dangerDistance) {
    digitalWrite(BUZZER, HIGH);   // Turn buzzer ON
  } else {
    digitalWrite(BUZZER, LOW);    // Turn buzzer OFF
  }

  delay(500);
}
