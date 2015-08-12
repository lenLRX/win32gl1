// win32gl1.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "win32gl1.h"
#include "printText.h"
#include "loadpng.h"
#include "gamelogic.h"
#include "director.h"
#include "testscene1.h"
#include <cmath>
using namespace std;

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HDC hDC;
PIXELFORMATDESCRIPTOR  pfd;
HGLRC ghRC;
bool pauseFlag;
bool openglInited = false;
LPDWORD DrawingThread = NULL;
HANDLE DrawingThreadHANDLE = NULL;
HWND hWnd;
float FPS = 60;
float LastCycleTime = 0.01;//��һ֡��ʱ��
POINT mousepos;//���λ��
char lastPressedKey = '\0';




// �˴���ģ���а����ĺ�����ǰ������: 
void  SceneShow(GLvoid);

void  SceneInit(int w,int h);

void openglInit();//��ʼ��OPENGL

void showFPS();//��ʾFPS

void setFPS(float fps);//����FPS

void getLastCycleTime();//�����һ֡��ʱ�䣨ע�⣡ÿ��ѭ��ֻ�ܵ���һ�Σ�������

void getKeyBoardState();


DWORD WINAPI  DrawingLoop(LPVOID lpParameter);

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  �ڴ˷��ô��롣

	pauseFlag = false;

	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32GL1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32GL1));

	// ����Ϣѭ��: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_SAVEBITS;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32GL1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32GL1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassEx(&wcex);
}

//
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	Director::create();
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
   //���ô��ڴ�С
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW&~WS_THICKFRAME,
      200, 200, WINDOW_WIDTH+16, WINDOW_HEIGHT+60, NULL, NULL, hInstance, NULL);
   //~WS_THICKFRAME��ֹ�ı䴰�ڴ�С
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	

	switch (message)
	{
	case WM_COMMAND:
		SceneShow();
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_PAUSE:
			pauseFlag = true;
			break;
		case IDM_RESUME:
			pauseFlag = false;
			break;
		case IDM_START:
			if (!DrawingThreadHANDLE)
				DrawingThreadHANDLE=CreateThread(NULL, 0, DrawingLoop, NULL, 0, DrawingThread);
			break;
		case IDM_END:
			if(!TerminateThread(DrawingThreadHANDLE, 0))
				MessageBox(NULL, L"�����̴߳���", L"����", MB_OK | MB_ICONEXCLAMATION);
			else
				MessageBox(NULL, L"���������߳�", L"��Ϣ", MB_OK | MB_ICONEXCLAMATION);
			DrawingThreadHANDLE = NULL;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		// TODO:  �ڴ���������ͼ����...
		
		break;
	case WM_DESTROY:
		TerminateThread(DrawingThreadHANDLE, 0);
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:

		break;
	case WM_CHAR:
		lastPressedKey = wParam;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


//OpenGL ��ʼ����ʼ 

void  SceneInit(int  w, int  h)

{
	BuildFont(hDC);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);        //   ��ɫ���� 

	glColor3f(1.0f, 1.0f, 1.0f);



	//glShadeModel(GL_FLAT);

	//glMatrixMode(GL_MODELVIEW);

	//glLoadIdentity();

	//glOrtho(-50.0f, 50.0f, -50.0f, 50.0f, -10.0f, 10.0f);
	
}



//  ����������еĻ�ͼ���� 

void  SceneShow(GLvoid)

{

	GetCursorPos(&mousepos);//������λ��

	getLastCycleTime();//ÿ֡����һ�¼�ʱ��

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	

	update(0.1f);
	if (Director::getTheInstance()->getTotalScene())
	{
		Director::getTheInstance()->getKeyState();
		Scene* thescene = Director::getTheInstance()->getCurrentScene();
		thescene->update(1/60.0);
		int i = 0;
		//glPrint(" %s", thescene.getname().c_str());
		for (vector<Sprite*>::iterator it = thescene->getSpriteList().begin(); it != thescene->getSpriteList().end(); it++)
		{
			i++;
			int flipXFlag = 1;
			int flipYFlag = 1;
			Point origin = (*it)->getpos();
			Size size = (*it)->getsize();
			float rot = (*it)->getrotation();
			static float rotf = 0.0f;
			rotf += 2.0f;
			glLoadIdentity();
			
			//glRotatef((*it)->getrotation(), 0.0f, 0.0f, 1.0f);      //��Z����ת
			//glTranslatef(1.0f, -1.0f, 0.0f);                        //Ϊ�˷��㽫����ϵԭ��ת�������½�
			//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);                     //Ϊʲôͼ��Ҫ���ŵģ���Ҳ����

			
			//glTranslatef(-size.width / WINDOW_WIDTH / 2, -size.height / WINDOW_HEIGHT/2, 0.0f); //����ϵԭ��������ԭ���غ�
			
			//glRotatef(-rot, 0.0f, 0.0f, 1.0f);
			float dx, dy;
			if (rot)
			{
				
				float wPrime = origin.x / WINDOW_WIDTH * 2 - 1;
				float hPrime = origin.y / WINDOW_HEIGHT * 2 - 1;

				dy = hPrime*(wPrime - hPrime / tan(rot / 180 * M_PI)) / (hPrime / tan(rot / 180 * M_PI));

				dx = cos(rot / 180 * M_PI)*(wPrime + hPrime*tan(rot / 180 * M_PI));
			}
			else
			{
				dx = 0;
				dy=0;
			}
			

			//glTranslatef(dx, -dy, 0.0f);
			//glPrint("%f %f", dx, dy);

			float r = sqrt(size.width*size.width + size.height*size.height);

			//glTranslatef((origin.x + size.width / 2) / WINDOW_WIDTH * 2 - 1, (origin.y + size.height/2) / WINDOW_HEIGHT * 2 - 1, 0.0f);
			glRotatef(90.0f+rotf, 0.0f, 0.0f, 1.0f);
			//glViewport(origin.x - r / 2, origin.y-r/2, r, r);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_TEXTURE_2D);
			glMatrixMode(GL_MODELVIEW);
			
			if ((*it)->getflipX())                                  //���ҷ�ת
			{
				glTranslatef(size.width / WINDOW_WIDTH, 1.0f, 0.0f);
				glRotatef(180.0f, 1.0f, 0.0f, 0.0f);               
				glTranslatef(-size.width / WINDOW_WIDTH, -1.0f, 0.0f);
				flipXFlag = -1;
			}
				
			if ((*it)->getflipY())                                  //���·�ת
			{
				glTranslatef(size.height / WINDOW_HEIGHT, 0.0f, 0.0f);
				glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
				glTranslatef(-size.height / WINDOW_HEIGHT, 0.0f, 0.0f);
				flipYFlag = -1;
			}
			origin.x *= -1 * flipYFlag;
			origin.y *= flipXFlag;
			glBindTexture(GL_TEXTURE_2D, (*it)->getTex());          //�������
			glBegin(GL_POLYGON);
			//_pos.x = -y;
			//_pos.y = x;
			//float r = sqrtf(size.width  * size.width  + size.height * size.height)/2;
			//- size.height / 2 + cos((rot+45)/180.0*M_PI)*r
			/*
			glTexCoord2f(0.0f, 0.0f); glVertex3f((origin.y ) / WINDOW_HEIGHT * 2, 2 - (-origin.x) / WINDOW_WIDTH * 2, 0.0f);    //����
			glTexCoord2f(0.0f, 1.0f); glVertex3f((origin.y + size.height) / WINDOW_HEIGHT * 2, 2 - (-origin.x) / WINDOW_WIDTH * 2, 0.0f);      //����
			glTexCoord2f(1.0f, 1.0f); glVertex3f((origin.y + size.height) / WINDOW_HEIGHT * 2, 2 - (-origin.x + size.width) / WINDOW_WIDTH * 2, 0.0f);      //����
			glTexCoord2f(1.0f, 0.0f); glVertex3f((origin.y) / WINDOW_HEIGHT * 2, 2 - (-origin.x + size.width) / WINDOW_WIDTH * 2, 0.0f);      //����
			*/

			
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-(size.width) / r , -(size.height) / r, 0.0f);    //����
			glTexCoord2f(0.0f, 1.0f); glVertex3f((size.width) / r , -(size.height) / r, 0.0f);      //����
			glTexCoord2f(1.0f, 1.0f); glVertex3f((size.width) / r , (size.height) / r, 0.0f);      //����
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-(size.width) / r , (size.height) / r, 0.0f);      //����
			

			/*
			glTexCoord2f(0.0f, 0.0f); glVertex3f((origin.y) / WINDOW_HEIGHT * 2, (origin.x) / WINDOW_WIDTH * 2, 0.0f);    //����
			glTexCoord2f(0.0f, 1.0f); glVertex3f((origin.y + size.height) / WINDOW_HEIGHT * 2,(origin.x) / WINDOW_WIDTH * 2, 0.0f);      //����
			glTexCoord2f(1.0f, 1.0f); glVertex3f((origin.y + size.height) / WINDOW_HEIGHT * 2, (origin.x - size.width) / WINDOW_WIDTH * 2, 0.0f);      //����
			glTexCoord2f(1.0f, 0.0f); glVertex3f((origin.y) / WINDOW_HEIGHT * 2, (origin.x - size.width) / WINDOW_WIDTH * 2, 0.0f);      //����
			*/
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		}
	}
	///////////////////////////////////////////////////////////
	//�κ�glPrintӦ�ڴ���֮��ִ�У���Ȼ��������
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glLoadIdentity();
	glRasterPos2f(-1.0f, -0.8f);
	ScreenToClient(hWnd, &mousepos);
	Director::getTheInstance()->setMousePos(mousepos);
	mousepos = Director::getTheInstance()->getMousePos();
	glPrint("mouse pos(%ld,%ld)", mousepos.x, mousepos.y);
	glRasterPos2f(-1.0f, -0.6f);
	glPrint("Keyboard: %c", lastPressedKey);
	//   ���������� 
	getKeyBoardState();
	showFPS();
	glRasterPos2f(-1.0f, -0.5f);
	glPrint("aswd control r reset");
	SwapBuffers(hDC);

}

void initDrawing()
{
	int  iFormat;



	hDC = GetDC(hWnd);



	ZeroMemory(&pfd, sizeof (pfd));

	pfd.nSize = sizeof (pfd);

	pfd.nVersion = 1;        //  �汾��һ����Ϊ 



	//  һ��������ػ������Եı�־λ 

	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

	pfd.iPixelType = PFD_TYPE_RGBA;     //  ����������������RGBA ������ɫ����;  

	pfd.cColorBits = 32;       //  ÿ����ɫ����������ɫλƽ�����Ŀ������ɫ������ʽ�ǻ�������С 

	pfd.cDepthBits = 16;

	pfd.iLayerType = PFD_MAIN_PLANE;  //  �����ԣ�Ϊ��һ���Զ������� 



	iFormat = ChoosePixelFormat(hDC, &pfd); //  ѡ��һ�����ظ�ʽ 



	SetPixelFormat(hDC, iFormat, &pfd);  //  ���õ�DC �� 



	ghRC = wglCreateContext(hDC);      //  ������ͼ������ 

	wglMakeCurrent(hDC, ghRC);       //  ʹ֮��Ϊ��ǰ��ͼ������ 


	openglInit();
}

DWORD WINAPI  DrawingLoop(LPVOID lpParameter)
{
	if (!openglInited)
		initDrawing();
	while (true)
	{
		SceneShow();
		Sleep(1000/60);
	}
}

//OpenGL ��ʼ����ʼ 

void openglInit()
{
	BuildFont(hDC);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);        //   ��ɫ���� 

	glColor3f(1.0f, 1.0f, 1.0f);
	glShadeModel(GL_FLAT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	///////////////////////////////////////////
	//�ڴ˼��س���
	Scene* p = (Scene*)new testscene1("test");
	Director::getTheInstance()->addScene(p);
	Director::getTheInstance()->init();
}

void showFPS()
{
	glLoadIdentity();
	glRasterPos2f(-1.0f, -1.0f);

	static float lastFPS = 0;
	lastFPS = 1.0 / LastCycleTime;
	glPrint("FPS:%f", lastFPS);
}


void setFPS(float fps)
{
	FPS = fps;
}

void getLastCycleTime()
{
	LARGE_INTEGER LARGE;
	static LONGLONG lasttimeL = 0;
	LONGLONG nowL = 0;
	double freq = 0;
	QueryPerformanceFrequency(&LARGE);
	freq = (double)LARGE.QuadPart;//���Ƶ��
	QueryPerformanceCounter(&LARGE);
	nowL = LARGE.QuadPart;
	DWORD now = GetTickCount();
	LastCycleTime = ((float)(nowL - lasttimeL)) / freq;
	lasttimeL = nowL;
}

void getKeyBoardState()
{
	if (true)
	{
		glRasterPos2f(-1.0f, -0.2f);
		glPrint("L button Pressed %d", GetAsyncKeyState(VK_LBUTTON) & 0x8000);
	}
}