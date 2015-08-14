#ifndef __TIMER__H__
#define __TIMER__H__
#include "director.h"
#include <string>

using namespace std;

class timer
{
public:
	timer();
	void setDelayTime(float t);             //�趨��ʱ
	void start();                           //��ʼ��ʱ��
	bool isRuning();                        //���ؼ�ʱ���Ƿ���������
	void tick();                            //�δ𣨾���һ��ʱ�䣩
	void registerEvent(string name);        //ע���¼�
private:
	bool running;                           //��������
	float delayTime;                        //�趨���ӳ�ʱ��
	LONGLONG startTime;                     //��ʼʱ��
	double freq;                            //Ƶ��
	string _name;                            //ע����¼�����
};

#endif