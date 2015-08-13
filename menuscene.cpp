#include "stdafx.h"
#include "menuscene.h"
#include "button.h"
using namespace std;

menuScene::menuScene(string name) :Scene(name)
{
	init();
}

menuScene::~menuScene()
{

}

void menuScene::init()
{
	Sprite* S1 = new Sprite("HelloWorld.png", 0);   //������������
	Button* btn = new Button("CloseNormal.png", 0);  //������ť
	S1->setflipY(true);                             //�������ҷ�ת
	S1->setsize(WINDOW_HEIGHT, WINDOW_WIDTH);
	S1->setpos(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	addchild(S1);
	btn->setsize(100, 100);
	btn->setpos(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	btn->setType(CIRCLE);
	btn->setRadius(50);
	btn->registerEvent(this, &menuScene::gotoNextScene, "NextScene");
	addchild(btn);
	registerMouseEvent(btn);
}

void menuScene::update(float dt)
{

}

void menuScene::gotoNextScene(EventMsg msg)
{
	if (msg.name == "NextScene")
	{
		Director::getTheInstance()->gotoNextScene();
	}
}