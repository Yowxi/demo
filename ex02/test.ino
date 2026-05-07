// 作业2：millis() 实现 1Hz LED 闪烁
// 功能：1秒亮、1秒灭，不使用delay()

const int ledPin = 2;           // 板载LED引脚
unsigned long lastMillis = 0;   // 记录上一次翻转时间
const long interval = 1000;     // 1000ms = 1秒 → 1Hz

void setup() {
  pinMode(ledPin, OUTPUT);      // 设置LED为输出模式
  Serial.begin(115200);         // 初始化串口（方便调试）
}

void loop() {
  // 获取当前系统时间（毫秒）
  unsigned long currentMillis = millis();

  // 判断：时间到了就翻转LED
  if (currentMillis - lastMillis >= interval) {
    lastMillis = currentMillis;       // 更新时间
    
    int state = digitalRead(ledPin);  // 读取当前状态
    digitalWrite(ledPin, !state);     // 翻转亮/灭
    
    Serial.println("LED 状态翻转");   // 串口输出（可选）
  }
}