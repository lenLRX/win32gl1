#ifndef __DIRECTOR__H__
#define __DIRECTOR__H__
#include "scene.h"
#include "sprite.h"
#include <vector>
#include <queue>
#include "globalvar.h"
#include "mouseevent.h"
#include "event.h"
using namespace std;

Point POINT2Point(POINT pt);

class Director
{
public:
	Director();
	static void create();                    //����ʵ��
	void init();                             //��ʼ��
	static Director* getTheInstance();       //���Ψһʵ��
	void gotoNextScene();                    //ת���¸�����
	void quit();                             //�˳���Ϸ
	Scene* getCurrentScene();                 //��õ�ǰ����
	int getTotalScene();                     //��õ�ǰ��������
	void addScene(Scene* theScene);           //���ӳ���
	void setMousePos(POINT mousepos);        //�趨���λ��
	Point getMousePos();                     //��ȡ���λ��
	template <class _func_type>              //
	void registMouseEvent(Object* obj, _func_type func)
	{
		eventManager.associate(obj, func);
	}
	void raiseMouseEvent(mouseEvent _event); //����һ������¼�              //�׳�һ������¼�
	void registKey(int key);                 //ע������¼�
	void getKeyState();                      //��������¼�
	void reset();                            //����
private:
	bool inited;                               //��ʼ����־
	static Director* theInstance;             //Ψһʵ��
	vector<Scene*> _scenes;                   //���г���
	vector<Scene*>::iterator currentScene;    //ָ��ǰ�����ĵ�����
	vector<int> _keyList;                     //�����İ����б�
	POINT _mousepos;                          //����λ��
	int lastLBUTTONState;                     //�ϴε����״̬�����ж����϶�����̧�����ƶ�
	Event<void, MouseEventMsg> eventManager;  //�¼�������

};
#endif//__DIRECTOCR__H__