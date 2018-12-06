#include <ESP8266WiFi.h>

#include <WiFiClient.h>

#include <ESP8266WebServer.h>

const char *ssid = "test";

const char *password = "password";

WiFiServer server(80);



void setup() {

delay(1000);

Serial.begin(115200);

Serial.println();

Serial.print("Configuring access point...");

WiFi.softAP(ssid, password);

IPAddress myIP = WiFi.softAPIP();

Serial.print("AP IP address: ");

Serial.println(myIP);


server.begin();

Serial.println("HTTP server started");

}

void loop() {


WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

 
 
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  
  Serial.println(request);
  
  client.flush();

 int len;
 Serial.println(request.indexOf("GET"));
  // Match the request
 Serial.println(request.indexOf("HTTP"));
  int value = LOW;

  len = request.length();
  if((request.indexOf("favicon")==-1)  && (request.indexOf("GET")>=0)){
    Serial.println(request.substring(4,len-6));
    
    }
  
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body style=\"background-color:silver\"><center><b><h1 style=\"color:blueviolet\">IoT</h1></b></center><br>");
            client.println("<form action=\"http://192.168.4.1\" method=\'get\'>");
            // Display current state, and ON/OFF buttons for GsaPIO 26  
            client.println(" Enter Text: <input type=\"text\" name=\"fname\"><br>");
            // If the output26State is off, it displays the ON button       
            client.println("<input type=\"submit\" value=\'Submit\'><br>");
            client.println("</form>");
            client.println("</body></html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
