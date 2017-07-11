#include "TaskDispatcher.h"
#include "DeltaTime.h"

#include <LiquidCrystal.h>

#include "LCD_16x2.h"
LCD_16x2 *lcd;

#include "Illumination1.h"
Illumination1 *illumination;

void setup()
{
  // create all your tasks here and register to dispatcher by
  // TaskDispatcher::getInstance()->Register(task);
  // (your tasks must be inherited from TaskBase)
  lcd = new LCD_16x2(new LiquidCrystal(13, 12, 11, 10, 9, 8));
  lcd->setMessage(1, "Arduino COOP Multitask library test");
  TaskDispatcher::getInstance()->Register(lcd);
  
  illumination = new Illumination1(A0);
  TaskDispatcher::getInstance()->Register(illumination);
  
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

  if(MessagesQueue::getInstance()->getFirst())
  {
    String str = String(*(int*)MessagesQueue::getInstance()->getFirst()->value);
    lcd->setMessage(2, str);
  }
}
