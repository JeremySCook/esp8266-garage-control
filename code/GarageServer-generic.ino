#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif

const char* ssid = "yourssidhere";
const char* password = "yourpasswordhere";

ESP8266WebServer server(80);

#define relayPin 5

const char *webpage =
#include "webPage.h"
;

void handleRoot() {
  //digitalWrite(LED_BUILTIN, 1);
  server.send(200, "text/html", webpage);
  //digitalWrite(LED_BUILTIN, 0);
}

void handleNotFound() {
  digitalWrite(LED_BUILTIN, 1);
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
  digitalWrite(BUILTIN_LED, 0);
}

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(relayPin, LOW);
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

  if (MDNS.begin("garage")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

   server.on("/door", []() {
    digitalWrite(relayPin, HIGH);
    delay(250);
    digitalWrite(relayPin, LOW);
    delay(50); //may not be needed
    server.send(200, "text/plain", "door");
  });

  server.on("/lightOn", []() {
    digitalWrite(LED_BUILTIN, LOW);
    server.send(200, "text/plain", "lightOn");
  });

  server.on("/lightOff", []() {
    digitalWrite(LED_BUILTIN, HIGH);
    server.send(200, "text/plain", "lightOff");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

}

void loop() {
  server.handleClient();
  MDNS.update();
}
