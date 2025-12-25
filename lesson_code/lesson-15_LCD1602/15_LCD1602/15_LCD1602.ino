/******************* LCD1602 + BH1750 *******************/
#include "Adafruit_LiquidCrystal.h"  // LCD I2C library
#include <BH1750.h>                  // Light sensor library
#include <Wire.h>                    // I2C communication

Adafruit_LiquidCrystal lcd(0);       // LCD (I2C address handled by library)
BH1750 lightMeter(0x5c);             // BH1750 light sensor address 0x5C

float lux = 0;                       // Light intensity value

void setup() {
  Serial.begin(115200);   // Serial for debugging
  Wire.begin();           // Start I2C bus

  /************* LCD Initialization *************/
  while (!lcd.begin(16, 2)) {        // Initialize LCD (16x2)
    Serial.println("LCD init failed! Check wiring.");
    delay(50);
  }
  Serial.println("LCD initialized.");
  lcd.setBacklight(1);               // Turn on LCD backlight
  lcd.clear();

  /************* BH1750 Initialization *************/
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x5c, &Wire)) {
    Serial.println("BH1750 init success!");
  } else {
    Serial.println("Error initializing BH1750.");
    lcd.setCursor(0, 0);
    lcd.print("BH1750 ERROR!");
    while (1); // Stop program if sensor fails
  }

  lcd.setCursor(0, 0);
  lcd.print("Light Sensor OK");
  delay(1000);
  lcd.clear();
}

void loop() {
  if (lightMeter.measurementReady(true)) {
    lux = lightMeter.readLightLevel();   // Read light intensity

    /************* Serial port output *************/
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");

    /************* LCD output *************/
    lcd.setCursor(0, 0);
    lcd.print("Light:        ");   // Clear old characters
    lcd.setCursor(7, 0);
    lcd.print(lux);

    lcd.setCursor(0, 1);
    lcd.print("Unit: lux     ");

    delay(200); // Prevent screen flickering
  }
}
