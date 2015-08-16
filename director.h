#ifndef __DIRECTOR__H__
#define __DIRECTOR__H__
#include "scene.h"
#include "sprite.h"
#include <vector>
#include <map>
#include "globalvar.h"
#include "mouseevent.h"
#include "event.h"
#include "timer.h"
using namespace std;

enum RunningState
{
	RUNNING,                     //正常运行
	SLEEPING                     //黑屏，空转状态
};

Point POINT2Point(POINT pt);

class Director
{
public:
	Director();
	static void create();                    //创建实例
	void startWithScene(string name);        //初始化
	static Director* getTheInstance();       //获得唯一实例
	void gotoScene(string name);             //转到下个场景
	Scene* getCurrentScene();                //获得当前场景
	int getTotalScene();                     //获得当前场景总数
	void addScene(Scene* theScene);          //增加场景
	void setMousePos(POINT mousepos);        //设定鼠标位置
	Point getMousePos();                     //获取鼠标位置
	template <class _func_type>              //
	void registerEvent(Object* obj, _func_type func)
	{
		eventManager.associate(obj, func);
	}
	template <class _func_type>              //
	void unregisterEvent(Object* obj, _func_type func)
	{
		eventManager.disAssociate(obj, func);
	}
	void cleanEvents();
	void raiseEvent(EventMsg msg);
	void raiseMouseEvent(mouseEvent _event); //发出一个鼠标事件              //抛出一个鼠标事件
	void registerKey(int key);               //注册键盘事件
	void getKeyState();                      //处理键盘事件
	void tickTimers();                       //处理计时器
	void addTimer(timer* _timer);            //加入一个计时器
	void cleanAllTimers();                   //删除所有计时器
	void start();                            //开始游戏（设定启动flag，在游戏线程的下一个循环启动游戏）
	void CheckFlag();                        //检查FLAG是否用变化（为什么搞这么复杂呢，http://blog.csdn.net/c__allen/article/details/17687513）
	void reset();                            //重置
	void end();                              //结束游戏，进入空转状态
	void quit();                             //退出游戏
	void pause();                            //暂停
	void resume();                           //继续
	void update();                           //更新（每帧调用一次）
	RunningState getState();                 //获得状态
private:
	float FPS;                                //帧率
	float dt;                                 //每一帧的时间(1s/FPS)
	bool shouldStart;                         //设定应该启动的Flag
	bool shouldStop;                          //设定应该停止的Flag
	bool shouldPause;                         //设定应该暂停的Flag
	bool shouldResume;                        //设定应该继续的Flag
	void _start();                            //真正的启动函数
	void _end();                               //结束游戏，进入空转状态
	void _pause();                             //暂停
	void _resume();                            //继续
	bool inited;                              //初始化标志
	static Director* theInstance;             //唯一实例
	map<string, Scene*> _scenes;              //所有场景
	Scene* currentScene;                      //指向当前场景的指针
	vector<int> _keyList;                     //监听的按键列表
	POINT _mousepos;                          //鼠标的位置
	int lastLBUTTONState;                     //上次的鼠标状态用来判断是拖动按下抬起还是移动
	vector<timer*> timers;                    //计时器
	vector<timer*> timerBuffer;               //计时器缓冲池
	Event<void, EventMsg> eventManager;       //事件管理者
	RunningState _state;                      //游戏状态
};
#endif//__DIRECTOCR__H__