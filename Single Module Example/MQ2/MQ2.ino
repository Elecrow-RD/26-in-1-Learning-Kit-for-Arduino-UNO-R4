#define MQ2Pin A2
int MQ2Value = 0;
void setup() {
  Serial.begin(115200);
  pinMode(MQ2Pin, INPUT);
}
void loop() {
  MQ2Value = analogRead(MQ2Pin); 
  Serial.println(MQ2Value); 
  delay(100);  
  }
