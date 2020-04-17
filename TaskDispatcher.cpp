// ACM
// Created by railmisaka (railmisaka@gmail.com)

#include "TaskDispatcher.h"
#include "DeltaTime.h"
#include "Messages.h"
#include "Timers.h"

TaskDispatcher* TaskDispatcher::instance = nullptr;

TaskDispatcher::TaskDispatcher() :
	tasks_first( nullptr ), tasks_last( nullptr )
{}

TaskDispatcher* TaskDispatcher::GetInstance()
{
	if( !instance ) {
		instance = new TaskDispatcher();
	}
	return instance;
}

void TaskDispatcher::Register( TaskBase *task )
{
	task->next = nullptr;

	if( tasks_last ) {
		tasks_last->next = task;
	} else {
		tasks_first = task;
		tasks_last = task;
	}
}

void TaskDispatcher::Unregister( TaskBase *task )
{
	if( tasks_first == task ) {
		tasks_first = tasks_first->next;
		return;
	}

	TaskBase *current = tasks_first->next;
	TaskBase *prev = tasks_first;
	while( current ) {
		if( current == task ) {
			prev->next = current->next;
			return;
		}

		prev = current;
		current = current->next;
	}
}

void TaskDispatcher::Setup( bool skipSetupTime )
{
	TaskBase *current = tasks_first;
	while( current ) {
		current->Setup();
		current = current->next;
	}

	// Skip time for initialization
	// Initialize to start time calculation
	if( skipSetupTime ) {
		DeltaTime::GetInstance();
	}
}

void TaskDispatcher::Loop()
{
	// swap messages queues
	MessagesQueue::GetInstance()->SwapQueue();

	// refresh time delta
	DeltaTime::GetInstance()->Loop();

	// refresh timers
	TimersDispatcher::GetInstance()->Loop( DeltaTime::GetInstance() );

	TaskBase *current = tasks_first;
	while( current ) {
		if( !current->IsSuspended() ) {
			current->Loop( DeltaTime::GetInstance() );
		}

		current = current->next;
	}
}
