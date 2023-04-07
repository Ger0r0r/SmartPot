#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
/* TODO
 *  Button - switcher +/-
 *  Ini state fix +
 *  Delete second button +
 *  Think about get inf from ESP +
 */


/* Установить свой SSID и пароль */
const char* ssid = "Room_222";  // SSID 
const char* password = "DEADFA11";  //пароль

ESP8266WebServer server(80);

uint8_t LEDpin = D7;
bool LEDstatus = LOW;

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(LEDpin, OUTPUT);
  Serial.println("Connecting to ");
  Serial.println(ssid);
    // подключаемся к локальной Wi-Fi сети
  WiFi.begin(ssid, password);
  // проверка подключения Wi-Fi к сети
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  server.on("/", handle_OnConnect);
  server.on("/ledon", handle_ledon);
  server.on("/ledoff", handle_ledoff);
  server.on("/test", test);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  
  if(LEDstatus) {
    digitalWrite(LEDpin, HIGH);
  } else {
    digitalWrite(LEDpin, LOW);
  }
   
}

void handle_OnConnect() {
  if(LEDstatus){
    Serial.println("GPIO7 Status: OFF");
  } else {
    Serial.println("GPIO7 Status: On");
  }
  server.send(200, "text/html", SendHTML(LEDstatus)); 
}

void handle_ledon() {
  LEDstatus = HIGH;
  Serial.println("GPIO7 Status: ON");
//  server.sendHeader("Location","/"); 
  server.send(200, "text/html", SendHTML(true)); 
}

void handle_ledoff() {
  LEDstatus = LOW;
  Serial.println("GPIO7 Status: OFF");
//  server.sendHeader("Location","/");
  server.send(200, "text/html", SendHTML(false)); 

}

void test(){
  server.sendHeader("Location","/");
  server.send(303); 
  Serial.println("I am in test!");
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t ledstat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
    ptr +="<h3>Using Station(STA) Mode</h3>\n";
  
  if(ledstat) {
    ptr +="<p>LED Status: ON</p> <a class=\"button button-off\" href=\"/ledoff\">OFF</a>\n";
  }
  else {
    ptr +="<p>LED Status: OFF</p><a class=\"button button-on\" href=\"/ledon\">ON</a>\n";
  }
  
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
