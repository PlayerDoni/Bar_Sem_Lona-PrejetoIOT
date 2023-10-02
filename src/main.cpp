#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
const char* ssid = "PROF.RAFAEL";
const char* password = "";
ESP8266WebServer server(80);
const int output5 = 5;//D1
IPAddress local_IP(192,168,1,85); //Troque o IP
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
void handleRoot();
void handleOn();
void handleOff();
void handleRoot() {
String html = "<!DOCTYPE html><html>";
html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
html += "<link rel=\"icon\" href=\"data:,\">";
html += "<style>html, body { height: 100%; margin: 0;}";
html += "body { display: flex; justify-content: center; align-items: center;}";
html += ".toggle-container { position: relative; display: inline-block;}";
html += ".toggleButton { width: 100px; height: 60px; background-color: gray; border: none;";
html += "border-radius: 30px; cursor: pointer; position: relative;}";
html += ".slider { position: absolute; top: 0; left: 0; width: 50%; height: 100%; background-color: #4CAF50;";
html += "border-radius: 30px; transition: 0.4s;}";
html += ".toggleButton.off .slider { left: 0; }";
html += ".toggleButton.on .slider { left: 50%; }";
html += "</style></head>";
html += "<body>";
html += "<div class=\"toggle-container\">";
html += "<div class=\"toggleButton off\" onclick=\"toggleLED(this)\">";
html += "<div class=\"slider\"></div>";
html += "</div>";
html += "</div>";
html += "<script>";
html += "function toggleLED(button) {";
html += " button.classList.toggle('on');";
html += " button.classList.toggle('off');";
html += " if (button.classList.contains('on')) {";
html += " var xhr = new XMLHttpRequest();";
html += " xhr.open('GET', '/5/on', true);";
html += " xhr.send();";
html += " } else {";
html += " var xhr = new XMLHttpRequest();";
html += " xhr.open('GET', '/5/off', true);";
html += " xhr.send();";
html += " }";
html += "}";
html += "</script>";
html += "</body></html>";



server.send(200, "text/html", html);
}
void handleOn() {
digitalWrite(output5, HIGH);
server.send(200, "text/plain", "LED Ligado!");
}
void handleOff() {
digitalWrite(output5, LOW);
server.send(200, "text/plain", "LED Desligado!");
}
void setup() {
Serial.begin(9600);
pinMode(output5, OUTPUT);
digitalWrite(output5, LOW);
if (!WiFi.config(local_IP, gateway, subnet)) {
Serial.println("STA Failed to configure");
}
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected.");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
server.on("/", HTTP_GET, handleRoot);
server.on("/5/on", HTTP_GET, handleOn);
server.on("/5/off", HTTP_GET, handleOff);
server.begin();
}
void loop(){
server.handleClient();
}
