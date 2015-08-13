#ifndef __MENUSCENE__H__
#define __MENUSCENE__H__
#include "scene.h"
class menuScene :public Scene
{
public:
	menuScene() = delete;
	menuScene(string name);
	~menuScene();
	virtual void init();
	virtual void update(float dt);
	void gotoNextScene(EventMsg msg);
};
#endif//__MENUSCENE__H__