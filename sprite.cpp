#include "stdafx.h"
#include "sprite.h"
#include <vector>
#include "globalvar.h"
#include "printText.h"

using namespace std;
Sprite::Sprite(string pic, int layer) \
:_layer(layer), rotation(0.0f), scaleX(1.0f), scaleY(1.0f), flipX(false), flipY(false)
{
	_anchorPoint.x = 0.5;
	_anchorPoint.y = 0.5;
	bool HitCache = false;
	//��һ�������Ƿ��Ѿ�������ͬ����ͼƬ
	for (vector<Texture>::iterator it = Textures.begin();it!=Textures.end();it++)
	{
		if ((*it).name == pic)
		{
			HitCache = true;            //����������ͬ����ͼƬ
			(*it).RefCount++;           
			Tex=(*it).Tex;              //��������
		}
	}

	//���û��ͬ��ͼƬ�����Ǿʹ���һ������
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


//��ȡ��ͼ���ȼ�
int Sprite::getlayer() const
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

Point Sprite::getAnchorPoint()
{
	return _anchorPoint;
}

void Sprite::setAnchorPoint(Point anchorPoint)
{
	_anchorPoint = anchorPoint;
}

void Sprite::setAnchorPoint(float x, float y)
{
	_anchorPoint.x = x;
	_anchorPoint.y = y;
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

Point Sprite::convertToLocalSpace(Point pt)
{
	Point returnPT;
	glLoadIdentity();
	glRotatef(90.0f + rotation / M_PI * 180, 0.0f, 0.0f, 1.0f);
	float mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);                        //����opengl��ͶӰ����������
	/*
	glRasterPos2f(0.65f, 0.8f);
	glPrint("\n%f,%f,%f,%f", mat[0], mat[1], mat[2], mat[3] );
	glRasterPos2f(0.6f, 0.8f);
	glPrint("%f,%f,%f,%f", mat[4], mat[5], mat[6], mat[7]);
	glRasterPos2f(0.55f, 0.8f);
	glPrint("%f,%f,%f,%f", mat[8], mat[9], mat[10], mat[11]);
	glRasterPos2f(0.5f, 0.8f);
	glPrint("%f,%f,%f,%f", mat[12], mat[13], mat[14], mat[15]);
	*/
	returnPT.x = mat[4] * (_pos.x - pt.x) + mat[5] * (_pos.y - pt.y);
	returnPT.y = mat[0] * (_pos.x - pt.x) + mat[1] * (_pos.y - pt.y) ;
	returnPT.y *= -1;
	return returnPT;
}

bool Sprite::mouseEventCallBack(mouseEvent _event)
{
	return false;
}

bool Sprite::operator< (const Sprite& cp)
{
	return this->_layer < cp.getlayer();
}