const int SoilMoistureSensor_Pin = A3;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int val = analogRead(SoilMoistureSensor_Pin);  
  Serial.print(val);
  Serial.print("\t");
  Serial.println();
  delay(100);
}
