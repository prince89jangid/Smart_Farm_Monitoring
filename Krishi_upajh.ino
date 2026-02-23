#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

/* ---------- First Page ---------- */
void page1() {
  
  String html = "<html><body>"
                "<h2>Hello</h2>"
                "<a href='/bye'>Go to Second Page</a>"
                "</body></html>";

  server.send(200, "text/html", html);
}

/* ---------- Second Page ---------- */
void page2() {
  String html = "<html><body>"
                "<h2>Bye</h2>"
                "<a href='/'>Back to First Page</a>"
                "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(9600);

  WiFi.softAP("ESP_AP", "12345678");   // AP mode
  Serial.println(WiFi.softAPIP());     // usually 192.168.4.1

  server.on("/", page1);      // First page
  server.on("/bye", page2);   // Second page

  server.begin();
}

void loop() {
  server.handleClient();
}