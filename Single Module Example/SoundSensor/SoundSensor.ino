#define Sound_Pin  A0

void setup() {
  Serial.begin(115200);
}

void loop() {
  int val = analogRead(Sound_Pin);  // 0~1023
  int bars = map(val, 0, 1023, 0, 50);
  Serial.print(val);
  Serial.print("\t");
  for (int i = 0; i < bars; i++) Serial.print("*");
  Serial.println();
  delay(10);
}
