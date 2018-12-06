//Visit www.roboshala.com for more details on NodeMCU and other projects.

#include <ESP8266WiFi.h>
#include<string.h>

const char* ssid = "Find Me"; // SSID i.e. Service Set Identifier is the name of your WIFI
const char* password = "111111111"; // Your Wifi password, in case you have open network comment the whole statement.
 
int ledPin = 14; // GPIO13 or for NodeMCU you can directly write D7 
WiFiServer server(80); // Creates a server that listens for incoming connections on the specified port, here in this case port is 80.
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); //Gets the WiFi shield's IP address and Print the IP address of serial monitor
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

 
 
 int value = LOW;
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  
  Serial.println(request);
  if ((request.indexOf("Prakash") != -1) && (request.indexOf("Saini") != -1))  {
    value = HIGH;
    digitalWrite(ledPin,HIGH);
  }
  
  client.flush();

  // Return the response
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<body style=\"background-color:silver\"><center><b><h1 style=\"color:blueviolet\">IoT</h1></b></center><br>");
            client.println("<form action='' method=\'get\'>");
            // Display current state, and ON/OFF buttons for GsaPIO 26  
            client.println(" Name: <input type=\"text\" name=\"fname\"><br>");
           client.println(" Password: <input type=\"password\" name=\"pass\"><br>");
                   
            client.println("<input type=\"submit\" name = \"submit\" value=\'Submit\'><br>");
            if(value == HIGH){
              client.println("You are in");
              }
              else
              {
                client.println("Failed!,Try again");
               }
            client.println("</form>");
            client.println("</body></html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 
