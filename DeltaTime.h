// ACM
// Created by railmisaka (railmisaka@gmail.com)

// Time delta between frames

#ifndef __DELTA_TIME_H__
#define __DELTA_TIME_H__

#include "Common.h"

class DeltaTime
{
public:
	static DeltaTime* GetInstance();

	void Loop();

	tTime GetDeltaTime() const;

private:
	DeltaTime();
	static DeltaTime *instance;

	tTime prevTime;
	tTime stepTime;
};

#endif
