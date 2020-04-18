// ACM
// Created by railmisaka (railmisaka@gmail.com)

// Task have not to block execution thread with delay or something else.

#ifndef __TASK_BASE_H__
#define __TASK_BASE_H__

#include "Arduino.h"
#include "DeltaTime.h"

#include "Debug.h"

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

// This task register self.
class AutoTask : public TaskBase
{
public:
	AutoTask();
	virtual ~AutoTask();
};

#endif
