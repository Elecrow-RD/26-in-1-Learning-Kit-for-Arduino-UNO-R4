#include <Stepper.h>
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the Stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 4, 7, 12, 13);

int stepCount = 0;         // number of steps the motor has taken

void setup() {
  // initialize the serial port:
  Serial.begin(115200);
}

void loop() {
  // step one step:
  myStepper.step(1);
  Serial.print("steps:");
  Serial.println(stepCount);
  stepCount++;
  delay(10);
}
