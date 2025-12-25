#define Flame A1

int sensorValue = 0;        // value read from the pot

void setup() {
  Serial.begin(115200);
  pinMode(Flame, INPUT);
}

void loop() {
  sensorValue = analogRead(Flame);
  //  Serial.print("sensor = ");
  //  Serial.println(sensorValue);
  if (sensorValue < 100)
  {
    Serial.println("Flame detected");
  }
  delay(100);
}
