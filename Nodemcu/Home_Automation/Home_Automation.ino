
#include <ESP8266WiFi.h>
#include<string.h>
#include "temp.h"


const uint8_t scl=5;
const uint8_t sda=4;
#include <LiquidCrystal.h>


const int rs = 0, en = 2, d4 = 14, d5 = 12, d6 = 13, d7 = 15;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const char* ssid = "Find Me"; // SSID i.e. Service Set Identifier is the name of your WIFI
const char* password = "111111111"; // Your Wifi password, in case you have open network comment the whole statement.
  
int room1=16;
int room2=10;
float t;

WiFiServer server(80); // Creates a server that listens for incoming connections on the specified port, here in this case port is 80.

 double Ax, Ay, Az, T, Gx, Gy, Gz;
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(room1, OUTPUT);
  digitalWrite(room1, LOW);
  pinMode(room2, OUTPUT);
  digitalWrite(room2, LOW);
 
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
  Wire.begin(sda,scl);
MPU6050_Init();
  lcd.begin(16, 2);
  lcd.noDisplay();
 
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
 int value1=LOW;
 int var_temp=LOW;
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  
  client.flush();
  Serial.println(request);
  
  if(request.indexOf("Submit") != -1){
  if ((request.indexOf("Prakash") != -1) && (request.indexOf("Saini") != -1))  {
    value = HIGH;
    lcd.display();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome");
  }
  if ((request.indexOf("Prakash") == -1)|| (request.indexOf("Saini") == -1) ) {
    
     value1=HIGH;
     lcd.display();
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Access Denied");
  
  }
  }
  
  if (request.indexOf("tempe") != -1){
     Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);
  
     t = ((float)T/340.00)+36.53;
     var_temp=HIGH;
    }
 if(request.indexOf("LED1=ON") !=-1){
  digitalWrite(room1,HIGH);
  }
  
 if(request.indexOf("LED1=OFF") !=-1){
  digitalWrite(room1,LOW);
  }
  
 if(request.indexOf("LED2=ON") !=-1){
  digitalWrite(room2,HIGH);
  }
  
 if(request.indexOf("LED2=ON") !=-1){
  digitalWrite(room2,LOW);
  }

 Serial.println(request.indexOf("GET"));
  // Match the request
 Serial.println(request.indexOf("HTTP"));
  // Return the response
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<body style=\"background-color:silver\"><center><b><h1 style=\"color:blueviolet\">IoT</h1></b></center><br>");
            client.println("<form action='' method=\'get\'>");
            // Display current state, and ON/OFF buttons for GsaPIO 26  
            client.println(" Name: <input type=\"text\" name=\"fname\"><br>");
           client.println(" Password: <input type=\"password\" name=\"pass\"><br>");
                   
            client.println("<input type=\"submit\" name=\"submit\" value=\'Submit\'><br>");
            if(value == HIGH){
              client.println("       You are in ");
              value=LOW;
              }
              
              
                else if(value1==HIGH){
                client.println("    Failed!,Try again  ");
                value1=LOW;
                }
               else {
                client.println("   Please Login ");
                }
            client.println("</form>");
            client.println("<br><br>");
            
            client.println("<a href=\"tempe\"><button style=\"margin-left:5px\">Click Me</button></a>");
            client.println("<b>Room Temperature : </b>");
           if(var_temp==HIGH){
            client.println(t);
            client.println("*C");
            }
            
            client.println("<br>");
            client.println("<h3>Room : 1</h3><a href=\"LED1=ON\"><button style=\"margin-left:5px\">Turn On </button></a>");
            client.println("<a href=\"LED1=OFF\"><button style=\"margin-left:5px\">Turn Off </button></a><br><br>");
            client.println("<h3>Room : 2</h3><a href=\"LED2=ON\"><button style=\"margin-left:5px\">Turn On </button></a>");
            client.println("<a href=\"LED2=OFF\"><button style=\"margin-left:5px\">Turn Off </button></a><br><br>");
            client.println("<h3>Room : 3</h3><a href=\"LED3=ON\"><button style=\"margin-left:5px\">Turn On </button></a>");
            client.println("<a href=\"LED3=OFF\"><button style=\"margin-left:5px\">Turn Off </button></a><br><br>");
            client.println("</body></html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 
