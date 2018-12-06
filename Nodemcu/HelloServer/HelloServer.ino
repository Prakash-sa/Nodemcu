#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "FindMe";
const char* password = "111111111";

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  int sec = millis() / 1000;
   int min = sec / 60;
   int hr = min / 60;
        char temp[420];
   snprintf ( temp, 400,

"<html>\
  <head>\
  <meta charset='utf-8'>\
    <title>ESP8266 Demo</title>\
    <meta name='viewport' content='width=device-width,initial-scale=1'>\
  </head>\
  <body >\
    <center>\
        <b><h1 style='color:blueviolet'>IoT</h1></b>\
   </center>\
    <br>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <br>\
<form action='' method='get'>\
Username: <input type='text' name='fname'><br />\
Password: <input type='password' name='pass'><br />\
Submit: <input type='submit' value='Submit'><br />\
</form>\
</body>\
</html>",

      hr, min % 60, sec % 60
   );
  server.send(200, "text/html", temp);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
   WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  server.handleClient();
 
 
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  
  Serial.println(request);
}
