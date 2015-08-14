#ifndef __EVENT__H__
#define __EVENT__H__

//������ѡ�� ������  /vmg !!!!!!!!!!!!



#include <vector>
#include <algorithm>
#include <string>
#include "mouseevent.h"
using namespace std;
//
/*----------------------------------------------------------------*/
/* class Object   ��Ӧ�¼�������������Ǵ�Object��������          */
/*----------------------------------------------------------------*/

typedef struct
{
	string name;
	mouseEvent _event;
	Point point;
	Size size;
	float param;
} EventMsg;

class Object
{
};

/*----------------------------------------------------------------*/
/* class Event     ģ�����Ϊ �������� ����Ӧ������������         */
/* ��ʵ��һ���������¼���Ӧ����                                   */
/*----------------------------------------------------------------*/

template<typename rtnTtpe, typename ArgType>
class Event
{
	//ʹÿ���¼���������Ӧ�ĺ�������
#define EVENT_LIST_MAX_NUM  (100)
	typedef rtnTtpe(Object::*pMemFunc)(ArgType arg);

public:
	Event()
	{
		m_totalFunc = 0;
		for (int i = 0; i < EVENT_LIST_MAX_NUM; i++)
		{
			m_objs[i] = NULL;
			m_func[i] = NULL;
		}
	}

	//�����ص���Ա����
	template <class _func_type>
	void associate(Object *obj, _func_type func)
	{
		m_objs[m_totalFunc] = obj;
		m_func[m_totalFunc] = static_cast<pMemFunc> (func);
		m_totalFunc++;
	}
	//ɾ���¼������ص���Ա����
	template <class _func_type>
	void disAssociate(Object *obj, _func_type func)
	{
		if (obj != m_obj)
		{
			return;
		}

		//����
		for (int i = 0; i < m_totalFunc; i++)
		{
			if (m_func[i] == func)
			{
				break;
			}
		}

		//�ƶ�ɾ��
		for (i; i < m_totalFunc - 1; i++)
		{
			m_objs[i] = m_objs[i + 1];
			m_func[i] = m_func[i + 1];
		}

		m_func[i] = NULL;
		m_objs[i] = NULL;
		m_totalFunc--;
	}

	//ִ�й����Ļص�����
	void sendEvent(ArgType arg)
	{
		for (int i = 0; i < m_totalFunc; i++)
		{
			if (m_func[i] != NULL&&m_objs[i] != NULL)
			{
				((m_objs[i]->*pMemFunc(m_func[i])))(arg);
			}
		}
	}
	void clean()
	{
		m_totalFunc = 0;
		for (int i = 0; i < EVENT_LIST_MAX_NUM; i++)
		{
			m_objs[i] = NULL;
			m_func[i] = NULL;
		}
	}
private:
	Object* m_objs[EVENT_LIST_MAX_NUM];
	pMemFunc m_func[EVENT_LIST_MAX_NUM];
	int m_totalFunc;
};

#endif//__EVENT__H__