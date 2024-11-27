#include <Arduino.h>
#include <Wire.h>
#include <SHT31.h>
#include <rgb_lcd.h>

#define minTemp4Powder -15
#define maxTemp4Powder -5
#define minHum4Powder 20
#define maxHum4powder 60

constant int buttonPin = 13;

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
      
    }
};

MyScreen screen;
MySensor sensor;

void setup() {
  //Initialize button
  pinMode(buttonPin, )

  //Initialze sensor and start screens
  sensor.begin();
  screen.init();
}

void loop() {
  sensor.showConditons(screen);
}
