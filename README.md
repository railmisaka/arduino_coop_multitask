#### Cooperative multitasking for Arduino.

Overhead:
```
Flash: 1446 	RAM: 23     (just library)
Flash: 1554 	RAM: 33     (one empty task)
```

You need to copy files to your project folder.
Library files:
* _CustomTypes.h_
* _DeltaTime.h_
* _DeltaTime.cpp_
* _TaskBase.h_
* _TaskDispatcher.h_
* _TaskDispatcher.cpp_

And sketch template:
* _arduino_coop_multitask.ino_
(don't forget to rename it)

Multitasking achieve by creating light tasks and updating them every loop circle.
For create task you have to create class iherited from ```TaskBase```

```c++
#include "TaskBase.h"
class CustomTask: public TaskBase
{
public:
  void setup();
  void loop(unsigned long delta_time);
};
```

```setup``` func will be called from main setup func.
```loop``` func will be called every circle. Parameter ```delta_time``` is time of previous circle.

#### Task must not block control and not call ```dalay``` func.

* Every of tast must be register in ```TaskDispatcher``` __BEFORE__ call of
    ```c++
    TaskDispatcher::getInstance()->setup();
    ```

* You can register your task by
    ```c++
    TaskDispatcher::getInstance()->Register(task);
    ```

* You also can unregister task (it will not to be update after this)
    ```c++
    TaskDispatcher::getInstance()->Unregister(task);
    ```

* You also can use
    ```c++
    DeltaTime::getInstance()->getDeltaTime()
    ```
    It will return time of previous main loop circle (same as ```delta_time```). But you don't need it in ```TaskBase::loop``` func.

This works pretty simple:
DeltaTime calling ```millis``` func and calculate previous circle time.
It update in TaskDispatcher in the beginning of every loop.

TaskDispatcher contains list of registered tasks and call it's ```setup``` in main setup and ```loop``` every main loop.
