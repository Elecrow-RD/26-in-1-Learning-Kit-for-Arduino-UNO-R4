#include <Servo.h>

#define  Servo1 6
#define  Servo2 5
Servo myservo1;
Servo myservo2;
int pos = 0;

void setup() {
  myservo1.attach(Servo1, 600, 2520);
  myservo2.attach(Servo2, 600, 2520);
  //  myservo1.write(0);

}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    myservo1.write(pos);
    myservo2.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo1.write(pos);
    myservo2.write(pos);
    delay(15);
  }
}
