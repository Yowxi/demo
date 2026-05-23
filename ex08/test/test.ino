#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "iPhone";
const char* password = "20061003";

const int LED_PIN   = 2;
const int TOUCH_PIN = 4;

WebServer server(80);

bool isArmed   = false;
bool isAlarming = false;

String makePage() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>安防报警系统</title>
</head>
<body style="font-family:Arial; text-align:center; margin-top:50px;">
  <h1>🚨 物联网安防报警系统</h1>

  <h2>
    状态：
    <b style="color:)rawliteral" + String(isAlarming ? "red" : (isArmed ? "green" : "#666")) + R"rawliteral(;">
      )rawliteral" + String(isAlarming ? "⚠️ 报警中" : (isArmed ? "✅ 已布防" : "🛡️ 已撤防")) + R"rawliteral(
    </b>
  </h2>

  <p>
    <a href="/arm">
      <button style="font-size:22px; padding:10px 30px; border:none; border-radius:8px; background:green; color:white;">
        🛡️ 布防
      </button>
    </a>
    <a href="/disarm">
      <button style="font-size:22px; padding:10px 30px; border:none; border-radius:8px; background:red; color:white; margin-left:10px;">
        🛑 撤防
      </button>
    </a>
  </p>
</body>
</html>
)rawliteral";
  return html;
}

void handleRoot() {
  server.send(200, "text/html; charset=utf-8", makePage());
}

// 布防（修复跳转）
void handleArm() {
  isArmed = true;
  isAlarming = false;
  digitalWrite(LED_PIN, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

// 撤防（修复跳转）
void handleDisarm() {
  isArmed = false;
  isAlarming = false;
  digitalWrite(LED_PIN, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("连接WiFi中");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n连接成功");
  Serial.print("访问地址: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
}

void loop() {
  server.handleClient();

  // 触摸检测
  if (isArmed && !isAlarming) {
    if (touchRead(TOUCH_PIN) < 1000) {
      isAlarming = true;
    }
  }

  // 报警闪烁
  if (isAlarming) {
    digitalWrite(LED_PIN, HIGH);
    delay(80);
    digitalWrite(LED_PIN, LOW);
    delay(80);
  }
}