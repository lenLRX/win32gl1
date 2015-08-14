#include "stdafx.h"
#include "timer.h"
#include <cassert>

timer::timer() :running(false), delayTime(0)
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
	assert(delayTime>0);//延迟时间应大于0
	running = true;
	LARGE_INTEGER LARGE;
	QueryPerformanceCounter(&LARGE);
	startTime = LARGE.QuadPart;
}

bool timer::isRuning()
{
	return running;
}

void timer::tick()
{
	LARGE_INTEGER LARGE;
	QueryPerformanceCounter(&LARGE);
	LONGLONG nowL = LARGE.QuadPart;
	float dt=((float)(nowL - startTime)) / freq;
	if (dt >= delayTime)
	{
		EventMsg msg;
		msg.name = _name;
		Director::getTheInstance()->raiseEvent(msg);
		running = false;
	}
}

void timer::registerEvent(string name)
{
	_name = name;
}