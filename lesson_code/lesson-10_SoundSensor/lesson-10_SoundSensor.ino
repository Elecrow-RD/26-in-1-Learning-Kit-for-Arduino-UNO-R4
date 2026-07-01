#define Sound_Pin  A0
#define Threshold 300   // The sound threshold can be adjusted according to the actual environment.

#define LED_RED 3

void setup() {
  Serial.begin(115200);

  pinMode(LED_RED, OUTPUT);
  // Initialization, turn off the lights
  digitalWrite(LED_RED, LOW);
}

void loop() {
  int val = analogRead(Sound_Pin);  // 0~1023

  Serial.print("Sound Value = ");
  Serial.println(val);

  // Determine whether it exceeds the threshold
  if (val > Threshold) {
    Serial.println(">>> Sound detected! Red LED ON");
    digitalWrite(LED_RED, HIGH);    // Loud sound → Red light on
  } else {
    digitalWrite(LED_RED, LOW);     // Voice becomes quiet → Red light goes out
  }

  delay(50);
}
