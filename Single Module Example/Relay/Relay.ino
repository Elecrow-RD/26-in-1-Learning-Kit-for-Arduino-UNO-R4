#define Relay 11

void setup() {
  pinMode(Relay, OUTPUT);
}


void loop() {
  digitalWrite(Relay, HIGH);
  delay(3000);
  digitalWrite(Relay, LOW);
  delay(3000);
}
