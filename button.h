#ifndef __BUTTON__H__
#define __BUTTON__H__
#include "sprite.h"

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
	void setSize(Size size);                 //���ô������εĳ���
	Size getSize();                          //��ô������εĳ���
	bool mouseEventCallBack(mouseEvent evet);//����¼��ص�����
private:
	buttonInfo _buttonInfo;
};
#endif//__BUTTON__H__