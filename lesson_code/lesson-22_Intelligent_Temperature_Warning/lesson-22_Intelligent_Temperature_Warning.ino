#include <Wire.h>
#include "DHT20.h"

#define LED_RED     11
#define LED_YELLOW  10
#define LED_GREEN   9
#define BUZ         3

DHT20 DHT;

// Temperature threshold (can be modified as needed)
#define TEMP_NORMAL_MAX   28.0
#define TEMP_HIGH_MAX     32.0

void setup() {
  Serial.begin(115200);
  Wire.begin();
  DHT.begin();

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZ, OUTPUT);

  Serial.println("=== Intelligent Temperature Warning System ===");
}

void loop() {
  if (millis() - DHT.lastRead() >= 1000) {   // ⭐Key point: 1 time per second
    int status = DHT.read();

    if (status != DHT20_OK) {
      return;
    }

    float temp = DHT.getTemperature();
    float humi = DHT.getHumidity();

    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print(" °C  |  Humidity: ");
    Serial.print(humi);
    Serial.println(" %");

    // ====== state judgement ======
    if (temp < TEMP_NORMAL_MAX) {
      normalState();
    } 
    else if (temp < TEMP_HIGH_MAX) {
      warningState();
    } 
    else {
      alarmState();
    }
  }
}

// ================== state function ==================

// Normal state: Green light is on, buzzer is off
void normalState() {
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(BUZ, LOW);
}

// High blood pressure state: Yellow light is on, and the buzzer makes a short beep.
void warningState() {
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_RED, LOW);

  digitalWrite(BUZ, HIGH);
  delay(100);
  digitalWrite(BUZ, LOW);
}

// High temperature alarm: Red light flashes, and the buzzer keeps sounding an alarm.
void alarmState() {
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);

  digitalWrite(LED_RED, HIGH);
  digitalWrite(BUZ, HIGH);
  delay(300);
  digitalWrite(LED_RED, LOW);
  digitalWrite(BUZ, LOW);
  delay(300);
}
