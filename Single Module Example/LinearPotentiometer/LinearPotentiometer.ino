const int LinearPotentiometer_Pin = A3;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int val = analogRead(LinearPotentiometer_Pin);  
  Serial.print(val);
  Serial.print("\t");
  Serial.println();
  delay(100);
}
