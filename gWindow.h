#ifndef GWINDOWH
#define GWINDOWH

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include "gDebug.h"

// linking required libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

class cWindow       // window class
{
public:
    HWND      hWnd;
    HDC       hDC;
    HGLRC     hRC;
    HINSTANCE hInstance;

    char      *Title;

    int       Width;
    int       Height;
    int       Bpp;

    bool      isFullscreen;
    bool      isActive;

    cWindow();
    ~cWindow() {};

    int       Create(char *title, int width, int height, int bpp, bool fullscreen, HINSTANCE hinstance);
    int       InitOpenGL();
    int       DeinitOpenGL();
    int       Close();
    int       SizeToFullScreen();
    int       SetPixFormat();
    void      UpdatePerspective(int width, int height);
};

#endif