/**
    Created 10 July 2017
    DeltaTime.cpp
    MIT License

    @author railmisaka
    @version 0.11 7/20/17 
*/

#include "Arduino.h"

#include "DeltaTime.h"
#include "CustomTypes.h"

DeltaTime* DeltaTime::instance = nullptr;

DeltaTime::DeltaTime()
: stepTime(0)
{
  prevTime = millis();
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
}
	
unsigned long DeltaTime::getDeltaTime()
{
	return stepTime;
}

