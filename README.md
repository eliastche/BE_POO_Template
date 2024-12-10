# Project Weather Station
This project is based on the ESP8266 module and coded in Arduino and C++.
The goal of this project is to create a weather station with being able to measure temperature, humidity, and light levels.
For this project you need: 
- The ESP8266 it's self
- Grove LCD screen
- Grove Temperature and humidity sensor
- A button
- A light sensor

In this project, we have also utilized the WiFi card on the ESP8266 making it able to connect to a local hotspot where we have embeded an HTML page to the controller displaying the data in a nice formate on the webpage as well.

## How to use it:
### Connecting to network
When starting the program for the first time it is important to have the rigth password and name of your local hot spot. change the WiFi credentials (STASSID and STAPSK) to your own WiFi credentials.

### Uploading the code
When uploading the code, it should reset the vi RTS pin and take you to the Serial Monitor in your Arduino IDE. Here, you will see a screen saying "Connecting to "Your-WiFi-name," and when the WiFi is connected, you will see your IP address.
If you are using the screen it will say "Waiting for network ;)"
When the network is connected the screen will change to say "Toulouse Powderstation" and then "Pres button to start". It is important when you see that you press the button because that microcontroller is close to exceeding its RAM limits it will restart its config mode if the button is not pressed.

When the button is pressed and you see either Hum:, Light:, Time:, or Temp: everything is good to go.

You can now also go to the HTML site entering the IP address of your network ensuring that both your device and your microcontroller is connected to the same WiFi

### Conditions
In the code, there are also some conditions for the ideal powder and when conditions are made the utility of the button no longer works and the most important message appears: **Go shread dude!!!**


