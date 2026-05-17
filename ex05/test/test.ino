// ex05 触摸三档调速呼吸灯
#define TOUCH_PIN 4
#define LED_PIN 2
#define THRESHOLD 1000

int brightness = 0;
int fadeDir = 1;
int gear = 0;

// 三档步长
int speed[3] = {1, 8, 30}; 

bool locked = false;

void touchHandle() {
  if (!locked) {
    gear = (gear + 1) % 3;
    locked = true;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  touchAttachInterrupt(TOUCH_PIN, touchHandle, THRESHOLD);
}

void loop() {
  brightness += fadeDir * speed[gear];
  if (brightness >= 255 || brightness <= 0) {
    fadeDir = -fadeDir;
  }
  analogWrite(LED_PIN, brightness);

  int val = touchRead(TOUCH_PIN);
  if (val > THRESHOLD + 10) {
    locked = false;
  }

  delay(10);
}