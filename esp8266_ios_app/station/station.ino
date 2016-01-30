/*-----------------------------------------------------------------------
  ACROBOTIC - 11/12/2015
  Author: MakerBro
  Platforms: ESP8266 Development Board (ESP-12E)
  File: firmware.ino
  ------------------------------------------------------------------------
  Description:
  This program connects the ESP9266 module to the web, and starts a simple
  webserver that listens for specific arguments passed by a client to
  control the status of LEDs.
  ------------------------------------------------------------------------
  Please consider buying products from Acrobotic to help fund future
  Open-Source projects like this! We’ll always put our best effort in every
  project, and release all our design files and code for you to use.

  https://acrobotic.com/
  ------------------------------------------------------------------------
  License:
  Released under the Creative Commons Attribution, Share-Alike license.
  Please check LICENSE.txt for more information. All text above must be
  included in any redistribution.
------------------------------------------------------------------------*/
// Include the libraries that we'll be using throughout the code
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Define the ID and password of your Wi-Fi network
const char* ssid = "BEARBEAR";
const char* password = "isachinesebear";

// Instantiate the ESP8266WebServer class, passing the argument 80 for the
// port that the server will be listening.
ESP8266WebServer server(80);

// User-defined function that will be called when a client accesses the root
// directory path of the ESP8266 host
void handleRoot() {
  // Simply sends an 'OK' (200) response to the client, and a plain text
  // string with usage.
  server.send(200, "text/plain", String("Hello from esp8266!"));
}

// In the setup function we initialize the different things
// that will be needed in our program, as well as set up the hardware
void setup(void) {
  // Start the Serial communication for debugging purposes
  Serial.begin(115200);
  //  Initialize the WiFi client and try to connect to our Wi-Fi network
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for a successful connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // For debugging purposes print the network ID and the assigned IP address
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Associate the URLs with the functions that will be handling the requests
  server.on("/", HTTP_GET, handleRoot);

  // Start running the webserver
  server.begin();
  Serial.println("HTTP server started");
}

// The loop function is straight-forward, simply handle any incoming requests to the
// our ESP8266 host!
void loop(void) {
  server.handleClient();
}
