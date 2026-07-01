#include <Wire.h>
#include <TM1650.h>

TM1650 display;

#define LED_RED 3

int countdownValue = 30;  // Countdown time (seconds)

// Display a four-digit number.
void showNumber(int num) {
  char buf[5];  //Four digits + one end character

  // Calculate each digit.
  int thousands = num / 1000;            // thousandth place
  int hundreds  = (num / 100) % 10;      // hundreds place
  int tens      = (num / 10) % 10;       // ten's place
  int ones      = num % 10;              // units digit

  // Convert to characters
  buf[0] = '0' + thousands;
  buf[1] = '0' + hundreds;
  buf[2] = '0' + tens;
  buf[3] = '0' + ones;
  buf[4] = '\0'; // String terminator

  display.displayString(buf);
}


void setup() {
  Wire.begin();
  Serial.begin(115200);

  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, LOW);

  display.init();
  display.displayOn();
  display.setBrightness(3);
}

void loop() {

  bool colonState = false;   // Used for countdown flashing

  // -------------------------
  // Countdown with colon blink
  // -------------------------
  while (countdownValue >= 0) {
    
    showNumber(countdownValue);

    // Colon blinking (using the first decimal point as the colon)
    colonState = !colonState;
    display.setDot(1, colonState);  // Bit 1 dot flash → Colon flash

    // Keep the decimal point closed.
    display.setDot(0, false);
    display.setDot(2, false);
    display.setDot(3, false);

    Serial.println(countdownValue);
    delay(1000);

    countdownValue--;
  }

  // --------------------------------------------------
  // Flashing mode when the countdown reaches 0 (Alarm mode)
  // The numbers, colon, decimal point, and LEDs all flash simultaneously
  // --------------------------------------------------
  while (true) {

    // Turn ON — show 0000 + all dots + LED
    showNumber(0);

    for (int i = 0; i < 4; i++) {
      display.setDot(i, true);  // All DOTS (including colons) are flashing
    }

    digitalWrite(LED_RED, HIGH);
    delay(300);

    // Turn OFF — close screen + LED off
    display.displayOff();
    digitalWrite(LED_RED, LOW);
    delay(300);

    display.displayOn();  // Re-enable for next cycle
  }
}
