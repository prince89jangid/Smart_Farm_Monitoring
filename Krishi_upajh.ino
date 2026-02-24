#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "S23";
const char* password = "passward";

ESP8266WebServer server(80);

#define BUTTON D3   // GPIO0

// ===== HTML page =====
String webpage = R"====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>IOT</title>
<style>
h1{text-align:center;}
.display{background:orange;padding:15px;border-radius:10px;width:120px;margin:auto;text-align:center;font-size:30px;}
</style>
</head>

<body>
<h1>Prince IOT</h1>
<div class="display" id="val">1</div>

<script>
setInterval(function(){
  fetch("/button").then(r => r.text()).then(data=>{
    document.getElementById("val").innerHTML = data;
  });
},30);
</script>

</body>
</html>
)====";

// ===== handlers =====
void handleRoot() {
  server.send(200, "text/html", webpage);
}

void handleButton() {
  int state = digitalRead(BUTTON);
  if(state == LOW) server.send(200, "text/plain", "0");
  else server.send(200, "text/plain", "1");
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/button", handleButton);

  server.begin();
}

void loop() {
  server.handleClient();
}
