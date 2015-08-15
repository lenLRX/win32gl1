#include "stdafx.h"
#include "director.h"

Director* Director::theInstance = NULL;

Director::Director() :inited(false), lastLBUTTONState(0), currentScene(NULL)
{
	
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


void Director::quit()
{
	exit(0);
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
	if (timerBuffer.size())                                    //�ѻ�����еļ�ʱ�����뵽timers�У�����Ӱ���ʱ�����ȣ�
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
			if (!(*it)->isRuning())                       //�����ʱ���Ѿ�������ɾ����
			{
				delete (*it);
				it = timers.erase(it);
			}
			else                                          //�����ʱ���������о͵δ�һ��
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
	//timers.push_back(_timer);�������������ڵ�����ʱ�����Ԫ��
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
}

void Director::reset()
{
	//TODO:�����������
	cleanEvents();
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