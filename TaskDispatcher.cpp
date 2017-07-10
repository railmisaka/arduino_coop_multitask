/**
    Created 10 July 2017
    TaskDispatcher.cpp
    MIT License

    @author railmisaka
    @version 0.1 7/10/17 
*/

#include "TaskDispatcher.h"
#include "DeltaTime.h"

// ========================================
// TASK DISPATCHER
// ========================================

TaskDispatcher* TaskDispatcher::instance = nullptr;
TaskDispatcher::TaskDispatcher()
{
  tasks = new TaskList();
}

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
  tasks->PushBack(task);
}

void TaskDispatcher::Unregister(TaskBase *task)
{
  tasks->Remove(task);
}

void TaskDispatcher::setup(bool early_time_start)
{
  TasksListElement *current = tasks->First();
  while(current)
  {
    current->task->setup();
    current = current->next;
  }

  if(early_time_start)
  {
    DeltaTime::getInstance();
  }
}

void TaskDispatcher::loop()
{
  // refresh time delta
  DeltaTime::getInstance()->loop();

  unsigned long time_delta = DeltaTime::getInstance()->getDeltaTime();

  TasksListElement *current = tasks->First();
  while(current)
  {
    current->task->loop(time_delta);
    current = current->next;
  }
}

// ========================================
// TASK LIST ELEMENT
// ========================================

TasksListElement::TasksListElement(TaskBase *t)
: task(t), next(nullptr)
{}

// ========================================
// LIST
// ========================================

TaskList::TaskList()
: first(nullptr), last(nullptr)
{}

TaskList::~TaskList()
{
  TasksListElement *tmp;
  TasksListElement *current = first;
  while(current)
  {
    tmp = current->next;
    delete current;
    current = tmp;
  }
}

void TaskList::PushBack(TaskBase *task)
{
  TasksListElement *tmp = new TasksListElement(task);

  if(last)
  {
    // if list not empty
    last->next = tmp;
  }
  else
  {
    // if list empty
    first = last = tmp;
  }
}

void TaskList::PushFront(TaskBase *task)
{
  TasksListElement *tmp = new TasksListElement(task);

  if(first)
  {
    // if list not empty
    tmp->next = first;
    first = tmp;
  }
  else
  {
    // if list empty
    first = last = tmp;
  }
}

void TaskList::Remove(TaskBase *task)
{
  TasksListElement *current = first;

  // prev->next == current
  TasksListElement *prev = nullptr;
  
  while(current)
  {
    if(current->task == task)
    {
      if(current == first)  // if we need to delete first element
      {
        first = first->next;

        if(!first)  // if now list is empty
        {
          last = nullptr;
        }
      }
      else if(current == last)  // if we need to delete last element
      {
        if(prev)  // if last is not first
        {
          last = prev;
        }
        else  // if list length is 1 (last == first, prev == nullptr)
        {
          first = last = nullptr;
        }
      }
      else  // current is in middle of list
      {
        prev->next = current->next;
      }

      delete current;
      
      break;
    }

    prev = current;
    current = current->next;
  }
}

TasksListElement* TaskList::First()
{
  return first;
}

