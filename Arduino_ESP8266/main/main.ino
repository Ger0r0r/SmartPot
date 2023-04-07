#include <ESP8266WiFi.h>
#include <string.h>

const char* ssid = "Room_222";
const char* password = "DEADFA11";

WiFiServer wifiServer(80);

void setup() {
  Serial.begin(115200);
  delay(1000);
  server_init(ssid, password);
}

void loop() {
  work(wifiServer);
}