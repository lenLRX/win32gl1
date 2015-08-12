#include "stdafx.h"
#include "sprite.h"
#include <vector>
#include "globalvar.h"

using namespace std;
Sprite::Sprite(string pic, int layer) \
:_layer(layer), rotation(0.0f), scaleX(1.0f), scaleY(1.0f), flipX(false), flipY(false)
{
	bool HitCache = false;
	//看一看我们是否已经储存了同名的图片
	for (vector<Texture>::iterator it = Textures.begin();it!=Textures.end();it++)
	{
		if ((*it).name == pic)
		{
			HitCache = true;            //我们碰到了同名的图片
			(*it).RefCount++;           
			Tex=(*it).Tex;              //设置纹理
		}
	}

	//如果没有同名图片，我们就创建一个纹理
	if (!HitCache)
	{
		Texture temp;
		temp.name = pic.c_str();
		temp.RefCount = 1;
		glGenTextures(1,&temp.Tex);
		InitTexture(temp.Tex, temp.name.c_str(), PNG);
		Tex = temp.Tex;
		Textures.push_back(temp);
	}
}

Sprite::Sprite(GLuint _Texture, int layer) \
: _layer(layer), rotation(0.0f), scaleX(1.0f), scaleY(1.0f), flipX(false), flipY(false)
{
	Tex = _Texture;
}

Sprite::~Sprite()
{
	;
}


//获取绘图优先级
int Sprite::getlayer()
{
	return _layer;
}

void Sprite::setlayer(int layer)
{
	_layer = layer;
}

void Sprite::setpos(Point pos)
{
	_pos = pos;
}

Point Sprite::getpos()
{
	return _pos;
}

void Sprite::setpos(float x, float y)
{
	_pos.x = x;
	_pos.y = y;
}

Size Sprite::getsize()
{
	return _size;
}

void Sprite::setsize(Size size)
{
	_size = size;
}

void Sprite::setsize(float x,float y)
{
	_size.width=x;
	_size.height = y;
}

void Sprite::setrotation(float rot)
{
	rotation = rot;
}

float Sprite::getrotation()
{
	return rotation;
}

float Sprite::getscaleX()
{
	return scaleX;
}

void Sprite::setscaleX(float X)
{
	scaleX = X;
}

float Sprite::getscaleY()
{
	return scaleY;
}

void Sprite::setscaleY(float Y)
{
	scaleY = Y;
}

void Sprite::setflipX(bool b)
{
	flipX = b;
}

bool Sprite::getflipX()
{
	return flipX;
}

void Sprite::setflipY(bool b)
{
	flipY = b;
}

bool Sprite::getflipY()
{
	return flipY;
}

void Sprite::setTex(GLuint t)
{
	Tex = t;
}

GLuint Sprite::getTex()
{
	return Tex;
}

void Sprite::setid(int id)
{
	_id = id;
}

int Sprite::getid()
{
	return _id;
}

bool Sprite::mouseEventCallBack(mouseEvent evet)
{
	return false;
}