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
	virtual void init();                      //初始化场景
	virtual void update(float dt);            //更新函数，需要每一帧调用
	virtual void onKeyPressedCallback(int key);//按键回调函数
	virtual bool sceneMouseEvent(mouseEvent _event);//场景鼠标事件处理
	void setname(string name);                //设置名字
	string getname();                         //获取名字
	int addchild(Sprite* child);              //加入精灵 返回该精灵在本场景中的ID
	void removeChildByID(int id);             //删除精灵
	Sprite* getChildByID(int id);             //获得精灵
	void handleMouseEvent(Point pt);          //响应鼠标事件
	vector<Sprite*>& getSpriteList();         //获取精灵列表
	void registerMouseEvent(Sprite* _sprite);   //注册鼠标事件
	void processMouseEvent(mouseEvent _event);//处理鼠标事件
	void clearKeys();                         //清空
protected:
	string _name;                          //每个场景唯一的名字
	vector<Sprite*> _sprites;              //保存本场景的精灵们
	vector<Sprite*> _mouseEventList;       //注册了鼠标事件的精灵们
	vector<Sprite*> _keyBoardEventList;    //注册了键盘事件的精灵
	int _keys[256];                       //按键状态
	int id;                                //用来标记每个精灵
};
#endif//__SCENE__H__