// 24BYJ-48 直接驱动，不引用任何库
// ULN2003 板输入 IN1~IN4 接 Arduino D8~D11
const uint8_t PIN[4] = {13, 12, 7, 4};

// 8 拍正转节拍（1 为 HIGH，0 为 LOW）
const uint8_t SEQ[8][4] = {
  {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,1,1,0},
  {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1}
};

void setup() {
  for (uint8_t i = 0; i < 4; i++) pinMode(PIN[i], OUTPUT);
}

void loop() {
  static uint32_t cnt = 0;          // 已走步数
  if (cnt < 4096) {                 // 一圈 = 4096 步
    uint8_t phase = cnt & 7;        // 0~7 循环
    for (uint8_t i = 0; i < 4; i++)
      digitalWrite(PIN[i], SEQ[phase][i]);
    delay(2);                       // 2 ms/步，约 4 r/min
    ++cnt;
  } else {                          // 转完停转
    for (uint8_t i = 0; i < 4; i++) digitalWrite(PIN[i], LOW);
  }
}
