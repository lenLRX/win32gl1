#include "stdafx.h"
#include "clock.h"
#include <cassert>

Clock::Clock()
{
	LARGE_INTEGER LARGE;
	QueryPerformanceFrequency(&LARGE);
	freq = (double)LARGE.QuadPart;
}

void Clock::start()
{
	if (!running)
	{
		running = true;
		LARGE_INTEGER LARGE;
		QueryPerformanceCounter(&LARGE);
		startTime = LARGE.QuadPart;
	}
}

bool Clock::isRuning()
{
	return running;
}

float Clock::getTimeSinceStart()
{
	assert(running);
	LARGE_INTEGER LARGE;
	QueryPerformanceCounter(&LARGE);
	LONGLONG nowL = LARGE.QuadPart;
	return ((float)(nowL - startTime)) / freq;
}