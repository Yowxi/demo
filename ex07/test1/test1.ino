#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "iPhone";
const char* password = "20061003";

const int LED_PIN = 2;  // 单灯 D2

WebServer server(80);

int brightness = 0;

// 网页：滑动条实时调光（带图标、美观版）
String makePage() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>LED 无极调光器</title>
</head>
<body style="font-family:Arial; text-align:center; margin-top:50px;">
  <h1>💡 LED 无极调光控制器</h1>

  <h3>🔦 灯珠亮度调节</h3>
  <input type="range" min="0" max="255" value=")rawliteral" + String(brightness) + R"rawliteral(" style="width:350px; height:20px;" oninput="updateLight(this.value)">
  <p>当前亮度值：<span id="lightVal" style="font-size:22px; color:red;">)rawliteral" + String(brightness) + R"rawliteral(</span></p>

  <script>
    function updateLight(val) {
      document.getElementById("lightVal").innerText = val;
      fetch("/setLight?val=" + val);
    }
  </script>
</body>
</html>
)rawliteral";
  return html;
}

void handleRoot() {
  server.send(200, "text/html; charset=utf-8", makePage());
}

// 实时设置亮度
void handleSetLight() {
  if (server.hasArg("val")) {
    brightness = server.arg("val").toInt();
    if (brightness < 0) brightness = 0;
    if (brightness > 255) brightness = 255;
    analogWrite(LED_PIN, brightness);
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, 0);

  WiFi.begin(ssid, password);
  Serial.print("连接WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n连接成功");
  Serial.print("访问地址: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/setLight", handleSetLight);

  server.begin();
}

void loop() {
  server.handleClient();
}