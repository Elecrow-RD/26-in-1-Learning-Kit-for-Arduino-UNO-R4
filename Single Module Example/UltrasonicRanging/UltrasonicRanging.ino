#include <HCSR04.h>
// Initialize sensor that uses digital pins 13 and 12.
const byte triggerPin = 8;
const byte echoPin = 2;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

void setup()
{
  Serial.begin(115200);

}
void loop()
{
  float distance = distanceSensor.measureDistanceCm();
  String Value = String(distance);
  delay(500);
  Serial.print((int)distance);
  Serial.println("\t cm");

}
