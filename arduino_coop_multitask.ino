#include "TaskDispatcher.h"
#include "DeltaTime.h"

void setup()
{
  // create all your tasks here and register to dispatcher by
  // TaskDispatcher::getInstance()->Register(task);
  // (your tasks must be inherited from TaskBase)
    
  // dispatcher initialization
  TaskDispatcher::getInstance()->setup(false);
  
  // your init code

}

void loop()
{
  // dispatcher loop
  TaskDispatcher::getInstance()->loop();
  
  // your main loop code
  // you can use DeltaTime (singlethon) here
  // it refreshes in dispatcher (DeltaTime::getInstance()->getDeltaTime())
  
}
