#ifndef __CLOCK__H__
#define __CLOCK__H__
#include "stdafx.h"
#include <string>

using namespace std;

class Clock
{
public:
	Clock();
	void start();                           //��ʼ��ʱ��
	bool isRuning();                        //���ؼ�ʱ���Ƿ���������
	float getTimeSinceStart();              //���ؾ����˶���ʱ��
private:
	bool running;                           //��������
	LONGLONG startTime;                     //��ʼʱ��
	double freq;                            //Ƶ��
};
#endif