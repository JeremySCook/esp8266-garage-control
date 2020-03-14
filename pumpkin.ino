//By Jeremy S. Cook - controls a few LEDs meant for a Pumpkin
//
//based on relay demo by Innovative Tom: 
//https://github.com/Innovativetom/InnovativeTomDemo-Wemos-Relay/blob/master/InnovativeTomDemo.txt
//
//That code in turn was resued from the example on the ESP8266 Learning Webpage below: 
//http://www.esp8266learning.com/wemos-webserver-example.php
//Code is here for reference, and was originally posted here: https://www.instructables.com/id/Smartphone-Controlled-Pumpkin/
//will be modified for garage remote control.

//CODE START 

#include <ESP8266WiFi.h>

// Below you will need to use your own WIFI information.

const char* ssid = "XXXYYY"; //WIFI Name, WeMo will only connect to a 2.4GHz network.
const char* password = "ABC123"; //WIFI Password

//defining the pins and setting up the "server"3

int Light1 = D1; // System uses pin 1 for first LED
int Light2 = D2; // System uses pin 2 for second LED

WiFiServer server(80);
IPAddress ip(10, 0, 0, 99); // where xx is the desired IP Address
IPAddress gateway(10, 0, 0, 1); // set gateway to match your network
IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network


// void setup is where we initialize variables, pin modes, start using libraries, etc. 
//The setup function will only run once, after each powerup or reset of the wemos board.

void setup() {
  Serial.begin(9600);
  delay(10);
 

  pinMode(Light1, OUTPUT);
  pinMode(Light2, OUTPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  
  digitalWrite(Light1, LOW);
  digitalWrite(Light2, LOW);
  digitalWrite(BUILTIN_LED, HIGH); //note that BUILTIN_LED is output low
 
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
  
  // Connect to WiFi network
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  //Trying to connect it will display dots
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
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}

//void loop is where you put all your code. it is a funtion that returns nothing and will repeat over and over again

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
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  //Match the request, checking to see what the currect state is
  int value = LOW;
  
  if (request.indexOf("/RTEYE=ON") != -1) {
    digitalWrite(Light1, HIGH);
  } 
  if (request.indexOf("/RTEYE=OFF") != -1){
    digitalWrite(Light1, LOW);
  }
  if (request.indexOf("/LTEYE=ON") != -1) {
    digitalWrite(Light2, HIGH);
  }
  if (request.indexOf("/LTEYE=OFF") != -1){
    digitalWrite(Light2, LOW);
  }
  if (request.indexOf("/MOUTH=ON") != -1) {
    digitalWrite(BUILTIN_LED, LOW);
  }
  if (request.indexOf("/MOUTH=OFF") != -1){
    digitalWrite(BUILTIN_LED, HIGH);
  }
  
  //Build the html page
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.println("<a href=\"/RTEYE=ON\"><button><font size=7>Click here to Turn ON RT EYE<br><br></button></a> <br><br>");
  client.println("<a href=\"/RTEYE=OFF\"><button><font size=7>Click here to turn OFF RT EYE.<br><br></button></a><br><br>");
  client.println("<a href=\"/LTEYE=ON\"><button><font size=7>Click here to Turn ON LT EYE.<br><br></button></a><br><br>");
  client.println("<a href=\"/LTEYE=OFF\"><button><font size=7>Click here to Turn OFF LT EYE.<br><br></button></a><br><br>");
  client.println("<a href=\"/MOUTH=ON\"><button><font size=7>Click here to Turn ON MOUTH.<br><br></button></a><br><br>");
  client.println("<a href=\"/MOUTH=OFF\"><button><font size=7>Click here to Turn OFF MOUTH.<br><br></button></a><br><br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}//END

//Original code by 
