#include <Wire.h>
#include "DHT20.h"
#include <BH1750.h>
#include "Adafruit_LiquidCrystal.h"

// ================== object definition ==================
DHT20 DHT;
BH1750 lightMeter(0x5c);
Adafruit_LiquidCrystal lcd(0);

// ================== macro definition ==================
#define BUZ 10
#define TEMP_ALARM 30.0
#define DARK_LUX 50.0

// ================== variable ==================
float temperature = 0;
float humidity = 0;
float lux = 0;

// ================== initialize ==================
void setup() {
  Serial.begin(115200);
  Wire.begin();

  // ---- DHT20 ----
  DHT.begin();
  delay(1000);

  // ---- BH1750 ----
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x5c, &Wire)) {
    Serial.println("BH1750 init OK");
  } else {
    Serial.println("BH1750 init FAIL");
  }

  // ---- LCD1602 ----
  while (!lcd.begin(16, 2)) {
    Serial.println("LCD init failed");
    delay(50);
  }
  lcd.setBacklight(1);
  lcd.clear();

  // ---- buzzer ----
  pinMode(BUZ, OUTPUT);
  digitalWrite(BUZ, LOW);

  Serial.println("Mini Environment Station Ready!");
}

// ================== major cycle ==================
void loop() {

  // ----------- Read DHT20 -----------
  if (millis() - DHT.lastRead() >= 1000) {
    int status = DHT.read();
    if (status == DHT20_OK) {
      temperature = DHT.getTemperature();
      humidity = DHT.getHumidity();
    }
  }

  // ----------- Read the light intensity. -----------
  if (lightMeter.measurementReady(true)) {
    lux = lightMeter.readLightLevel();
  }

  // ----------- LCD display -----------
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C ");
  lcd.print("H:");
  lcd.print(humidity, 0);
  lcd.print("% ");

  lcd.setCursor(0, 1);
  if (lux < DARK_LUX) {
    lcd.print("Too Dark       ");
  } else {
    lcd.print("Lux:");
    lcd.print(lux, 0);
    lcd.print("          ");
  }

  // ----------- Temperature alarm -----------
  if (temperature > TEMP_ALARM) {
    digitalWrite(BUZ, HIGH);
    delay(100);
    digitalWrite(BUZ, LOW);
  }

  // ----------- Serial port debugging output -----------
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" C | Hum: ");
  Serial.print(humidity);
  Serial.print(" % | Lux: ");
  Serial.println(lux);

  delay(500);
}
