#include <Arduino.h>
#include <Wire.h>
#include <SHT31.h>
#include <rgb_lcd.h>
#include <ESP8266WiFi.h> //Library for all WiFi related functionalities
#include <WiFiClient.h> //Send requests to web browser
#include <ESP8266WebServer.h> //Handles all HTTP protocols

#include "Application.h"

//Pins
#define BUTTONPIN 13// sur la carte: D7
#define LIGHTSENSORPIN 12// sur la carte : D6

//Wifi credentials
//Elias's HotSpot
// #define STASSID "Tche"
// #define STAPSK "Elias123"
//Haakon's Wifi
//#define STASSID "devolo-278";
//#define STAPSK "VBQCROOVXZYVUHMR";
//Haakon's HotSpot
#define STASSID "Halla man";
#define STAPSK "noe kult";
//Max HotSpot
// #define STASSID "A Man"
// #define STAPSK "HASNONAME"
//Marthe HotSpot
// #define STASSID "iPhone de Marthe C"
// #define STAPSK "marthe31"

//Values for optimal powder conditions
#define minTemp4Powder -15
#define maxTemp4Powder -5
#define minHum4Powder 20
#define maxHum4Powder 60

// Network credentials
const char* ssid     = STASSID;
const char* password = STAPSK;

// Set web server port number to 80
ESP8266WebServer server(80);

// Variable to store the HTTP request
String header;

//Initialiser notre powderStation
PowderStation thisStation;// = new PowderStation();

void handleRoot() {

  String s = MAIN_page;

  // s.replace("{{TEMP}}", String(thisStation.readTemp()));
  // s.replace("{{LIGHT}}", String(thisStation.readLight()));
  // s.replace("{{HUM}}", String(thisStation.readHum()));

  server.send(200, "text/html", s); //Send web page
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

  server.begin();                  //Start server
  Serial.println("HTTP server started");

  //clear screen
  thisStation.clearScreen();

  //Start the station
  thisStation.start();
}
int temp;
int hum;
int light;
void loop() {
  server.handleClient();

  // Afficher les condtions 
  thisStation.showConditions();

  //Mettre à jour le bouton
  thisStation.button.updateState(digitalRead(BUTTONPIN));

  //Mettre à jour l'état de la station
  if(thisStation.button.getOldState() != thisStation.button.getState() && thisStation.button.getState() == HIGH){
    thisStation.changeState();
  }

  //Mettre à jour le bouton
  thisStation.button.updateOldState();
}
