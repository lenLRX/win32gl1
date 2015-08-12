#ifndef __DATASTRUCT__H__
#define __DATASTRUCT__H__
#include <string>
using namespace std;

typedef struct
{
	float x;
	float y;
}Point;


typedef struct
{
	float height;
	float width;
}Size;

typedef struct
{
	int RefCount;
	GLuint Tex;
	string name;
}Texture;

enum picType
{
	PNG
};
#endif//__DATASTRUCT__H__