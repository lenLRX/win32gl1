#include "stdafx.h"
#include "director.h"
#include "testscene1.h"
#include "menuscene.h"
#include "simplegame1.h"
#include "simplegame2.h"
extern bool shouldRun;
extern void initDrawing();
extern bool openglInited;

Director* Director::theInstance = NULL;

Director::Director() :\
inited(false), lastLBUTTONState(0), currentScene(NULL), _state(SLEEPING)\
, shouldStart(false),shouldStop(false),shouldPause(false),shouldResume(false), FPS(60.0f)
{
	dt = 1 / FPS;
}

void Director::create()
{
	if (!theInstance)
	    theInstance = new Director();
}

void Director::startWithScene(string name)
{
	currentScene = _scenes[name];
	currentScene->init();
	inited = true;
	_state = RUNNING;
}

Director* Director::getTheInstance()
{
	return theInstance;
}

void Director::gotoScene(string name)
{
	if (currentScene)
		currentScene->clean();
	cleanEvents();
	cleanAllTimers();
	currentScene = _scenes[name];
	currentScene->init();
}


Scene* Director::getCurrentScene()
{
	return currentScene;
}

int Director::getTotalScene()
{
	return _scenes.size();
}

void Director::addScene(Scene* theScene)
{
	_scenes.insert(pair<string, Scene*>(theScene->getname(), theScene));
}

void Director::setMousePos(POINT mousepos)
{
	_mousepos = mousepos;
	if (_mousepos.x < 0)
		_mousepos.x = 0;
	if (_mousepos.y < 0)
		_mousepos.y = 0;
	if (_mousepos.x > WINDOW_WIDTH)
		_mousepos.x = WINDOW_WIDTH;
	if (_mousepos.y > WINDOW_HEIGHT)
		_mousepos.y = WINDOW_HEIGHT;
	_mousepos.y = WINDOW_HEIGHT - _mousepos.y;
}

Point Director::getMousePos()
{
	return POINT2Point(_mousepos);
}

void Director::registerKey(int key)
{
	_keyList.push_back(key);
}

void Director::getKeyState()
{
	getCurrentScene()->clearKeys();
	if (_keyList.size())
	{
		for (vector<int>::iterator it = _keyList.begin(); it != _keyList.end(); it++)
		{
			if (GetAsyncKeyState((*it)) & 0x8000)
			{
				getCurrentScene()->onKeyPressedCallback((*it));
			}

		}
	}
	int LBUTTONState = GetAsyncKeyState(VK_LBUTTON) & 0x8000;
	mouseEvent _event;
	
	if (LBUTTONState)
	{
		if (lastLBUTTONState)
		{
			_event.type = DRAG;
		}
		else
		{
			_event.type = DOWN;
		}
	}
	else
	{
		if (lastLBUTTONState)
		{
			_event.type = UP;
		}
		else
		{
			_event.type = MOVE;
		}
	}
	_event.point = POINT2Point(_mousepos);
	lastLBUTTONState = LBUTTONState;
	EventMsg msg;
	msg._event = _event;
	msg.name = "test";
	raiseEvent(msg);
	raiseMouseEvent(_event);
	
}

void Director::tickTimers()
{
	if (timerBuffer.size())                                    //把缓冲池中的计时器加入到timers中（并不影响计时器精度）
	{
		vector<timer*>::iterator it = timerBuffer.begin();
		while (it != timerBuffer.end())
		{
			timers.push_back((*it));
			it++;
		}
	}
	timerBuffer.clear();
	if (timers.size())
	{
		vector<timer*>::iterator it = timers.begin();
		while (it != timers.end())
		{
			if (!(*it)->isRuning())                       //如果计时器已经触发就删除它
			{
				delete (*it);
				it = timers.erase(it);
			}
			else                                          //如果计时器正在运行就滴答一下
			{
				
				(*it)->tick();
				++it;
			}
		}
	}
}

void Director::addTimer(timer* _timer)  
{
	_timer->start();
	//timers.push_back(_timer);不能在容器正在迭代的时候插入元素
	timerBuffer.push_back(_timer);
}

void Director::cleanAllTimers()
{
	if (timers.size())
	{
		vector<timer*>::iterator it = timers.begin();
		while (it != timers.end())
		{
		    delete (*it);
			it++;
		}
		timers.clear();
	}
	if (timerBuffer.size())
	{
		vector<timer*>::iterator it = timerBuffer.begin();
		while (it != timerBuffer.end())
		{
			delete (*it);
			it++;
		}
		timerBuffer.clear();
	}
}

void Director::reset()
{
	//TODO:增加清理代码
	cleanAllTimers();
	cleanEvents();
	if (_scenes.size())
	{
		for (map<string, Scene*>::iterator it = _scenes.begin(); it != _scenes.end();)
		{
			delete (*it).second;
			it = _scenes.erase(it);
		}
	}
	currentScene = NULL;
	_keyList.clear();
	_state = SLEEPING;
}

void Director::cleanEvents()
{
	eventManager.clean();
}

void Director::raiseEvent(EventMsg msg)
{
	eventManager.sendEvent(msg);
}

void Director::raiseMouseEvent(mouseEvent _event)
{
	getCurrentScene()->processMouseEvent(_event);
}

Point POINT2Point(POINT pt)
{
	Point pt2;
	pt2.x = pt.x;
	pt2.y = pt.y;
	return pt2;
}

RunningState Director::getState()
{
	return _state;
}

void Director::start()
{
	if (_state==SLEEPING)
	    shouldStart = true;
}

void Director::CheckFlag()
{
	if (shouldStart)
	{
		_start();
	}
	if (shouldStop)
	{
		_end();
	}
	if (shouldPause)
	{
		_pause();
	}
	if (shouldResume)
	{
		_resume();
	}
}

void Director::_start()
{
	shouldStart = false;
	_state = RUNNING;
	///////////////////////////////////////////
	//在此加载场景
	Scene* p = (Scene*)new testscene1("test");
	Scene* p2 = (Scene*)new menuScene("menu");
	Scene* p3 = (Scene*)new simplegame1("game1");
	Scene* p4 = (Scene*)new simplegame2("game2");
	Director::getTheInstance()->addScene(p2);
	Director::getTheInstance()->addScene(p);
	Director::getTheInstance()->addScene(p3);
	Director::getTheInstance()->addScene(p4);
	Director::getTheInstance()->startWithScene("game2");
}

void Director::end()
{
	shouldStop = true;
}

void Director::_end()
{
	shouldStop = false;
	reset();
	_state = SLEEPING;
}

void Director::quit()
{
	shouldRun = false;
}

void Director::pause()
{
	shouldPause = true;
}

void Director::_pause()
{
	shouldPause = false;
	if (timers.size())
	{
		for (vector<timer*>::iterator it = timers.begin(); it != timers.end(); ++it)
		{
			(*it)->pause();
		}
	}
	if (timerBuffer.size())
	{
		for (vector<timer*>::iterator it = timerBuffer.begin(); it != timerBuffer.end(); ++it)
		{
			(*it)->pause();
		}
	}
	currentScene->pause();
	dt = 0.0f;
}

void Director::resume()
{
	shouldResume = true;
}

void Director::_resume()
{
	shouldResume = false;
	if (timers.size())
	{
		for (vector<timer*>::iterator it = timers.begin(); it != timers.end(); ++it)
		{
			(*it)->resume();
		}
	}
	if (timerBuffer.size())
	{
		for (vector<timer*>::iterator it = timerBuffer.begin(); it != timerBuffer.end(); ++it)
		{
			(*it)->resume();
		}
	}
	currentScene->resume();
	dt = 1 / FPS;
}

void Director::update()
{
	currentScene->update(dt);
}