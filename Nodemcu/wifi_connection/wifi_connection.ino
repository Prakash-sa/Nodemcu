#include<ESP8266EiFi.h>

const *char ssid="Find Me";
const *char password = "11111111";

int ledepin =13;
WiFiServer server(80);

void setup(){
    Serial.begin(115200);
    delay(10);

    pinMode(led,OUTPUT);

    Serial.println();
    Serial.println();
    Serial.println("Connecting to the server");


    WiFi.begin(ssid,password);
    while(WiFiStatus() != WL_CONNECTED){
        delay(20);
        Serial.print(".");
    }

    Serial.println("connet to the http.//");
    Serial.print(WiFi.localIP());

}
void loop(){

WiFiClient client = server.available();
if(!client){
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


    
}
