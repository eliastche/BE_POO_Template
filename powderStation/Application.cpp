/*********************************************************************
 * @file  Apllication.cpp
 * @author Haakon Bogen & Elias Tche
 * @brief Fichier source de l'application
 *********************************************************************/
#include "Application.h"

//Values for optimal powder conditions
#define minTemp4Powder -15
#define maxTemp4Powder -5
#define minHum4Powder 20
#define maxHum4powder 60

//******************************************************************************************************
//Functions for button
//******************************************************************************************************

//Constructors
Button:: Button(){
    this->pin = 13;
    this->state = 0;
    this->oldState = 0;
}
Button:: Button(int pin){
    this->pin = pin;
    this->state = 0;
    this->oldState = 0;
}

//Fetch attributes
int Button:: getState(){
    return state;
}
int Button:: getOldState(){
    return oldState;
}
int Button:: getPin(){
    return pin;
}

//Set attributes
void Button:: changeState(int newSet){
    state = newSet;
}
void Button:: updateOldState(int newSet){
    oldState = newSet;
}
void Button:: changePin(int newSet){
    pin = newSet;
}

//******************************************************************************************************
//Functions for WeatherStation
//******************************************************************************************************

//Constructors
WeatherStation:: WeatherStation() : button(13) {
    screen.begin(16, 2);
    tempHumSensor = SHT31();
    state = showTemp;
    location = "Toulouse";
    lightSensorPin = 12;
}
WeatherStation:: WeatherStation(int lightPin, Button butt, String location){
    screen.begin(16, 2);
    tempHumSensor = SHT31();
    button = butt;
    state = showtemp;
    lightSensorPin = lightPin;
    this->location = location;
}

void WeatherStation:: start(){
    //Set colour
    setRGB(weatherRed,weatherGreen,weatherBlue);
    
    //Print instructions
    setCursor(0,0);
    print(location);
    setCursor(0,1);
    print("Weather Station");
    delay(2000);
    clear();

    setCursor(0,0);
    print("Press button to");
    setCursor(0,1);
    print("start");
    
    //Wait four user to press button
    while(button.getState() == 0){
        button.setState(digitalRead(buttonPIN));
    }
    
    clear();
}

//Fetch attributes
int WeatherStation:: readLight(){
    return light;
}
int WeatherStation:: readTemp(){
    return temp;
}
int WeatherStation:: readHum(){
    return hum;
}

//Set attributes
void WeatherStation:: changeState(){
    if(state < showClock) state++;
    else state = showTemp;
    screen.clear();
}
void WeatherStation:: updateConditionSs(){
    light = readPin(lightSensorPin);
    temp = (int)tempHumSensor.getTemperature();
    hum = (int)tempHumSensor.getHumidity();
}

//Print
void WeatherStation:: showCondtions(){
    screen.setSensor(0,0);
    updateConditions();

    switch (state){
        case showTemp:
            screen.print("Temp: ");
            screen.print(temp);
            break;
        case showHum:
            screen.print("Hum: ");
            screen.print(hum);
            break;
        case showLight:
            screen.print("Light: ");
            screen.print(light);
            break;
        case showClock:
            screen.print("Time is now");
            break;
    }

}

//******************************************************************************************************
//Functions for PowderStation
//******************************************************************************************************

//Constructors
//The constructors for PowderStation works the same as the constructors for a WeatherStation
PowderStation:: PowderStation():WeatherStation(){}
PowderStation:: PowderStation(int lightPin, Button butt, String location): WeatherStation(int lightPin, Button butt, String location){}

void PowderStations:: start(){
    //Set colour
    setRGB(powderRed,powderGreen,powderBlue);
    
    //Print instructions
    setCursor(0,0);
    print(location);
    setCursor(0,1);
    print("PowderStation");
    delay(2000);
    clear();

    setCursor(0,0);
    print("Press button to");
    setCursor(0,1);
    print("start");
    
    //Wait four user to press button
    while(button.getState() == 0){
        button.setState(digitalRead(buttonPIN));
    }
    
    clear();
}