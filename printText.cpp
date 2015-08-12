#include "stdafx.h"
#include "printText.h"

GLuint	base;			// �����������ʾ�б�Ŀ�ʼλ��

GLfloat	cnt1;			// �����ƶ�������1

GLfloat	cnt2;			// �����ƶ�������2

GLvoid BuildFont(HDC hDC)						// ����λͼ����

{

	HFONT	font;						// ������

	HFONT	oldfont;						// �ɵ�������



	base = glGenLists(96);					// ����96����ʾ�б�
	font = CreateFont(-24,					// ����߶�
		0,				// ������
		0,				// �������ת�Ƕ� Angle Of Escapement
		0,				// ������ߵ���ת�Ƕ�Orientation Angle
		FW_BOLD,				// ���������
		FALSE,				// �Ƿ�ʹ��б��

		FALSE,				// �Ƿ�ʹ���»���

		FALSE,				// �Ƿ�ʹ��ɾ����
		ANSI_CHARSET,			// �����ַ���
		OUT_TT_PRECIS,			// �������
		CLIP_DEFAULT_PRECIS,		// �ü�����
		ANTIALIASED_QUALITY,		// �������
		FF_DONTCARE | DEFAULT_PITCH,		// Family And Pitch
		L"Courier New");			// ��������

	oldfont = (HFONT)SelectObject(hDC, font);			// ѡ��������Ҫ������

	wglUseFontBitmaps(hDC, 32, 96, base);			// ����96����ʾ�б����ƴ�ASCII��Ϊ32-128���ַ�

	SelectObject(hDC, oldfont);					// ѡ��ԭ��������

	DeleteObject(font);					// ɾ������
}


GLvoid KillFont(GLvoid)						// ɾ����ʾ�б�

{

	glDeleteLists(base, 96);					//ɾ��96����ʾ�б�

}

GLvoid glPrint(const char *fmt, ...)					// �Զ���GL������庯��

{
	char		text[256];				// �������ִ�

	va_list		ap;					// ָ��һ�������б��ָ��

	if (fmt == NULL)						// ����������򷵻�
		return;
	va_start(ap, fmt);						// �����ɱ����

	vsprintf(text, fmt, ap);				// �Ѳ���ֵд���ַ���

	va_end(ap);
	glPushAttrib(GL_LIST_BIT);					// ����ʾ�б�����ѹ�����Զ�ջ

	glListBase(base - 32);					// ������ʾ�б�Ļ���ֵ

	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);		// ������ʾ�б�����ַ���

	glPopAttrib();						// �������Զ�ջ

}
