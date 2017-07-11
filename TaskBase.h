/**
    Created 10 July 2017
    TaskBase.h
    MIT License

    @author railmisaka
    @version 0.1 7/10/17 
*/

#ifndef __TASK_BASE_H__
#define __TASK_BASE_H__

#include "Arduino.h"
#include "MessagesQueue.h"

class TaskBase
{	
public:
  virtual ~TaskBase() {}

  virtual void setup() = 0;
	virtual void loop(unsigned long delta_time) = 0;
};

#endif
