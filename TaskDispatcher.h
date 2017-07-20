/**
    Created 10 July 2017
    TaskDispatcher.cpp
    MIT License

    @author railmisaka
    @version 0.11 7/20/17 
*/

#ifndef __TASK_DISPATCHER_H__
#define __TASK_DISPATCHER_H__

#include "TaskBase.h"

// forward
class TaskList;

class TaskDispatcher
{
private:
  // registered tasks
  TaskBase *tasks_first;
  TaskBase *tasks_last;

// singlethon
private:
  TaskDispatcher();
  static TaskDispatcher *instance;

public:
  static TaskDispatcher* getInstance();
//

public:
  void Register(TaskBase *task);
  void Unregister(TaskBase *task);

  void setup(bool early_time_start = false);
  void loop();
};

#endif

