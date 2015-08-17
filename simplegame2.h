#ifndef __SIMPLEGAME2__H__
#define __SIMPLEGAME2__H__
#include "scene.h"
#include "director.h"
#include "bar.h"
#include "clock.h"
#include <Box2D\Box2D.h>
#include <string>
using namespace std;
class simplegame2 :public Scene, public b2ContactListener
{
public:
	simplegame2() = delete;
	simplegame2(string name);
	~simplegame2();
	virtual void init();
	virtual void clean();
	virtual void update(float dt);
	//virtual void pause();                         //��ͣ
	//virtual void resume();                        //����
	virtual void BeginContact(b2Contact* contact);//�̳п�ʼ��ײ���麯��
	void initPhysics();                           //��ʼ������ģ��
	void shoot(EventMsg msg);                     //�����ӵ�
private:
	int playerSprite;                             //��Ҿ���
	int bulletInTheWorld;                         //�ѷ�����ӵ�����
	int maxBulletInTheWorld;                      //����ͬʱ���������ӵ�����
	b2Body* playerBody;                           //��ҵ�����ʵ��
	b2World* world;
};


#endif//__SIMPLEGAME2__H__