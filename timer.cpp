#include "stdafx.h"
#include "timer.h"
#include "director.h"
#include <cassert>

timer::timer() :running(false), delayTime(0), _name("no name")
{
	LARGE_INTEGER LARGE;
	QueryPerformanceFrequency(&LARGE);
	freq = (double)LARGE.QuadPart;
}

void timer::setDelayTime(float t)
{
	delayTime = t;
}

void timer::start()
{
	if (!running)
	{
		assert(delayTime>0);//延迟时间应大于0
		running = true;
		LARGE_INTEGER LARGE;
		QueryPerformanceCounter(&LARGE);
		startTime = LARGE.QuadPart;
	}
}

bool timer::isRuning()
{
	return running;
}

void timer::tick()
{
	assert(running);
	LARGE_INTEGER LARGE;
	QueryPerformanceCounter(&LARGE);
	LONGLONG nowL = LARGE.QuadPart;
	float dt=((float)(nowL - startTime)) / freq;
	if (dt >= delayTime)
	{
		running = false;
		EventMsg msg;
		msg.name = _name;
		Director::getTheInstance()->raiseEvent(msg);
		
	}
}

void timer::registerEvent(string name)
{
	_name = name;
}
