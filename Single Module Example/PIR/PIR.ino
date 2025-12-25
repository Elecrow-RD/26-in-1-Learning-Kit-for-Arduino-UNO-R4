#define PIR  9    

int PIRState = 0;        

void setup() {
  Serial.begin(115200);
  pinMode(PIR, INPUT);
}

void loop() {
  PIRState = digitalRead(PIR);
  if (PIRState == HIGH) 
  {
    Serial.println("Detected human body");
  } 
  else 
  {
    Serial.println("No human presence was detected.");
  }
}
