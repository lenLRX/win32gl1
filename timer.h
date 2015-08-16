#ifndef __TIMER__H__
#define __TIMER__H__
#include "clock.h"
#include "event.h"
#include <string>

using namespace std;

class timer
{
public:
	timer();
	~timer();
	void setDelayTime(float t);             //�趨��ʱ
	void start();                           //��ʼ��ʱ��
	bool isRuning();                        //���ؼ�ʱ���Ƿ���������
	void tick();                            //�δ𣨾���һ��ʱ�䣩
	void pause();                           //��ͣ
	void resume();                          //����
	void registerEvent(string name);        //ע���¼�
	void registerEvent(EventMsg msg);
private:
	bool running;                           //��������
	Clock* pauseHandler;                    //��ʱ����ͣ����ʱ��
	float compensation;                     //ʱ�Ӳ���ֵ
	float delayTime;                        //�趨���ӳ�ʱ��
	LONGLONG startTime;                     //��ʼʱ��
	double freq;                            //Ƶ��
	EventMsg _msg;                          //������ʱ����Ϣ
};

#endif