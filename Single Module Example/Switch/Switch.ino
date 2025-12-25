#define Switch 11


void setup() {
  Serial.begin(115200);
  pinMode(Switch, INPUT);
}

void loop() {
  if (digitalRead(Switch) == HIGH) {
      Serial.println("Switch press");
  } 
}
