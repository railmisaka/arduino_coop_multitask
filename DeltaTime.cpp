/**
    Created 10 July 2017
    DeltaTime.cpp
    MIT License

    @author railmisaka
    @version 0.1 7/10/17 
*/
//#define TIME_SERIAL_LOGGING
#include "Arduino.h"

#include "DeltaTime.h"
#include "CustomTypes.h"

DeltaTime* DeltaTime::instance = nullptr;

DeltaTime::DeltaTime()
: stepTime(0)
{
  prevTime = millis();

  #ifdef TIME_SERIAL_LOGGING
  Serial.begin(9600);
  #endif
}

DeltaTime* DeltaTime::getInstance()
{
  if(instance == nullptr)
  {
    instance = new DeltaTime();
  }

  return instance;
}

void DeltaTime::loop()
{
  unsigned long tmp = millis();
  
  // overflow protection
  if(tmp < prevTime)
  {
    stepTime = (MAX_UNSIGNED_LONG - prevTime) + tmp;
  }
  else
  {
    stepTime = tmp - prevTime;
  }
  
  //
  prevTime = tmp;

  #ifdef TIME_SERIAL_LOGGING
  Serial.println(stepTime);
  #endif
}
	
unsigned long DeltaTime::getDeltaTime()
{
	return stepTime;
}
