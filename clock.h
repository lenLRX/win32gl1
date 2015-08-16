#ifndef __CLOCK__H__
#define __CLOCK__H__
#include "stdafx.h"
#include <string>

using namespace std;

class Clock
{
public:
	Clock();
	~Clock();
	void start();                           //��ʼ��ʱ��
	bool isRuning();                        //���ؼ�ʱ���Ƿ���������
	void pause();                           //��ͣ
	void resume();                          //����
	float getTimeSinceStart();              //���ؾ����˶���ʱ��
private:
	bool running;                           //��������
	Clock* pauseHandler;                    //ʱ����ͣ����ʱ��
	float compensation;                     //ʱ�Ӳ���ֵ
	LONGLONG startTime;                     //��ʼʱ��
	double freq;                            //Ƶ��
};
#endif