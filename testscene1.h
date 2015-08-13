#ifndef __TESTSCENE1__H__
#define __TESTSCENE1__H__
#include "scene.h"
#include "event.h"
#include <stdlib.h>
#include <time.h>
#include <Box2D\Box2D.h>
#include <string>
#include <cstdio>

#define PTM_RATIO 32

using namespace std;
class testscene1 :public Scene,public b2ContactListener
{
public:
	testscene1() = delete;
	testscene1(string name);
	~testscene1();
	virtual void init();
	virtual void update(float dt);
	virtual void BeginContact(b2Contact* contact);//�̳п�ʼ��ײ���麯��
	void initPhysics();                        //��ʼ������ģ��
	void testCallback(EventMsg msg);
	void addNewSpriteCallback(EventMsg msg);   //���һ�·���һ������
	void removeAllSprites(EventMsg msg);       //ɾ�����о���
private:
	int followSprite;
	int coin;                                  //���мӷֵĽ��
	b2World* world;
};


#endif//__TESTSCENE1__h__