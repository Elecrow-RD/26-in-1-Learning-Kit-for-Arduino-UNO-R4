/*
  IR Remote + LED Control
  Button 1: Red light on
  Button 2: Yellow light on
  Button 3: Green light on
  Button 4: Three lights in sequence (cyclic)
*/

#include <DIYables_IRcontroller.h> 

#define IR_RECEIVER_PIN 3

DIYables_IRcontroller_21 irController(IR_RECEIVER_PIN, 200);

// LED pin
#define LED_RED 11
#define LED_YELLOW 10
#define LED_GREEN 9

int mode = 0;  // Current working mode: 1 = Red light / 2 = Yellow light / 3 = Green light / 4 = Continuous flow

void setup() {
  Serial.begin(115200);
  irController.begin();

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
}

// Encapsulate a function: Clear all lights
void allOff() {
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void loop() {

  // ---- Read infrared key value ----
  Key21 command = irController.getKey();
  if (command != Key21::NONE) {
    switch (command) {

      case Key21::KEY_CH_MINUS:
        Serial.println("CH-");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_CH:
        Serial.println("CH");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_CH_PLUS:
        Serial.println("CH+");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_PREV:
        Serial.println("<<");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_NEXT:
        Serial.println(">>");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_PLAY_PAUSE:
        Serial.println(">||");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_VOL_MINUS:
        Serial.println("–");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_VOL_PLUS:
        Serial.println("+");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_EQ:
        Serial.println("EQ");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_100_PLUS:
        Serial.println("100+");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_200_PLUS:
        Serial.println("200+");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_0:
        Serial.println("Turn off all the lights");
        mode = 0;
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_1:  //Button 1
        Serial.println("Mode 1: The red light is on");
        mode = 1;
        break;

      case Key21::KEY_2:  // Button 2
        Serial.println("Mode 2: The yellow light is on");
        mode = 2;
        break;

      case Key21::KEY_3:  // Button 3
        Serial.println("Mode 3: The green light is on");
        mode = 3;
        break;

      case Key21::KEY_4:  // Button 4
        Serial.println("Mode 4: Three lamps and flowing water");
        mode = 4;
        break;

      case Key21::KEY_5:
        Serial.println("5");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_6:
        Serial.println("6");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_7:
        Serial.println("7");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_8:
        Serial.println("8");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_9:
        Serial.println("9");
        // TODO: YOUR CONTROL
        break;

      default:
        Serial.println("WARNING: undefined command:");
        break;
    }
  }

  // ---- Perform the action according to the mode. ----
  switch (mode) {
    case 0:
      allOff();
      break;

    case 1: // The red light is on
      allOff();
      digitalWrite(LED_RED, HIGH);
      break;

    case 2: // The yellow light is on
      allOff();
      digitalWrite(LED_YELLOW, HIGH);
      break;

    case 3: // The green light is on
      allOff();
      digitalWrite(LED_GREEN, HIGH);
      break;

    case 4: // waterfall light
      allOff();
      digitalWrite(LED_RED, HIGH);
      delay(300);

      allOff();
      digitalWrite(LED_YELLOW, HIGH);
      delay(300);

      allOff();
      digitalWrite(LED_GREEN, HIGH);
      delay(300);
      break;

    default:
      // Initial state: All off
      allOff();
      break;
  }
}

