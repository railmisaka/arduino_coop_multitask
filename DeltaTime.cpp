// ACM
// Created by railmisaka (railmisaka@gmail.com)

#include "Common.h"
#include "DeltaTime.h"

DeltaTime* DeltaTime::instance = nullptr;

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
	
tTime DeltaTime::GetDeltaTime() const
{
	return stepTime;
}
