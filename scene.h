#ifndef __SCENE__H__
#define __SCENE__H__
#include "sprite.h"
#include "scene.h"
#include "mouseevent.h"
#include "event.h"
#include <string>
#include <vector>
using namespace std;


class Scene : public Object
{
public:
	Scene()=delete;
	Scene(string name);
	~Scene();
	virtual void init();                      //��ʼ������
	virtual void update(float dt);            //���º�������Ҫÿһ֡����
	virtual void onKeyPressedCallback(int key);//�����ص�����
	virtual bool sceneMouseEvent(mouseEvent _event);//��������¼�����
	void setname(string name);                //��������
	string getname();                         //��ȡ����
	int addchild(Sprite* child);              //���뾫�� ���ظþ����ڱ������е�ID
	void removeChildByID(int id);             //ɾ������
	Sprite* getChildByID(int id);             //��þ���
	void handleMouseEvent(Point pt);          //��Ӧ����¼�
	vector<Sprite*>& getSpriteList();         //��ȡ�����б�
	void registerMouseEvent(Sprite* _sprite);   //ע������¼�
	void processMouseEvent(mouseEvent _event);//��������¼�
	void clearKeys();                         //���
protected:
	string _name;                          //ÿ������Ψһ������
	vector<Sprite*> _sprites;              //���汾�����ľ�����
	vector<Sprite*> _mouseEventList;       //ע��������¼��ľ�����
	vector<Sprite*> _keyBoardEventList;    //ע���˼����¼��ľ���
	int _keys[256];                       //����״̬
	int id;                                //�������ÿ������
};
#endif//__SCENE__H__