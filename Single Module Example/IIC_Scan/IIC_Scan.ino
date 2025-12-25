#include <Wire.h>

void setup() {
  Wire.begin();        
  Serial.begin(115200);
  Serial.println(F("\nI2C 地址扫描开始..."));
  Serial.println(F("地址 HEX DEC"));
  Serial.println(F("-----------"));
}

void loop() {
  byte nFound = 0;

  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print(F(" 0x"));
      if (addr < 16) Serial.print('0');
      Serial.print(addr, HEX);
      Serial.print(F("   "));
      Serial.println(addr, DEC);
      nFound++;
    }
  }

  if (nFound == 0)
    Serial.println(F("未检测到设备！"));
  else {
    Serial.print(F("\n共发现 "));
    Serial.print(nFound);
    Serial.println(F(" 个设备"));
  }

  Serial.println(F("等待 5 秒后重新扫描..."));
  delay(5000);
}
