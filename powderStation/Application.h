/*********************************************************************
 * @file  Apllication.h
 * @author Haakon Bogen & Elias Tche
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <String.h>

//Include necessary libraires for external sensor/ screens
#include <Arduino.h>
#include <Wire.h>
#include <SHT31.h>
#include <rgb_lcd.h>


//Colours
#define weatherRed 75
#define weatherGreen 200
#define weatherBlue 200

#define powderRed 50
#define powderGreen 100
#define powderBlue 255

//States for display of informations in the weather station
#define SHOWTEMP 0
#define SHOWHUM 1
#define SHOWLIGHT 2
#define SHOWCLOCK 3

/**
  * @class Application
  * @brief Classe Application 
*/

typedef struct condtion{
  int max;
  int min;
} cond;

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

    //Condtions
    int light;
    int temp;
    int hum;
};

class PowderStation : public WeatherStation{
  public:
    //Constructor
    PowderStation(void);
    PowderStation(int lightPin, Button butt, String location);
    
    void start(void);
    boolean goodConditions(void);
    
  protected:
    

  private:

};

const char MAIN_page[] PROGMEM = R"=====(
<html>
<head>
    <title>Powder Station</title>
    <script src="https://kit.fontawesome.com/yourcode.js" crossorigin="anonymous"></script>
    <style>
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
    </style>

</head>
<body>
    <h1>Powder Station</h1>
    <div class="grid">
        <div class="box">
            <h2>Time of day</h2>
            <p>Woup woup! It's powder time!</p>
        </div>
        <div class="box">
            <h2>Temperature</h2>
            <p>{{TEMP}} C</p>
        </div>
        <div class="box">
            <h2>Light levels</h2>
            <p>{{LIGHT}} lux</p>
        </div>
        <div class="box">
            <h2>Humidity</h2>
            <p>{{HUM}} %</p>
        </div>
    </div>
</body>
</html>
)=====";

#endif