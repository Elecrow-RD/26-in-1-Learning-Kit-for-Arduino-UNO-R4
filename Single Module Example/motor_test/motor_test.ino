#include <Servo.h>
#include "Adafruit_LiquidCrystal.h"  // Include the Adafruit LCD library for I2C communication

Adafruit_LiquidCrystal lcd(0);  // Create LCD object with I2C address parameter (1 may correspond to 0x27)
/* ---------- 硬件引脚 ---------- */
const uint8_t PIN_SERVO1 = 6;
const uint8_t PIN_SERVO2 = 5;
const uint8_t PIN_COIL1  = 4;
const uint8_t PIN_COIL2  = 7;
const uint8_t PIN_COIL3  = 12;
const uint8_t PIN_COIL4  = 13;

/* ---------- 步进参数 ---------- */
const uint16_t STEPS_PER_REV  = 200;
const uint8_t  STEP_SEQUENCE[8] = {
  0b1000, 0b1100, 0b0100, 0b0110,
  0b0010, 0b0011, 0b0001, 0b1001
};          // 8 拍半步序
volatile uint8_t  seqIdx = 0;
volatile uint32_t stepCnt = 0;

/* ---------- 舵机参数 ---------- */
Servo srv1, srv2;
int16_t  servoAngle = 0;        // 当前角度
int8_t   servoDir   = 1;        // 1 递增，-1 递减
const uint16_t SERVO_REFRESH_MS = 20; // 20 ms 更新一次舵机角度

/* ---------- 时间片调度 ---------- */
uint32_t lastStepTime = 0;
const uint32_t STEP_PERIOD_US = 2'000; // 500 步/秒，可改
uint32_t lastServoTime = 0;

/* ---------- 底层：非阻塞写线圈 ---------- */
inline void writeCoils(uint8_t pattern) {
  digitalWrite(PIN_COIL1, pattern & 0x08 ? HIGH : LOW);
  digitalWrite(PIN_COIL2, pattern & 0x04 ? HIGH : LOW);
  digitalWrite(PIN_COIL3, pattern & 0x02 ? HIGH : LOW);
  digitalWrite(PIN_COIL4, pattern & 0x01 ? HIGH : LOW);
}

/* ---------- 初始化 ---------- */
void setup() {
  Serial.begin(115200);
  pinMode(PIN_COIL1, OUTPUT);
  pinMode(PIN_COIL2, OUTPUT);
  pinMode(PIN_COIL3, OUTPUT);
  pinMode(PIN_COIL4, OUTPUT);
  srv1.attach(PIN_SERVO1, 600, 2520);
  srv2.attach(PIN_SERVO2, 600, 2520);
    // Initialize LCD with 16 columns and 2 rows; retry if initialization fails
  while (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");  // Print error message
    delay(50);  // Wait 50ms before retrying
  }
  
  Serial.println("Backpack init'd.");  // Print success message once initialized
  
  // Set cursor to column 0, row 0 (top-left corner) and display "HELLO WORLD"
  lcd.setCursor(0, 0);
  lcd.print("HELLO WORLD");
  delay(1000);  // Wait 1 second before next action
  
  // Set cursor to column 0, row 1 (second row) and display "Bye Bye"
  lcd.setCursor(0, 1);
  lcd.print("Bye Bye");
  delay(1000);  // Wait 1 second before next action
  
//  lcd.clear();  // Clear the display and reset cursor to (0,0)
  lcd.setBacklight(1);  // Turn off the backlight (0 = off, non-zero = on)
}

/* ---------- 主循环：纯非阻塞 ---------- */
void loop() {
  uint32_t now = micros();
  /* ---- 1. 步进任务 ---- */
  if (now - lastStepTime >= STEP_PERIOD_US) {
    lastStepTime = now;
    seqIdx = (seqIdx + 1) & 7;          // 下一步序
    writeCoils(STEP_SEQUENCE[seqIdx]);
    stepCnt++;
    if (stepCnt % STEPS_PER_REV == 0) { // 每圈打印一次
      Serial.println(F(">>> 1 rev"));
    }
  }

  /* ---- 2. 舵机任务 ---- */
  if (millis() - lastServoTime >= SERVO_REFRESH_MS) {
    lastServoTime = millis();
    servoAngle += servoDir;
    if (servoAngle >= 180) { servoAngle = 180; servoDir = -1; }
    if (servoAngle <= 0)   { servoAngle = 0;   servoDir =  1; }
    srv1.write(servoAngle);
    srv2.write(servoAngle);
  }

  /* ---- 3. 其他后台任务 ---- */
  // 这里可以放 Serial 解析、传感器读取、OLED 刷新等，都不会被阻塞
}
