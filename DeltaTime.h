/**
    Created 10 July 2017
    DeltaTime.h
    MIT License

    @author railmisaka
    @version 0.11 7/20/17 
*/

#ifndef __DELTA_TIME_H__
#define __DELTA_TIME_H__

#include "MessagesQueue.h"

class DeltaTime
{
private:
  static DeltaTime *instance;
  DeltaTime();
  
private:
	unsigned long prevTime;
	unsigned long stepTime;
	
public:
  // singlethon
  static DeltaTime* getInstance();

	void loop();
	
	unsigned long getDeltaTime();
};

#endif

