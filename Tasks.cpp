// ACM
// Created by railmisaka (railmisaka@gmail.com)

#include "Tasks.h"
#include "TaskDispatcher.h"

TaskBase::TaskBase() :
	suspended( false )
{}

void TaskBase::Suspend()
{
	suspended = true;
}

void TaskBase::Resume()
{
	suspended = false;
}

bool TaskBase::IsSuspended()
{
	return suspended;
}

AutoTask::AutoTask()
{
	TaskDispatcher::GetInstance()->Register( this );
}

AutoTask::~AutoTask()
{
	TaskDispatcher::GetInstance()->Unregister( this );
}
