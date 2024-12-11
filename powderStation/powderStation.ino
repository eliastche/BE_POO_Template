#include <Arduino.h>
#include <Wire.h>
#include <SHT31.h>
#include <rgb_lcd.h>
#include <ESP8266WiFi.h> //Library for all WiFi related functionalities
#include <WiFiClient.h> //Send requests to web browser
#include <ESP8266WebServer.h> //Handles all HTTP protocols

// Header to including all necessary functions
#include "Application.h"

//Pins
#define BUTTONPIN 13// sur la carte: D7
#define LIGHTSENSORPIN 12// sur la carte : D6

//Wifi credentials used during testing
//Elias's HotSpot
// #define STASSID "Tche"
// #define STAPSK "Elias123"
//Haakon's Wifi
// #define STASSID "devolo-278";
// #define STAPSK "VBQCROOVXZYVUHMR";
//Haakon's HotSpot
#define STASSID "Halla man";
#define STAPSK "noe kult";
//Max HotSpot
// #define STASSID "A Man"
// #define STAPSK "HASNONAME"
//Marthe HotSpot
// #define STASSID "iPhone de Marthe C"
// #define STAPSK "marthe31"

// Network credentials
const char* ssid     = STASSID;
const char* password = STAPSK;

// Set web server port number to 80
ESP8266WebServer server(80);

// Variable to store the HTTP request
String header;

//Initialiser notre powderStation
PowderStation thisStation;

void handleRoot() {
  String s = MAIN_page;

  server.send(200, "text/html", s); //Send web page
}

// Prepare a JSON response with sensor data
void handleSensorData() {
    String json = "{";
    json += "\"temp\":" + String(thisStation.readTemp()) + ",";
    json += "\"light\":" + String(thisStation.readLight()) + ",";
    json += "\"hum\":" + String(thisStation.readHum());
    json += "}";

    // Send the JSON response
    server.send(200, "application/json", json);
}

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  // Connect to network
  thisStation.waitForNetwork();

  Serial.begin(9600);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //Connect to WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  server.on("/", handleRoot);      //Which routine to handle at root location
  server.on("/data", handleSensorData); // Serve sensor data as JSON

  server.begin();                  //Start server
  Serial.println("HTTP server started");

  //clear screen
  thisStation.clearScreen();

  //Showing start menu of the station
  thisStation.start();
}

void loop() {
  server.handleClient();

  // Print weather conditions
  thisStation.showConditions();

  // Update button
  thisStation.button.updateState(digitalRead(BUTTONPIN));

  // Check if button is pressed(check if changes and new value is '1'), then changes the state of the stations
  if(thisStation.button.getOldState() != thisStation.button.getState() && thisStation.button.getState() == HIGH){
    thisStation.changeState();
  }

  // Update the 'old' button state
  thisStation.button.updateOldState();
}
