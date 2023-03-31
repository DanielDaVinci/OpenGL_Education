#include <windows.h>		
#include <gl\gl.h>	
#include <gl\glu.h>
#include "gl\glaux.h"

#include <math.h>
#include <vector>
#include <string>

#pragma comment (lib, "legacy_stdio_definitions.lib")

#define PI 3.14159265358979323846

using namespace std;

HDC			hDC = NULL;
HGLRC		hRC = NULL;
HWND		hWnd = NULL;
HINSTANCE	hInstance;

bool	keys[256];
bool	active = TRUE;
bool	fullscreen = TRUE;

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0)
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

const GLsizei textureSize = 2;
GLuint textures[textureSize];

GLvoid LoadGLTextures(string url)
{
	static int size = 0;
	size++;

	AUX_RGBImageRec* texture = auxDIBImageLoad(url.c_str());

	glBindTexture(GL_TEXTURE_2D, textures[size - 1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	GLfloat borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->sizeX, texture->sizeY, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, texture->data);
}

int InitGL(GLvoid)
{
	glGenTextures(textureSize, &textures[0]);
	LoadGLTextures("Data/BUMPS.bmp");
	LoadGLTextures("Data/CUBE.bmp");
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return TRUE;
}

void DrawStar(int edges, GLfloat maxR, GLfloat minR)
{
	static GLfloat rotate = 0.0f;

	glLoadIdentity();

	glTranslatef(-2.5f, 0.0f, -10.0f);
	glRotatef(rotate, 0.0f, 1.0f, 0.0f);
	rotate += 0.1f;

	GLfloat x, y, angle;

	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		for (int i = 0; i < edges * 2; i++)
		{
			GLfloat angle1 = 90.0f + (i * 360.0f / (edges * 2));
			GLfloat x1 = cos(angle1 * PI / 180) * ((i % 2 == 0) ? maxR : minR);
			GLfloat y1 = sin(angle1 * PI / 180) * ((i % 2 == 0) ? maxR : minR);

			GLfloat angle2 = 90.0f + ((i + 1) * 360.0f / (edges * 2));
			GLfloat x2 = cos(angle2 * PI / 180) * (((i + 1) % 2 == 0) ? maxR : minR);
			GLfloat y2 = sin(angle2 * PI / 180) * (((i + 1) % 2 == 0) ? maxR : minR);

			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(x1, y1, 0.5f);
			glVertex3f(x1, y1, -0.5f);
			glVertex3f(x2, y2, -0.5f);
			glVertex3f(x2, y2, 0.5f);
		}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.0f, 0.0f, 0.5f);
	for (int i = 0; i <= edges * 2; i++)
	{
		angle = 90.0f + (i * 360.0f / (edges * 2));
		x = cos(angle * PI / 180) * ((i % 2 == 0) ? maxR : minR);
		y = sin(angle * PI / 180) * ((i % 2 == 0) ? maxR : minR);

		glTexCoord2f(x / (maxR * 2) + 0.5f, y / (maxR * 2) + 0.5f); glVertex3f(x, y, 0.5f);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.0f, 0.0f, -0.5f);
	for (int i = 0; i <= edges * 2; i++)
	{
		angle = 90.0f + (i * 360.0f / (edges * 2));
		x = cos(angle * PI / 180) * ((i % 2 == 0) ? maxR : minR);
		y = sin(angle * PI / 180) * ((i % 2 == 0) ? maxR : minR);

		glTexCoord2f(x / (maxR * 2) + 0.5f, y / (maxR * 2) + 0.5f); glVertex3f(x, y, -0.5f);
	}
	glEnd();
}

void DrawHalfCube()
{
	static GLfloat rotation = 0.0f;
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, textures[1]);

	glTranslatef(2.5f, 0.0f, -10.0f);
	glRotatef(rotation, 1.0f, 1.0f, 0.0f);
	rotation += 0.01f;

	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5f, -0.5f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(-0.5f, 0.5f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(0.5f, 1.5f); glVertex3f(-1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.5f, 1.5f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.5f, 0.5f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.5f, -0.5f); glVertex3f(1.0f, -1.0f, 1.0f);


		glTexCoord2f(0.5f, -0.5f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(-0.5f, 0.5f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.5f, 1.5f); glVertex3f(-1.0f, 1.0f, -1.0f);

		glTexCoord2f(0.5f, 1.5f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.5f, 0.5f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.5f, -0.5f); glVertex3f(-1.0f, 1.0f, -1.0f);


		glTexCoord2f(0.5f, -0.5f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(-0.5f, 0.5f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.5f, 1.5f); glVertex3f(1.0f, 1.0f, -1.0f);

		glTexCoord2f(0.5f, 1.5f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.5f, 0.5f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.5f, -0.5f); glVertex3f(1.0f, 1.0f, -1.0f);


		glTexCoord2f(0.5f, -0.5f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(-0.5f, 0.5f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(0.5f, 1.5f); glVertex3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.5f, 1.5f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.5f, 0.5f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.5f, -0.5f); glVertex3f(1.0f, 1.0f, 1.0f);


		glTexCoord2f(0.5f, -0.5f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(-0.5f, 0.5f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.5f, 1.5f); glVertex3f(1.0f, 1.0f, -1.0f);

		glTexCoord2f(0.5f, 1.5f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.5f, 0.5f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.5f, -0.5f); glVertex3f(1.0f, 1.0f, -1.0f);


		glTexCoord2f(0.5f, -0.5f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(-0.5f, 0.5f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.5f, 1.5f); glVertex3f(1.0f, -1.0f, -1.0f);

		glTexCoord2f(0.5f, 1.5f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.5f, 0.5f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(0.5f, -0.5f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
}

BOOL DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawStar(5, 2.0f, 0.775f);
	DrawHalfCube();
	return TRUE;
}

GLvoid KillGLWindow(GLvoid)
{
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	if (hRC)
	{
		if (!wglMakeCurrent(NULL, NULL))
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;
	}

	if (hDC && !ReleaseDC(hWnd, hDC))
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}

	if (hWnd && !DestroyWindow(hWnd))
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}

	if (!UnregisterClass("OpenGL", hInstance))
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;
	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD		dwStyle;
	RECT		WindowRect;
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)height;

	fullscreen = fullscreenflag;

	hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "OpenGL";

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;


		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{

			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;
			}
			else
			{

				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);


	if (!(hWnd = CreateWindowEx(dwExStyle,
		"OpenGL",
		title,
		dwStyle |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN,
		(1920 - width) / 2, (1080 - height) / 2,
		WindowRect.right - WindowRect.left,
		WindowRect.bottom - WindowRect.top,
		NULL,
		NULL,
		hInstance,
		NULL)))
	{
		KillGLWindow();
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	static	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		bits,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	if (!(hDC = GetDC(hWnd)))
	{
		KillGLWindow();
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		KillGLWindow();
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{
		KillGLWindow();
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(hRC = wglCreateContext(hDC)))
	{
		KillGLWindow();
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!wglMakeCurrent(hDC, hRC))
	{
		KillGLWindow();
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ReSizeGLScene(width, height);

	if (!InitGL())
	{
		KillGLWindow();
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND	hWnd,
	UINT	uMsg,
	WPARAM	wParam,
	LPARAM	lParam)
{
	switch (uMsg)
	{
		case WM_ACTIVATE:
		{
			if ((LOWORD(wParam) != WA_INACTIVE) && !((BOOL)HIWORD(wParam)))
				active = TRUE;
			else
				active = FALSE;

			return 0;
		}

		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
			}
			break;
		}

		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		case WM_KEYDOWN:
		{
			keys[wParam] = TRUE;
			return 0;
		}

		case WM_KEYUP:
		{
			keys[wParam] = FALSE;
			return 0;
		}

		case WM_SIZE:
		{
			ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));

			if (DrawGLScene())
				SwapBuffers(hDC);
			return 0;
		}

		case WM_WINDOWPOSCHANGED:
		{
			if (DrawGLScene())
				SwapBuffers(hDC);
			break;
		}
	}


	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	MSG		msg;
	BOOL	done = FALSE;


	if (MessageBox(NULL, "Would You Like To Run In Fullscreen Mode?", "Start FullScreen?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		fullscreen = FALSE;
	}


	if (!CreateGLWindow("Window", 640, 480, 32, fullscreen))
	{
		return 0;
	}

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{

			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])
			{
				done = TRUE;
			}
			else
			{
				SwapBuffers(hDC);
			}

			if (keys[VK_F1])
			{
				keys[VK_F1] = FALSE;
				KillGLWindow();
				fullscreen = !fullscreen;

				if (!CreateGLWindow("Window", 640, 480, 32, fullscreen))
				{
					return 0;
				}
			}
		}
	}


	KillGLWindow();
	return (msg.wParam);
}
