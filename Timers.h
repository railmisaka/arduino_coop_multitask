// ACM
// Created by railmisaka (railmisaka@gmail.com)

#ifndef __TIMERS_H__
#define __TIMERS_H__

#include "Common.h"
#include "DeltaTime.h"

class TimerBase;

class TimersDispatcher
{
public:
	static TimersDispatcher* GetInstance();

	void Loop( const DeltaTime* );

	void Register( TimerBase* );
	void Unregister( TimerBase* );

private:
	static TimersDispatcher *instance;

	TimerBase *timers;
};

class TimerBase
{
public:
	TimerBase();
	~TimerBase();

	virtual void Stop();
	virtual void Start();
	virtual bool IsStopped();

	virtual void Pause();
	virtual void Resume();
	virtual bool IsPaused();

	virtual bool IsActive();

	virtual void Reset() {};

protected:
	virtual void Loop( const DeltaTime* ) = 0;

	TimerBase *next;
	bool paused;
	bool stopped;

	friend class TimersDispatcher;
};


class IntervalTimer : public TimerBase
{
public:
	IntervalTimer( tTime );

	bool OnTime();

	virtual void Reset() { currentTime = 0; };

protected:
	virtual void Loop( const DeltaTime* ) override;

private:
	tTime intervalTime;
	tTime currentTime;
};

class SwitchTimer : public TimerBase
{
public:
	SwitchTimer( tTime, tTime );

	bool OnFirst();
	bool OnSecond();

	virtual void Reset()
	{
		currentTime = 0;
		firstInterval = true;
	};

protected:
	virtual void Loop( const DeltaTime* ) override;

private:
	tTime firstIntervalTime;
	tTime secondIntervalTime;
	tTime currentTime;
	bool firstInterval;
};

#endif
