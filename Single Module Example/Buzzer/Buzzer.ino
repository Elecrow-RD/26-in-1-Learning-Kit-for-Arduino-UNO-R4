#define BUZ 10


void setup() {
  pinMode(BUZ, OUTPUT);
}
void loop() {
  digitalWrite(BUZ, HIGH);
  delay(1000);
  digitalWrite(BUZ, LOW);
  delay(1000);
}
