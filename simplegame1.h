#ifndef __SIMPLEGAME1__H__
#define __SIMPLEGAME1__H__
#include "scene.h"
#include "director.h"
#include "bar.h"
#include "clock.h"
#include <Box2D\Box2D.h>
#include <string>
using namespace std;
class simplegame1 :public Scene, public b2ContactListener
{
public:
	simplegame1() = delete;
	simplegame1(string name);
	~simplegame1();
	virtual void init();
	virtual void clean();
	virtual void update(float dt);
	virtual void BeginContact(b2Contact* contact);//�̳п�ʼ��ײ���麯��
	void initPhysics();                           //��ʼ������ģ��
	void addAlert(EventMsg msg);                  //��Ӿ���
	void addNewBullet(EventMsg msg);              //�����µ��ӵ�
	void damaged();                               //����
private:
	Bar* testbar;                                 //Ѫ��
	float score;                                  //����
	int playerSprite;                             //��Ҿ���
	int alertSprite;                              //��������
	float life;                                   //����ֵ
	float damage;                                 //ÿ�α������Ժ���˺�ֵ
	Clock _clock;                                 //�Ʒ��õ�ʱ��
	b2Body* playerBody;                           //��ҵ�����ʵ��
	b2World* world;
};
#endif//__SIMPLEGAME1__H__