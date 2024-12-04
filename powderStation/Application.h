/*********************************************************************
 * @file  Apllication.h
 * @author Haakon Bogen & Elias Tche
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef APPLICATION_H_
#define APPLICATION_H_

//Include necessary libraires for external sensor/ screens
#include "Arduino.h"
#include "Wire.h"
#include "SHT31.h"
#include "rgb_lcd.h"


//States for display of informations in the weather station
#define showTemp 0
#define showHum 1
#define showLight 2
#define showClock 3

enum condition{
    minTemp: int;
    maxTemp: int;

    minHum: int;
    maxTemp: hum;
}

/**
  * @class Application
  * @brief Classe Application 
*/    
class WeatherStation{
  public:
    Weatherstation(void);

    //Update attributes
    void changeState(void);
    void setButtonSate(void);
    void updateConditionds(void);

    //Fetch attributes
    int getState(void);
    int getButtonState(void);
    int getOldbuttonState(void);

    //Other methods
    void showConditions(void);

  protected:
    int state;
    lcd_rgb screen;
    SHT31 tempHumSensor;
    int lightSensorPin;
    int buttonPin;
    int buttonState;
    int oldButtonState;

  private:

}

class PowderStaition : public WeatherStation{
  public:
    Boolean goodConditions;
    condition;
    
  protected:

  private:

}

#endif