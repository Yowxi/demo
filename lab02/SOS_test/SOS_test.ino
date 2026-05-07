// 定义LED引脚，ESP32通常板载LED连接在GPIO 2
// 实验2 进阶：SOS 求救信号灯（三短 三长 三短）
const int ledPin = 2;
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {

  // S：三次短闪
  for(int i=0; i<3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  delay(500); // 字母间隔

  // O：三次长闪
  for(int i=0; i<3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(600);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  delay(500); // 字母间隔


  // S：三次短闪
  for(int i=0; i<3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  delay(2000); // 一轮结束，长停顿
}