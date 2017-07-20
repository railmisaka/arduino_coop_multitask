/**
    Created 10 July 2017
    TaskBase.h
    MIT License

    @author railmisaka
    @version 0.11 7/20/17 
*/

#ifndef __TASK_BASE_H__
#define __TASK_BASE_H__

#include "Arduino.h"
#include "MessagesQueue.h"

class TaskBase
{
friend class TaskDispatcher;

public:
  virtual ~TaskBase() {}

  virtual void setup() = 0;
	virtual void loop(unsigned long delta_time) = 0;

private:
  TaskBase *next;
};

#endif

