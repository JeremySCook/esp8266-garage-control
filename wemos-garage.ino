//This example will use a static IP to control the switching of a relay. Over LAN using a web browser. 
//A lot of this code have been resued from the example on the ESP8266 Learning Webpage below. 
//http://www.esp8266learning.com/wemos-webserver-example.php
//Modified by Jeremy S. Cook 3/18/2020 for garage remote control
//CODE START 

#include <ESP8266WiFi.h>

// Below you will need to use your own WIFI informaiton.

const char* ssid = "BHNTG1682GBD42"; //WIFI Name, WeMo will only connect to a 2.4GHz network.
const char* password = "a826c81a"; //WIFI Password

//defining the pins and setting up the "server"

int relayControl = 5; // System uses pin 2 for second LED

WiFiServer server(80);
IPAddress ip(192, 168, 0, 50); // where xx is the desired IP Address
IPAddress gateway(192, 168, 0, 1); // set gateway to match your network
IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network


// void setup is where we initialize variables, pin modes, start using libraries, etc. 
//The setup function will only run once, after each powerup or reset of the wemos board.

void setup() {
  Serial.begin(9600);
  delay(10);
 
  pinMode(relayControl, OUTPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  
  digitalWrite(relayControl, LOW);
  digitalWrite(BUILTIN_LED, HIGH);
 
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

  //cycle relay/door
  
  if (request.indexOf("/DOOR=ON") != -1) {
    digitalWrite(relayControl, HIGH);
    delay(500);
    digitalWrite(relayControl, LOW);
  } 
  if (request.indexOf("/LED=ON") != -1){
    digitalWrite(BUILTIN_LED, LOW);
  }
  if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(BUILTIN_LED, HIGH);
  }

  
  //Build the html page
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<div align=\"center\">");
  client.println("<br><br><br><br><br><br><br>");

  client.println("<a href=\"/DOOR=ON\"><button><font size=12>CYCLE DOOR</button></a> <br><br>");
  client.println("<a href=\"/LED=ON\"><button><font size=12>LED ON</button></a><br><br>");
  client.println("<a href=\"/LED=OFF\"><button><font size=12>LED OFF</button></a><br><br>");

  client.println("</div>");
  
  client.println("</html>");
 
  delay(1000); //increased delay, as device was hanging after a few minutes at 1ms
  Serial.println("Client disconnected");
  Serial.println("");
 
}//END
