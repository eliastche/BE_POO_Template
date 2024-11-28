#include <Arduino.h>
#include <Wire.h>
#include <SHT31.h>
#include <rgb_lcd.h>
#include <ESP8266WiFi.h> //Library for all WiFi related functionalities
#include <WiFiClient.h> //Send requests to web browser
#include <ESP8266WebServer.h> //Handles all HTTP protocols

#include "website/index.html"

#define minTemp4Powder -15
#define maxTemp4Powder -5
#define minHum4Powder 20
#define maxHum4powder 60

constant int buttonPin = 13;
int buttonState = 0;

// Network credentials
const char* ssid     = "devolo-278";
const char* password = "VBQCROOVXZYVUHMR";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
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

class MySensor : public SHT31{
  public:
    void showConditons(rgb_lcd screen){
      //Fetch values
      int temp = (int)getTemperature();
      int hum = (int)getHumidity();

      //Print values
      screen.setCursor(0,0);
      screen.print("Temp:");
      screen.print(temp);

      screen.setCursor(0,1);
      screen.print("Hum:");
      screen.print(hum);
    }

};

class MyScreen : public rgb_lcd{
  public:
    void init(){
      begin(16,2);

      setRGB(50,100,255);
      
      setCursor(0,0);
      print("The");
      setCursor(0,1);
      print("PowderDetector");
      delay(2000);
      clear();

      setCursor(0,0);
      print("Press button to");
      setCursor(0,1);
      print("start");
      
      while(read())

    }
};

MyScreen screen;
MySensor sensor;

void setup() {
  //Initialize button
  pinMode(buttonPin, INPUT)

  //Initialze sensor and start screens
  sensor.begin();
  screen.init();

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
}

void loop() {
  sensor.showConditons(screen);

  WiFiClient client = server.available();   // Listen for incoming clients

  server.handleClient();
}
