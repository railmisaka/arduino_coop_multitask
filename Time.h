// ACM
// Created by railmisaka (railmisaka@gmail.com)

#ifndef __TIMERS_H__
#define __TIMERS_H__

#include "Common.h"
#include "Time.h"

class DeltaTime
{
public:
	static DeltaTime* GetInstance();

	void Loop();

	tTime GetDeltaTime() const
	{
		return stepTime;
	}

private:
	DeltaTime();
	static DeltaTime *instance;

	tTime prevTime;
	tTime stepTime;
};

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
	virtual ~TimerBase();

	void Stop();
	void Start();
	bool IsStopped();

	void Pause();
	void Resume();
	bool IsPaused();

	bool IsActive();

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
