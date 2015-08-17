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
	//virtual void pause();                         //暂停
	//virtual void resume();                        //继续
	virtual void BeginContact(b2Contact* contact);//继承开始碰撞的虚函数
	void initPhysics();                           //初始化物理模型
	void shoot(EventMsg msg);                     //发射子弹
private:
	int playerSprite;                             //玩家精灵
	int bulletInTheWorld;                         //已发射的子弹数量
	int maxBulletInTheWorld;                      //可以同时存在最多的子弹数量
	b2Body* playerBody;                           //玩家的物理实体
	b2World* world;
};


#endif//__SIMPLEGAME2__H__