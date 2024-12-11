/*********************************************************************
 * @file  Appication.h
 * @author Haakon Bogen & Elias Tche
 * @brief Header for the weatherstation program
 *********************************************************************/
#ifndef APPLICATION_H_
#define APPLICATION_H_

//Include necessary libraires for external sensor/ screens
#include <Arduino.h>
#include <Wire.h>
#include <SHT31.h>
#include <rgb_lcd.h>

// Include libraries for other functionalities
#include <String>
#include <ctime>

//Colours
#define weatherRed 75
#define weatherGreen 200
#define weatherBlue 200

#define powderRed 50
#define powderGreen 100
#define powderBlue 255

// Define constants for optimal weather conditons
#define MIN_TEMP_POWDER -15
#define MAX_TEMP_POWDER -5
#define MIN_HUM_POWDER 20
#define MAX_HUM_POWDER 60

//States for display of informations in the weather station
#define SHOWTEMP 0
#define SHOWHUM 1
#define SHOWLIGHT 2
#define SHOWCLOCK 3

typedef struct treshold{
  int min; 
  int max;
} limit;

/**
  * @class Button
  * @brief Button making it possible to change between what the screen shows 
*/

class Button{
  public:
    //Methods

    //Constructors
    Button(void);
    Button(int pin);
    
    //Get attributes (Getters)
    int getState(void);
    int getOldState(void);
    int getPin(void);

    //Set attributes (Setters)
    void changePin(int pin);
    void updateState(int state);
    void updateOldState(void);

  private:
    //Attributes
    int state;
    int pin;
    int oldState;
};

/**
  * @class WeatherStation
  * @brief Overclass containing methods to show weatherconditions and local time 
*/

class WeatherStation{
  public:
    //Public attributes
    Button button;

    WeatherStation(void);
    WeatherStation(int lightPin, Button butt, String location);

    //Update attributes
    void changeState(void);
    void updateConditions(void);

    //Fetch attributes
    int readLight(void);
    int readTemp(void);
    int readHum(void);
    String readTime(void);

    //Set attributs
    void setRGB(int red, int green, int blue);

    //Other methods
    void showConditions(void);
    void start(void);
    void waitForNetwork(void);
    void clearScreen(void);
  protected:
    //Attributes
    rgb_lcd screen;
    SHT31 tempHumSensor;
    int state;
    int lightSensorPin;
    String location;
    time_t curr_time;
    tm *tm_local;

    //Weather conditions
    int light;
    int temp;
    int hum;
};

/**
  * @class PowderStation
  * @brief herited class of a weatherConditions containing weatherconditions
*/

class PowderStation : public WeatherStation{
  public:
    //Constructor
    PowderStation(void);
    PowderStation(int lightPin, Button butt, String location);
    
    // Methods
    void start(void);
    void showConditions(void);
    int goodTemp(void);
    int goodHum(void);
    int checkCond(void);

  protected:
    // Attributs
    static limit condTemp;
    static limit condHum;
  private:

};

const char MAIN_page[] PROGMEM = R"=====(
<html>
<head>
    <title>Powder Station</title>
    <script src="https://kit.fontawesome.com/yourcode.js" crossorigin="anonymous"></script>
    <script>
        // Function to fetch and update sensor data
        function updateSensorData() {
            fetch('/data') // Request sensor data from the server
                .then(response => response.json()) // Parse the JSON response
                .then(data => {
                    // Update the HTML elements with new sensor values
                    document.getElementById('temp').textContent = data.temp + " C";
                    document.getElementById('light').textContent = data.light + " lux";
                    document.getElementById('hum').textContent = data.hum + " %";
                })
                .catch(error => console.error('Error fetching sensor data:', error));
        }

        // Periodically update the data every 5 seconds
        setInterval(updateSensorData, 5000);
        window.onload = updateSensorData; // Fetch data immediately on page load
    </script>
    <<style>
        body, html{
            background-color: lightcyan;
            position: relative;
            margin: 5px;
            height: 95%;
            bottom: 5px;
        }
        .grid {
            position: relative;
            display: grid;
            grid-template-columns: 1fr 1fr; 
            grid-template-rows: auto auto;
            gap: 10px; 
            height: 100%;
        }
        
        h1 {
            color: rgb(51, 153, 255);
            text-align: center;
        }
        
        h2 {
            color: darkcyan;
            text-align: center;
        }
        
        p {
            font-family: Arial, Helvetica, sans-serif;
            font-size: 20px;
            text-align: center;
        }
        
        .box {
            display: flexbox;
            background: lightblue;
            align-items: flex-start;
            justify-content: center;
        }
    </style>>

</head>
<body>
    <h1>Powder Station</h1>
    <div class="grid">
        <div class="box">
            <h2>Time of day</h2>
            <p>Time to shread</p>
        </div>
        <div class="box">
            <h2>Temperature</h2>
            <p id="temp">Loading...SH</p>
        </div>
        <div class="box">
            <h2>Light levels</h2>
            <p id="light">Loading...</p>
        </div>
        <div class="box">
            <h2>Humidity</h2>
            <p id="hum">Loading...</p>
        </div>
    </div>
</body>
</html>
)=====";

#endif