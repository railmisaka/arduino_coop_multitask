// ACM
// Created by railmisaka (railmisaka@gmail.com)

#include "Time.h"

DeltaTime* DeltaTime::instance = nullptr;
TimersDispatcher* TimersDispatcher::instance = nullptr;

DeltaTime::DeltaTime() :
	stepTime( 0UL )
{
	prevTime = millis();
}

DeltaTime* DeltaTime::GetInstance()
{
	if( instance == nullptr ) {
		instance = new DeltaTime();
	}
	return instance;
}

void DeltaTime::Loop()
{
	tTime tmp = millis();

	// overflow protection
	if( tmp < prevTime ) {
		stepTime = (MAX_UNSIGNED_LONG - prevTime) + tmp;
	} else {
		stepTime = tmp - prevTime;
	}

	prevTime = tmp;
}

TimersDispatcher* TimersDispatcher::GetInstance()
{
	if( instance == nullptr ) {
		instance = new TimersDispatcher();
	}
	return instance;
}

void TimersDispatcher::Loop( const DeltaTime* delta )
{
	TimerBase *current = timers;
	while( current ) {
		if( current->IsActive() ) {
			current->Loop( delta );
		}

		current = current->next;
	}
}

void TimersDispatcher::Register( TimerBase* timer )
{
	timer->next = timers;
	timers = timer;
}

void TimersDispatcher::Unregister( TimerBase* timer )
{
	if( timers == timer ) {
		timers = timers->next;
		return;
	}

	TimerBase *current = timers->next;
	TimerBase *prev = timers;
	while( current ) {
		if( current == timer ) {
			prev->next = current->next;
			return;
		}

		prev = current;
		current = current->next;
	}
}

TimerBase::TimerBase() :
	next( nullptr ), paused( false ), stopped( false )
{
	TimersDispatcher::GetInstance()->Register( this );
}

TimerBase::~TimerBase()
{
	TimersDispatcher::GetInstance()->Unregister( this );
}


void Stop();
void Start();
bool IsStopped();

void Pause();
void Resume();

bool IsActive();

void TimerBase::Stop()
{
	stopped = true;
}

void TimerBase::Start()
{
	if( stopped ) {
		Reset();
	}

	stopped = false;
	paused = false;
}

bool TimerBase::IsStopped()
{

	return stopped;
}

void TimerBase::Pause()
{
	paused = true;
}

void TimerBase::Resume()
{
	paused = false;
}

bool TimerBase::IsPaused()
{
	return paused;
}

bool TimerBase::IsActive()
{
	return !IsStopped() && !IsPaused();
}

IntervalTimer::IntervalTimer( tTime i ) :
	intervalTime( i ), currentTime( 0UL )
{}

bool IntervalTimer::OnTime()
{
	if( currentTime > intervalTime ) {
		currentTime -= intervalTime;
		return true;
	}
	return false;
}

void IntervalTimer::Loop( const DeltaTime* delta )
{
	currentTime += delta->GetDeltaTime();
}

SwitchTimer::SwitchTimer( tTime f, tTime s ) :
	firstIntervalTime( f ), secondIntervalTime( s ), currentTime( 0UL ), firstInterval( true )
{}

bool SwitchTimer::OnFirst()
{
	if( firstInterval ) {
		if( currentTime > firstIntervalTime ) {
			currentTime -= firstIntervalTime;
			firstInterval = false;
			return true;
		}
	}
	return false;
}
bool SwitchTimer::OnSecond()
{
	if( !firstInterval ) {
		if( currentTime > secondIntervalTime ) {
			currentTime -= secondIntervalTime;
			firstInterval = true;
			return true;
		}
	}
	return false;
}

void SwitchTimer::Loop( const DeltaTime* delta )
{
	currentTime += delta->GetDeltaTime();
}
