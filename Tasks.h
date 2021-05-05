// ACM
// Created by railmisaka (railmisaka@gmail.com)

// Task have not to block execution thread with delay or something else.

#ifndef __TASK_BASE_H__
#define __TASK_BASE_H__

#include "Common.h"
#include "Time.h"

class TaskDispatcher;

class TaskBase
{
public:
	TaskBase();
	virtual ~TaskBase() {}

	void Suspend();
	void Resume();
	bool IsSuspended();

protected:
	virtual void Setup() {};
	virtual void Loop( const DeltaTime* ) = 0;

private:
	TaskBase *next;
	bool suspended;

	friend class TaskDispatcher;
};

// This task register self
class AutoTask : public TaskBase
{
public:
	AutoTask();
	virtual ~AutoTask();
};

// Dispatcher for manage all tasks
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

	// Registered tasks
	TaskBase *tasks_first;
	TaskBase *tasks_last;
};

#endif
