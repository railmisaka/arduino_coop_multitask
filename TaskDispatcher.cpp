/**
    Created 10 July 2017
    TaskDispatcher.cpp
    MIT License

    @author railmisaka
    @version 0.11 7/20/17 
*/

#include "TaskDispatcher.h"
#include "DeltaTime.h"
#include "MessagesQueue.h"

// ========================================
// TASK DISPATCHER
// ========================================

TaskDispatcher* TaskDispatcher::instance = nullptr;
TaskDispatcher::TaskDispatcher()
: tasks_first(nullptr), tasks_last(nullptr)
{}

TaskDispatcher* TaskDispatcher::getInstance()
{
  if(!instance)
  {
    instance = new TaskDispatcher();
  }

  return instance;
}

void TaskDispatcher::Register(TaskBase *task)
{
  task->next = nullptr;
  
  if(tasks_last)
  {
    tasks_last->next = task;
  }
  else
  {
    tasks_last = task;
  }
}

void TaskDispatcher::Unregister(TaskBase *task)
{
  if(tasks_first == task)
  {
    tasks_first = tasks_first->next;
    return;
  }
  
  TaskBase *current = tasks_first->next;
  TaskBase *prev = tasks_first;
  while(current)
  {
    if(current == task)
    {
      prev->next = current->next;
      return;
    }
    prev = current;
    current = current->next;
  }
}

void TaskDispatcher::setup(bool early_time_start)
{
  TaskBase *current = tasks_first;
  while(current)
  {
    current->setup();
    current = current->next;
  }

  if(early_time_start)
  {
    DeltaTime::getInstance();
  }
}

void TaskDispatcher::loop()
{
  // swap messages queues
  MessagesQueue::getInstance()->SwapQueue();
  
  // refresh time delta
  DeltaTime::getInstance()->loop();

  unsigned long time_delta = DeltaTime::getInstance()->getDeltaTime();

   TaskBase *current = tasks_first;
  while(current)
  {
    current->loop(time_delta);
    current = current->next;
  }
}

