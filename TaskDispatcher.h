/**
    Created 10 July 2017
    TaskDispatcher.cpp
    MIT License

    @author railmisaka
    @version 0.1 7/10/17 
*/

#ifndef __TASK_DISPATCHER_H__
#define __TASK_DISPATCHER_H__

#include "TaskBase.h"

// forward
class TaskList;

class TaskDispatcher
{
private:
  TaskDispatcher();

  TaskList *tasks;  // registeres tasks
  
  static TaskDispatcher *instance;

public:
  // singlethon
  static TaskDispatcher* getInstance();

public:
  void Register(TaskBase *task);
  void Unregister(TaskBase *task);

  void setup(bool early_time_start = false);
  void loop();
};

class TasksListElement
{
public:
  TasksListElement(TaskBase *t);
  TaskBase *task;
  TasksListElement *next;
};

class TaskList
{
public:
  TaskList();
  ~TaskList();
  
private:
  TasksListElement *first;
  TasksListElement *last;
  
public:
  void PushBack(TaskBase *task);
  void PushFront(TaskBase *task);

  void Remove(TaskBase *task);

  TasksListElement* First();
};

#endif
