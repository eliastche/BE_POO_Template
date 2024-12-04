#include <Arduino.h>
#include <Wire.h>
#include <SHT31.h>
#include <rgb_lcd.h>
#include <ESP8266WiFi.h> //Library for all WiFi related functionalities
#include <WiFiClient.h> //Send requests to web browser
#include <ESP8266WebServer.h> //Handles all HTTP protocols

#include "Application.h"

//Pins
#define buttonPIN 13//D7
#define lightSensorPIN 12//D6

//Screenstates
#define showTemp 0
#define showHum 1
#define showLight 2
#define showClock 3

//Wifi credentials
//Elias's HotSpot
//#define STASSID " Tche "
//#define STAPSK "Elias123"
//Haakon's Wifi
//#define STASSID "devolo-278";
//#define STAPSK "VBQCROOVXZYVUHMR";
//Haakon's HotSpot
//#define STASSID "Halla man";
//#define STAPSK "noe kult";
//Max HotSpot
#define STASSID "A Man"
#define STAPSK "HASNONAME"

//Values for optimal powder conditions
#define minTemp4Powder -15
#define maxTemp4Powder -5
#define minHum4Powder 20
#define maxHum4Powder 60

int buttonState = 0;
int oldButtonState = 0;
int screenState = showTemp;

// Network credentials
const char* ssid     = STASSID;
const char* password = STAPSK;

// Set web server port number to 80
ESP8266WebServer server(80);

// Variable to store the HTTP request
String header;

void handleRoot() {

  String s = MAIN_page;

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
    //Affichage
    

};

class MyScreen : public rgb_lcd{
  private:
    int state;
  
  public:
    void init(){
      //Initializee screen with 16 by 2
      begin(16,2);

      //Set colour
      setRGB(50,100,255);
      
      //Print instructions
      setCursor(0,0);
      print("The");
      setCursor(0,1);
      print("Powder Station");
      delay(2000);
      clear();

      setCursor(0,0);
      print("Press button to");
      setCursor(0,1);
      print("start");
      
      while(buttonState == 0){
        this->state = showTemp;
        buttonState = digitalRead(buttonPIN);
      }
      
      clear();

    }
    //Get values
    int getState(){
      return state;
    }

    //Set values
    void changeState(){
      //Update state
      if(state != showClock) state++; //Move to next
      else state = showTemp; //Reset to temp mode
    }

    //Printing
    
};

MyScreen screen;
MySensor sensor;

void setup() {
  //Initialize button
  pinMode(buttonPIN, INPUT);

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
int temp;
int hum;
int light;
void loop() {
  server.handleClient();

  buttonState = digitalRead(buttonPIN);

  switch (screen.getState()){
        case showTemp:
          //Fetch value
          temp = (int)sensor.getTemperature();

          //Print value
          screen.setCursor(0,0);
          screen.print("Temp:");
          screen.print(temp);

          screen.setCursor(0,1);
          if(temp < minTemp4Powder) screen.print("Too cold!");
          else if(temp > maxTemp4Powder) screen.print("Too warm!");
          else screen.print("Temp good!");
          break;
        case showHum:
          //Fetch value
          hum = (int)sensor.getHumidity();

          //Print value
          screen.setCursor(0,0);
          screen.print("Hum:");
          screen.print(hum);

          screen.setCursor(0,1);
          if(temp < minHum4Powder) screen.print("Too dry!");
          else if(temp > maxHum4Powder) screen.print("Too wet!");
          else screen.print("Humidity good!");

          break;
        case showLight:
          //FetchValue
          light = analogRead(lightSensorPIN);

          //Print value
          screen.setCursor(0,0);
          screen.print("Light:");
          screen.print(light);

          break;
        case showClock:
          //Print value
          screen.setCursor(0,0);
          screen.print("Clock mode");
          screen.setCursor(0,1);
          screen.print("Time is now!");
          break;
      }

  if(oldButtonState != buttonState && buttonState == HIGH){
    screen.changeState();
    screen.clear();
  }
  oldButtonState = buttonState;
}
