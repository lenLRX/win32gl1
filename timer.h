#ifndef __TIMER__H__
#define __TIMER__H__
#include "director.h"
#include <string>

using namespace std;

class timer
{
public:
	timer();
	void setDelayTime(float t);             //设定延时
	void start();                           //开始计时器
	bool isRuning();                        //返回计时器是否正在运行
	void tick();                            //滴答（经过一段时间）
	void registerEvent(string name);        //注册事件
private:
	bool running;                           //正在运行
	float delayTime;                        //设定的延迟时间
	LONGLONG startTime;                     //起始时间
	double freq;                            //频率
	string _name;                            //注册的事件名称
};

#endif