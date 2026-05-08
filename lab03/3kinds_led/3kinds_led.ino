// 三色渐变呼吸灯：红→绿→黄→红 循环
const int RED_PIN   = 4;     // 红灯
const int GREEN_PIN = 18;    // 绿灯
const int YELLOW_PIN = 22;   // 黄灯

unsigned long prevMs = 0;
const int stepTime = 10;     // 渐变速度

int r = 255, g = 0, y = 0;   // 红、绿、黄 三个亮度
int stage = 0;  // 0:红→绿  1:绿→黄  2:黄→红

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
}

void loop() {
  unsigned long now = millis();
  if (now - prevMs >= stepTime) {
    prevMs = now;
    doGradient();
    showColor();
  }
}

// 渐变逻辑：红 → 绿 → 黄 → 红
void doGradient() {
  if (stage == 0) {       // 红慢慢灭，绿慢慢亮
    r--;
    g++;
    if (r <= 0) stage = 1;
  } 
  else if (stage == 1) {  // 绿慢慢灭，黄慢慢亮
    g--;
    y++;
    if (g <= 0) stage = 2;
  } 
  else if (stage == 2) {  // 黄慢慢灭，红慢慢亮
    y--;
    r++;
    if (y <= 0) stage = 0;
  }

  // 限制亮度 0~255，防止异常
  r = constrain(r, 0, 255);
  g = constrain(g, 0, 255);
  y = constrain(y, 0, 255);
}

// 输出到三个独立LED
void showColor() {
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(YELLOW_PIN, y);
}