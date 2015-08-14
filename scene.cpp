#include "stdafx.h"
#include "scene.h"
#include <stdlib.h>
#include <cassert>
using namespace std;
Scene::Scene(string name) :_name(name), id(0)
{

}

Scene::~Scene()
{

}

void Scene::init()
{
	;
}

void Scene::clean()
{

}

void Scene::update(float dt)
{
	throw 0;
}

bool Scene::sceneMouseEvent(mouseEvent _event)
{
	return false;
}

void Scene::setname(string name)
{
	_name = name;
}

string Scene::getname()
{
	return _name;
}

int Scene::addchild(Sprite* child)
{
	id++;
	child->setid(id);
	_sprites.push_back(child);
	return id;
}


void Scene::removeChildByID(int id)
{
	if (_sprites.size())
	{
		vector<Sprite*>::iterator it = _sprites.begin();
		while (it != _sprites.end())
		{
			if ((*it)->getid() == id)
			{
				it= _sprites.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
	
	if (_keyBoardEventList.size())
	{
		vector<Sprite*>::iterator it = _keyBoardEventList.begin();
		while (it != _keyBoardEventList.end())
		{
			if ((*it)->getid() == id)
			{
				it = _keyBoardEventList.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
	//throw 0;
	if (_mouseEventList.size())
	{
		vector<Sprite*>::iterator it = _mouseEventList.begin();
		while (it != _mouseEventList.end())
		{
			if ((*it)->getid() == id)
			{
				it = _mouseEventList.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
	id = 0;
}

Sprite* Scene::getChildByID(int id)
{
	if (_sprites.size())
	{
		for (vector<Sprite*>::iterator it = _sprites.begin(); it != _sprites.end(); it++)
		{
			if (id == (*it)->getid())//我们找到了对应ID的精灵
				return (*it);
		}
	}
	throw 0;//没找到或者向量为空，抛出异常
}

void Scene::handleMouseEvent(Point pt)
{
	;
}

vector<Sprite*>& Scene::getSpriteList()
{
	return _sprites;
}

void Scene::registerMouseEvent(Sprite* _sprite)
{
	_mouseEventList.push_back(_sprite);
}

void Scene::processMouseEvent(mouseEvent _event)
{
	if (sceneMouseEvent(_event))
	{
		return;
	}
	if (_mouseEventList.size())
	{
		for (vector<Sprite*>::iterator it = _mouseEventList.begin(); it != _mouseEventList.end(); it++)
		{
			if ((*it)->mouseEventCallBack(_event))
				return;                                 //当mouseEventCallBack返回值为真时，判断消息已经被处理完毕
		}
	}
}

void Scene::onKeyPressedCallback(int key)
{
	assert(key < 256);
	_keys[key]=1;
}

void Scene::clearKeys()
{
	for (int i = 0; i < 256; i++)
	{
		_keys[i] = 0;
	}
}