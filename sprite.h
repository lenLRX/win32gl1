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

//精灵类
class Sprite:public Object
{
public:
	Sprite() = delete;                //禁用默认构造函数
	Sprite(string pic,int layer);
	Sprite(GLuint _Texture, int layer);//使用纹理初始化
	~Sprite();                        //析构函数
	int getlayer();                   //获取绘图优先级
	void setlayer(int layer);         //设置绘图优先级
	Point getpos();                   //获得精灵位置
	void setpos(Point pos);           //设置精灵位置
	void setpos(float x, float y);    //设置精灵位置
	Size getsize();                   //获得精灵大小
	void setsize(Size size);          //设置精灵大小
	void setsize(float x, float y);   //设置精灵大小
	void setrotation(float rot);      //设置旋转角度
	float getrotation();              //获得旋转角度
	float getscaleX();                //获得X轴缩放比例
	void setscaleX(float X);          //设置X轴缩放比例
	float getscaleY();                //获得Y轴缩放比例
	void setscaleY(float Y);          //设置Y轴缩放比例
	void setflipX(bool b);            //设置绕X轴翻转
	bool getflipX();                  //获得绕X轴翻转
	void setflipY(bool b);            //设置绕Y轴翻转
	bool getflipY();                  //获得绕Y轴翻转
	void setTex(GLuint t);            //设置纹理ID
	GLuint getTex();                  //获得纹理ID
	void setid(int id);               //设置id
	int getid();                      //获得id
	Point convertToLocalSpace(Point pt);//将点从全局坐标系转换到精灵坐标系
	virtual bool mouseEventCallBack(mouseEvent _event);//鼠标事件回调函数
protected:
	int _layer;                       //绘图优先级
	Point _pos;                       //精灵位置
	Size _size;                       //精灵大小
	GLuint Tex;                       //纹理ID
	float rotation;                   //旋转角度（degree）
	float scaleX;                     //X轴缩放  
	float scaleY;                     //Y轴缩放
	bool flipX;                       //X轴翻转
	bool flipY;                       //Y轴翻转
	int _id;                           //标记每个精灵的id
};
#endif//__SPRITE__H__