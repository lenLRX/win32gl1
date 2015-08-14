#ifndef __SIMPLEGAME1__H__
#define __SIMPLEGAME1__H__
#include "scene.h"
#include <Box2D\Box2D.h>
#include <string>
using namespace std;
class simplegame1 :Scene, public b2ContactListener
{
public:
	simplegame1() = delete;
	simplegame1(string name);
	~simplegame1();
	virtual void init();
	virtual void clean();
	virtual void update(float dt);
	virtual void BeginContact(b2Contact* contact);//继承开始碰撞的虚函数
	void initPhysics();                        //初始化物理模型
private:
	int ctrlSprite;
	b2World* world;
};
#endif//__SIMPLEGAME1__H__