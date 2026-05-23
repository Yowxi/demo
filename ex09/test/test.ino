#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "iPhone";
const char* password = "20061003";

const int TOUCH_PIN = T0; 
WebServer server(80);

// 平滑滤波
int raw = 0;
int filtered = 0;

String makePage() {
  return R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>触摸实时面板</title>
  <style>
    body{text-align:center;margin-top:50px;}
    h1{font-size:80px;color:red;}
  </style>
</head>
<body>
  <h2>手靠近 → 数值变小</h2>
  <h1 id="val">--</h1>
  <script>
    setInterval(()=>{
      fetch("/v").then(r=>r.text()).then(x=>{
        document.getElementById("val").innerText=x;
      });
    },100);
  </script>
</body>
</html>
)rawliteral";
}

void handleRoot() {
  server.send(200, "text/html; charset=utf-8", makePage());
}

void handleV() {
  server.send(200, "text/plain", String(filtered));
}

void setup() {
  Serial.begin(115200);

  // 关键：不要 pinMode(TOUCH_PIN, OUTPUT)！
  // 触摸引脚默认就是输入型，设为OUTPUT就废了

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/v", handleV);
  server.begin();
}

void loop() {
  server.handleClient();

  raw = touchRead(TOUCH_PIN);
  // 简单滤波，让变化顺滑
  filtered = filtered * 0.8 + raw * 0.2;

  Serial.print("raw:");
  Serial.print(raw);
  Serial.print("  filt:");
  Serial.println(filtered);

  delay(100);
}