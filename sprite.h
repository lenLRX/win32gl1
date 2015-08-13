#ifndef __SPRITE__H__
#define __SPRITE__H__
#include <gl\gl.h> 
#include <gl\glu.h> 
#include <string>
#include "datastruct.h"
#include "loadpng.h"
#include "mouseevent.h"
#include "event.h"

using namespace std;

//������
class Sprite:public Object
{
public:
	Sprite() = delete;                //����Ĭ�Ϲ��캯��
	Sprite(string pic,int layer);
	Sprite(GLuint _Texture, int layer);//ʹ�������ʼ��
	~Sprite();                        //��������
	int getlayer();                   //��ȡ��ͼ���ȼ�
	void setlayer(int layer);         //���û�ͼ���ȼ�
	Point getpos();                   //��þ���λ��
	void setpos(Point pos);           //���þ���λ��
	void setpos(float x, float y);    //���þ���λ��
	Size getsize();                   //��þ����С
	void setsize(Size size);          //���þ����С
	void setsize(float x, float y);   //���þ����С
	void setrotation(float rot);      //������ת�Ƕ�
	float getrotation();              //�����ת�Ƕ�
	float getscaleX();                //���X�����ű���
	void setscaleX(float X);          //����X�����ű���
	float getscaleY();                //���Y�����ű���
	void setscaleY(float Y);          //����Y�����ű���
	void setflipX(bool b);            //������X�ᷭת
	bool getflipX();                  //�����X�ᷭת
	void setflipY(bool b);            //������Y�ᷭת
	bool getflipY();                  //�����Y�ᷭת
	void setTex(GLuint t);            //��������ID
	GLuint getTex();                  //�������ID
	void setid(int id);               //����id
	int getid();                      //���id
	Point convertToLocalSpace(Point pt);//�����ȫ������ϵת������������ϵ
	virtual bool mouseEventCallBack(mouseEvent _event);//����¼��ص�����
protected:
	int _layer;                       //��ͼ���ȼ�
	Point _pos;                       //����λ��
	Size _size;                       //�����С
	GLuint Tex;                       //����ID
	float rotation;                   //��ת�Ƕȣ�degree��
	float scaleX;                     //X������  
	float scaleY;                     //Y������
	bool flipX;                       //X�ᷭת
	bool flipY;                       //Y�ᷭת
	int _id;                           //���ÿ�������id
};
#endif//__SPRITE__H__