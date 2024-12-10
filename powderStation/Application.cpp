/*********************************************************************
 * @file  Apllication.cpp
 * @author Haakon Bogen & Elias Tche
 * @brief Fichier source de l'application
 *********************************************************************/
#include "Application.h"

//******************************************************************************************************
//Functions for button
//******************************************************************************************************

//Constructors
Button:: Button(){
    //Initialiser les valeurs
    this->pin = 13;
    this->state = 0;
    this->oldState = 0;

    //Initialiser le pin
    pinMode(this->pin, INPUT);
}
Button:: Button(int pin){
    //Initialiser les valeurs
    this->pin = pin;
    this->state = 0;
    this->oldState = 0;

    //Initialiser le pin
    pinMode(this->pin, INPUT);
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
void Button:: updateState(int newSet){
    state = newSet;
}
void Button:: updateOldState(){
    oldState = state;
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
    state = SHOWTEMP;
    location = "Toulouse";
    lightSensorPin = 12;
    curr_time = time(NULL);
    
}
WeatherStation:: WeatherStation(int lightPin, Button butt, String location){
    screen.begin(16, 2);
    tempHumSensor = SHT31();
    button = butt;
    state = SHOWTEMP;
    lightSensorPin = lightPin;
    this->location = location;
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
String WeatherStation:: readTime(){
  return (String)tm_local->tm_hour+ ":" + (String)tm_local->tm_min + ":" + (String)tm_local->tm_sec;
}

//Set attributes
void WeatherStation:: changeState(){
    if(state < SHOWCLOCK){
       state++;
    }
    else{
      state = SHOWTEMP;
    }
    screen.clear();
}
void WeatherStation:: updateConditions(){
    light = digitalRead(lightSensorPin);
    temp = tempHumSensor.getTemperature();
    hum = tempHumSensor.getHumidity();
    tm *tm_local = localtime(&curr_time);
}
//Other methods
void WeatherStation:: showConditions(){
    screen.setCursor(0,0);
    updateConditions();

    switch (state){
        case SHOWTEMP:
            screen.print("Temp: ");
            screen.print(temp);
            break;
        case SHOWHUM:
            screen.print("Hum: ");
            screen.print(hum);
            break;
        case SHOWLIGHT:
            screen.print("Light: ");
            screen.print(light);
            break;
        case SHOWCLOCK:
            screen.print("Time:" );
            //screen.print((String)tm_local->tm_hour);
            screen.print(":");
            //screen.print((String)tm_local->tm_min);
            screen.print(":");
            //screen.print((String)tm_local->tm_sec);
            break;
    }

}
void WeatherStation:: start(){
    //Initalize lightsensorpin and temperature and humidity sensor
    pinMode(lightSensorPin, INPUT);
    tempHumSensor.begin();

    //Set colour
    screen.setRGB(weatherRed,weatherGreen,weatherBlue);
    
    //Print instructions
    screen.setCursor(0,0);
    screen.print(location);
    screen.setCursor(0,1);
    screen.print("Weather Station");
    delay(2000);
    screen.clear();

    screen.setCursor(0,0);
    screen.print("Press button to");
    screen.setCursor(0,1);
    screen.print("start");
    
    //Wait four user to press button
    while(button.getState() == 0){
        button.updateState(digitalRead(button.getPin()));
    }
    
    screen.clear();
}
void WeatherStation:: waitForNetwork(){
  screen.setCursor(0,0);
  screen.print("Waiting for");
  screen.setCursor(0,1);
  screen.print("network;)");
}
void WeatherStation:: clearScreen(){
  screen.clear();
}

//******************************************************************************************************
//Functions for PowderStation
//******************************************************************************************************

//Constructors
//The constructors for PowderStation works the same as the constructors for a WeatherStation
PowderStation:: PowderStation():WeatherStation(){}
PowderStation:: PowderStation(int lightPin, Button butt, String location): WeatherStation(lightPin, butt, location){}

//Start function for powderStation
void PowderStation:: start(){
    //Initalize lightsensorpin
    pinMode(lightSensorPin, INPUT);
    tempHumSensor.begin();

    //Set colour
    screen.setRGB(powderRed,powderGreen,powderBlue);
    
    //Print instructions
    screen.setCursor(0,0);
    screen.print(location);
    screen.setCursor(0,1);
    screen.print("PowderStation");
    delay(2000);
    screen.clear();

    screen.setCursor(0,0);
    screen.print("Press button to");
    screen.setCursor(0,1);
    screen.print("start");
    
    //Wait four user to press button
    while(button.getState() == 0){
        button.updateState(digitalRead(button.getPin()));
    }
    
    screen.clear();
}

//Show conditions for powderStation
void PowderStation:: showConditions(){
  if(checkCond()){
    screen.setCursor(0,0);
    screen.print("Go shred dude!!!");
  }
  else{
    WeatherStation :: showConditions();
  }
}

// Functions for right weather conditions
int PowderStation:: goodTemp(){
  return this->temp >= MIN_TEMP_POWDER && this->temp <= MAX_TEMP_POWDER;
}
int PowderStation:: goodHum(){
  return this->hum >= MIN_HUM_POWDER && this->hum <= MAX_HUM_POWDER;
}

int PowderStation:: checkCond(){
  return this->goodTemp() && this->goodHum();
}
