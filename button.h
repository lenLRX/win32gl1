#ifndef __BUTTON__H__
#define __BUTTON__H__
#include "sprite.h"
#include "director.h"
enum buttonType
{
	RECTANGLE,
	CIRCLE
};

typedef struct{
	buttonType type;
	float radius;
	Size size;
} buttonInfo;


class Button :public Sprite
{
public:
	Button() = delete;
	Button(string pic, int layer);
	Button(GLuint _Texture, int layer);      //ʹ�������ʼ��
	~Button();                               //��������
	void setType(buttonType type);           //��������
	buttonType getType();                    //�������
	void setRadius(float r);                 //���ð뾶
	float getRadius();                       //��ð뾶
	void setRectSize(Size size);                 //���ô������εĳ���
	Size getRectSize();                          //��ô������εĳ���
	template <class _func_type>              //
	void registerEvent(Object* obj, _func_type func,string name)
	{

		callbackName = name;
		Director::getTheInstance()->registerEvent(obj, func);
	}
	void raiseEvent(EventMsg msg);
	bool mouseEventCallBack(mouseEvent _event);//����¼��ص�����
private:
	string callbackName;
	buttonInfo _buttonInfo;
};
#endif//__BUTTON__H__