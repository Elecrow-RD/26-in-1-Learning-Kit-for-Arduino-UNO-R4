#include <HCSR04.h>
#include <Servo.h>

/* ---------- Ultrasonic ---------- */
const byte triggerPin = 8;
const byte echoPin = 2;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

/* ---------- Servo ---------- */
#define SERVO1_PIN 6

Servo myservo1;

int doorOpenAngle = 90;    // Door open angle (adjustable)
int doorCloseAngle = 0;    // Door close angle

/* ---------- Buzzer ---------- */
#define BUZ 10

/* ---------- State variables ---------- */
bool doorIsOpen = false;          // Current door state
unsigned long lastDetectTime = 0; // Last time a person was detected
const unsigned long closeDelay = 5000; // 5 seconds

void setup() {
  Serial.begin(115200);

  myservo1.attach(SERVO1_PIN, 600, 2520);

  pinMode(BUZ, OUTPUT);

  // Initial state: door closed
  myservo1.write(doorCloseAngle);
}

void loop() {

  /* ---------- 1. Read distance ---------- */
  float distance = distanceSensor.measureDistanceCm();
  if (distance < 0) 
    return;

  Serial.print("Distance: ");
  Serial.print((int)distance);
  Serial.println(" cm");

  /* ---------- 2. Anti-pinch alarm ---------- */
  if (distance > 0 && distance <= 10) {
    buzzerWarning();
  }

  /* ---------- 3. Door opening logic ---------- */
  if (distance > 0 && distance <= 50) {
    openDoor();
    lastDetectTime = millis(); // Record the time when a person is detected
  }

  /* ---------- 4. Door closing logic ---------- */
  if (doorIsOpen) {
    if (millis() - lastDetectTime >= closeDelay) {
      closeDoor();
    }
  }

  delay(200);
}

/* ================== Function definitions ================== */

// Open the door
void openDoor() {
  if (!doorIsOpen) {
    myservo1.write(doorOpenAngle);
    doorIsOpen = true;
    Serial.println("Door OPEN");
  }
}

// Close the door
void closeDoor() {
  myservo1.write(doorCloseAngle);
  doorIsOpen = false;
  Serial.println("Door CLOSE");
}

// Buzzer warning (two beeps)
void buzzerWarning() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUZ, HIGH);
    delay(150);
    digitalWrite(BUZ, LOW);
    delay(150);
  }
}
