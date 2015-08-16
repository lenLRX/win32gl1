#ifndef __DIRECTOR__H__
#define __DIRECTOR__H__
#include "scene.h"
#include "sprite.h"
#include <vector>
#include <map>
#include "globalvar.h"
#include "mouseevent.h"
#include "event.h"
#include "timer.h"
using namespace std;

enum RunningState
{
	RUNNING,                     //��������
	SLEEPING                     //��������ת״̬
};

Point POINT2Point(POINT pt);

class Director
{
public:
	Director();
	static void create();                    //����ʵ��
	void startWithScene(string name);        //��ʼ��
	static Director* getTheInstance();       //���Ψһʵ��
	void gotoScene(string name);             //ת���¸�����
	Scene* getCurrentScene();                //��õ�ǰ����
	int getTotalScene();                     //��õ�ǰ��������
	void addScene(Scene* theScene);          //���ӳ���
	void setMousePos(POINT mousepos);        //�趨���λ��
	Point getMousePos();                     //��ȡ���λ��
	template <class _func_type>              //
	void registerEvent(Object* obj, _func_type func)
	{
		eventManager.associate(obj, func);
	}
	template <class _func_type>              //
	void unregisterEvent(Object* obj, _func_type func)
	{
		eventManager.disAssociate(obj, func);
	}
	void cleanEvents();
	void raiseEvent(EventMsg msg);
	void raiseMouseEvent(mouseEvent _event); //����һ������¼�              //�׳�һ������¼�
	void registerKey(int key);               //ע������¼�
	void getKeyState();                      //��������¼�
	void tickTimers();                       //�����ʱ��
	void addTimer(timer* _timer);            //����һ����ʱ��
	void cleanAllTimers();                   //ɾ�����м�ʱ��
	void start();                            //��ʼ��Ϸ���趨����flag������Ϸ�̵߳���һ��ѭ��������Ϸ��
	void CheckFlag();                        //���FLAG�Ƿ��ñ仯��Ϊʲô����ô�����أ�http://blog.csdn.net/c__allen/article/details/17687513��
	void reset();                            //����
	void end();                              //������Ϸ�������ת״̬
	void quit();                             //�˳���Ϸ
	void pause();                            //��ͣ
	void resume();                           //����
	void update();                           //���£�ÿ֡����һ�Σ�
	RunningState getState();                 //���״̬
private:
	float FPS;                                //֡��
	float dt;                                 //ÿһ֡��ʱ��(1s/FPS)
	bool shouldStart;                         //�趨Ӧ��������Flag
	bool shouldStop;                          //�趨Ӧ��ֹͣ��Flag
	bool shouldPause;                         //�趨Ӧ����ͣ��Flag
	bool shouldResume;                        //�趨Ӧ�ü�����Flag
	void _start();                            //��������������
	void _end();                               //������Ϸ�������ת״̬
	void _pause();                             //��ͣ
	void _resume();                            //����
	bool inited;                              //��ʼ����־
	static Director* theInstance;             //Ψһʵ��
	map<string, Scene*> _scenes;              //���г���
	Scene* currentScene;                      //ָ��ǰ������ָ��
	vector<int> _keyList;                     //�����İ����б�
	POINT _mousepos;                          //����λ��
	int lastLBUTTONState;                     //�ϴε����״̬�����ж����϶�����̧�����ƶ�
	vector<timer*> timers;                    //��ʱ��
	vector<timer*> timerBuffer;               //��ʱ�������
	Event<void, EventMsg> eventManager;       //�¼�������
	RunningState _state;                      //��Ϸ״̬
};
#endif//__DIRECTOCR__H__