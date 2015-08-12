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
class testscene1 :public Scene
{
public:
	testscene1() = delete;
	testscene1(string name);
	~testscene1();
	virtual void init();
	virtual void update(float dt);
	void initPhysics();                        //初始化物理模型
	void testCallback(MouseEventMsg msg);
	void addNewSpriteCallback(MouseEventMsg msg);
private:
	int followSprite;
	b2World* world;
};


#endif//__TESTSCENE1__h__