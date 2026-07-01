#include "DHT20.h"

DHT20 DHT;

#define BUZ 10   // Beeper is on pin D10

// Set the alarm threshold
float tempThreshold = 30.0;  // Alarm triggered when temperature exceeds 30°C
float humiThreshold = 40.0;  // Alarm when humidity is below 40%

uint8_t count = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("DHT20 + BUZZER Alarm");

  Wire.begin();
  DHT.begin();   

  pinMode(BUZ, OUTPUT);
  digitalWrite(BUZ, LOW);   // Default setting: Disable the buzzer

  delay(1000);
}

void loop()
{
  // Read every 1 second
  if (millis() - DHT.lastRead() >= 1000)
  {
    int status = DHT.read();   // Read the sensor
    float humidity = DHT.getHumidity();
    float temperature = DHT.getTemperature();

    // Print the title every 10 items.
    if ((count % 10) == 0)
    {
      count = 0;
      Serial.println();
      Serial.println("Type\tHumidity (%)\tTemp (°C)\tStatus");
    }
    count++;

    // print data
    Serial.print("DHT20\t");
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.print(temperature, 1);
    Serial.print("\t\t");

    // display status
    if (status == DHT20_OK) 
      Serial.println("DHT20_OK");
    else 
      Serial.println("READ ERROR");

    //===============================
    //        Alarm judgment logic
    //===============================
    bool alarm = false;   // Do we need to call the police?

    if (temperature > tempThreshold)
    {
      Serial.println("⚠ Temperature too high! Alarm triggered!");
      alarm = true;
    }

    if (humidity < humiThreshold)
    {
      Serial.println("⚠ Low humidity! Alarm triggered!");
      alarm = true;
    }

    // Control the buzzer
    if (alarm)
    {
      digitalWrite(BUZ, HIGH);   // The buzzer is ringing.
    }
    else
    {
      digitalWrite(BUZ, LOW);    // Turn off the buzzer when it is normal.
    }
  }
}
