// ex06 双通道PWM反相渐变警车灯
#define LED_A 4
#define LED_B 18

// 两路独立亮度变量
int valA = 0;
int valB = 255;
int step = 2;

void setup()
{
  pinMode(LED_A,OUTPUT);
  pinMode(LED_B,OUTPUT);
}

void loop()
{
    valA += step;
    valB = 255 - valA;

    // 到达极值翻转变化方向
    if(valA >= 255 || valA <= 0)
    {
        step = -step;
    }
    // 双通道独立PWM输出
    analogWrite(LED_A, valA);
    analogWrite(LED_B, valB);

    delay(12);
}