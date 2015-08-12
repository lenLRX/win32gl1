#include "stdafx.h"
#include "button.h"

Button::Button(string pic, int layer) :Sprite(pic, layer)
{

}

Button::Button(GLuint _Texture, int layer) : Sprite(_Texture, layer)
{

}

Button::~Button()
{

}

void Button::setType(buttonType type)
{
	_buttonInfo.type = type;
}

buttonType Button::getType()
{
	return _buttonInfo.type;
}

void Button::setRadius(float r)
{
	_buttonInfo.radius = r;
}

float Button::getRadius()
{
	return _buttonInfo.radius;
}

bool Button::mouseEventCallBack(mouseEvent evet)
{

}