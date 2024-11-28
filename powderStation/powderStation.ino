#include <Arduino.h>
#include <Wire.h>
#include <SHT31.h>
#include <rgb_lcd.h>

//Pins
#define buttonPIN 13//D7
#define lightSensorPIN 12//D6

//Screenstates
#define showTemp 0
#define showHum 1
#define showLight 2
#define showClock 3

//Values for optimal powder conditions
#define minTemp4Powder -15
#define maxTemp4Powder -5
#define minHum4Powder 20
#define maxHum4Powder 60

int buttonState = 0;
int oldButtonState = 0;
int screenState = showTemp;

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
}
int temp;
int hum;
int light;
void loop() {
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
