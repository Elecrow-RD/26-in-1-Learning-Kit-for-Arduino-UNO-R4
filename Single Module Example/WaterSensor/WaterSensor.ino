#define WaterSensor 11


void setup() {
  Serial.begin(115200);
  pinMode(WaterSensor, INPUT);
}

void loop() {

  if (digitalRead(WaterSensor) == LOW) {
    Serial.println("Rain has been detected.");
  }
}
