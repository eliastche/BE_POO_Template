/*********************************************************************
 * @file  Apllication.cpp
 * @author Haakon Bogen & Elias Tche
 * @brief Fichier source de l'application
 *********************************************************************/
#include "Application.h"
#include "Arduino.h"
#include <Wire.h>
#include <SHT31.h>
#include <rgb_lcd.h>

//Pins
#define buttonPIN 13//D7
#define lightSensorPIN 12//D6

//Values for optimal powder conditions
#define minTemp4Powder -15
#define maxTemp4Powder -5
#define minHum4Powder 20
#define maxHum4powder 60

//Screenstates
#define showTemp 0
#define showHum 1
#define showLight 2
#define showClock 3


Application::Application()
{
  // Code
  ; 
}
  
Application::~Application()
{
  // Code
  ;
}  

void Application::init(void)
{
  // Code
    ;
}


void Application::run(void)
{
  // Code
    ;
}
