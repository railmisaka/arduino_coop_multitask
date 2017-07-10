Cooperative multitasking for Arduino.

Overhead(just library) 		Flash: 1446 	RAM: 23
Overhead(one empty class)	Flash: 1554 	RAM: 33

Multitasking achieve by creating light tasks and updating them every loop circle.
For create task you have to create class iherited from TaskBase

#include "TaskBase.h"
class CustomTask: public TaskBase
{
public:
  void setup();
  void loop(unsigned long delta_time);
};

setup func will be called from main setup func.
loop func will be called every circle. Parameter delta_time is time of previous circle.

Every of tast must be register in TaskDispatcher BEFORE 
TaskDispatcher::getInstance()->setup().

You can register your task by
TaskDispatcher::getInstance()->Register(task);

You also can unregister task (it will not to be update after this)
TaskDispatcher::getInstance()->Unregister(task);

You also can use
DeltaTime::getInstance()->getDeltaTime()
it will return time of previous main llop circle (same as delta_time). But you don't need it in TaskBase::loop.

This works pretty simple:
DeltaTime calling millis func and calculate previous circle time.
It update in TaskDispatcher in the beginning of every loop.

TaskDispatcher contains list of registered tasks and call it's setup in main setup and loop every main loop.
