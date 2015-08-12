#ifndef __MOUSEEVENT__H__
#define __MOUSEEVENT__H__
#include "stdafx.h"
#include "datastruct.h"
enum mouseEventType
{
	DOWN,//�������
	UP,//̧�����
	MOVE,//�ƶ����
	DRAG//�϶����
};

typedef struct
{
	mouseEventType type;
	Point point;
}mouseEvent;


#endif//__MOUSEEVENT__H__