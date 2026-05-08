// 作业3：millis() 实现标准 SOS
const int ledPin = 2;
unsigned long prevMs = 0;

// 时间（毫秒）
const int SHORT = 200;//短亮
const int LONG  = 1000;//长亮
const int GAP   = 250;//闪与闪之间间隔
const int LETTER_GAP = 700;//字母之间间隔
const int END_PAUSE = 5000;//一段过后间隔

int step = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long now = millis();
  // 三短闪前S
  if (step >= 0 && step <= 2) {
    if (now - prevMs >= SHORT) {
      digitalWrite(ledPin, HIGH);
      if (now - prevMs >= SHORT + GAP) {
        prevMs = now;
        digitalWrite(ledPin, LOW);
        step++;
      }
    }
  }

  // 字母间隔
  else if (step == 3) {
    if (now - prevMs >= LETTER_GAP) {
      prevMs = now;
      step++;
    }
  }

  // 三长闪：O
  else if (step >= 4 && step <= 6) {
    if (now - prevMs >= LONG) {
      digitalWrite(ledPin, HIGH);
      if (now - prevMs >= LONG + GAP) {
        prevMs = now;
        digitalWrite(ledPin, LOW);
        step++;
      }
    }
  }

  // 字母间隔
  else if (step == 7) {
    if (now - prevMs >= LETTER_GAP) {
      prevMs = now;
      step++;
    }
  }

  // 三短闪：后S
  else if (step >= 8 && step <= 10) {
    if (now - prevMs >= SHORT) {
      digitalWrite(ledPin, HIGH);
      if (now - prevMs >= SHORT + GAP) {
        prevMs = now;
        digitalWrite(ledPin, LOW);
        step++;
      }
    }
  }

  // 结束停顿
  else if (step == 11) {
    digitalWrite(ledPin, LOW);
    if (now - prevMs >= END_PAUSE) {
      prevMs = now;
      step = 0;
    }
  }
}