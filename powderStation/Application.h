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


//Colors
#define weatherRed 75
#define weatherGreen 200
#define weatherBlue 200


#define powderRed 50
#define powderGreen 100
#define powderBlue 255

//States for display of informations in the weather station
#define showTemp 0
#define showHum 1
#define showLight 2
#define showClock 3

/**
  * @class Application
  * @brief Classe Application 
*/

class Button{
  public:
    //Methods

    //Constructors
    Button(void);
    Button(int pin);
    
    //Get attributes
    int getState(void);
    int getPin(void);

    //Set attributes
    void changeState(void);
    void changePin(int pin);
    void updateOldState(void);

  private:
    //Attributes
    int state;
    int pin;
    int oldState;
}

class WeatherStation{
  public:
    Weatherstation(void);
    WeatherStation(int lightPin, Button butt, String location);

    //Update attributes
    void changeState(void);
    void updateConditions(void);

    //Fetch attributes
    int readLight(void);
    int readTemp(void);
    int readHum(void);

    //Other methods
    void showConditions(void);
    void start(void);

  protected:
    //Attributes
    lcd_rgb screen;
    SHT31 tempHumSensor;
    int state;
    int lightSensorPin;
    Button button;
    String location;

    //Condtions
    int light;
    int temp;
    int hum;
}

class PowderStation : public WeatherStation{
  public:
    //Constructor
    PowderStation(void);
    PowderStation(int lightPin, Button butt, String location);
    
    void start(void);
    Boolean goodConditions(void);
    
  protected:

  private:

}
#endif