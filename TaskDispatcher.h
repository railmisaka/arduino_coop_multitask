// ACM
// Created by railmisaka (railmisaka@gmail.com)

// Dispatcher for manage all tasks

#ifndef __TASK_DISPATCHER_H__
#define __TASK_DISPATCHER_H__

#include "Tasks.h"

class TaskDispatcher
{
public:
	static TaskDispatcher* GetInstance();

	void Register( TaskBase *task );
	void Unregister( TaskBase *task );

	void Setup( bool skipSetupTime = true );
	void Loop();

private:
	TaskDispatcher();
	static TaskDispatcher *instance;

	// registered tasks
	TaskBase *tasks_first;
	TaskBase *tasks_last;
};

#endif

