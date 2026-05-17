#define TOUCH_PIN 4
#define LED_PIN 2
#define THRESHOLD 1000    

bool ledState = false;
bool isTriggered = false; // 防止重复触发（关键）

// 中断服务函数
void gotTouch() {
  // 只在未触发过时执行 → 保证只翻转一次
  if (!isTriggered) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    isTriggered = true; // 锁定，防止连续触发
  }
}

void setup() {
  Serial.begin(11500);
  delay(1000);
  pinMode(LED_PIN, OUTPUT);
  
  // 绑定触摸中断
  touchAttachInterrupt(TOUCH_PIN, gotTouch, THRESHOLD);
}

void loop() {
  // 松手后重置触发锁 → 才能进行下一次触摸
  int val = touchRead(TOUCH_PIN);
  if (val > THRESHOLD + 10) { 
    isTriggered = false;
  }

  Serial.print("触摸值：");
  Serial.println(val);
  delay(50);
}