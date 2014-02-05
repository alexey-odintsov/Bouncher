/************************************************************************************************
*                                                                                               *
*                                                                                               *
************************************************************************************************/

#include "gWindow.h"

/************************************************************************************************
* Constructor                                                                                   *
************************************************************************************************/
cWindow::cWindow()
{
    this->Width         = 0;
    this->Height        = 0;
    this->Bpp           = 0;
    this->Title         = "";
    this->isActive      = false;
    this->isFullscreen  = false;
}

/************************************************************************************************
* Window creation                                                                               *
************************************************************************************************/
int cWindow::Create(char *title, int width, int height, int bpp, bool fullscreen, HINSTANCE hinstance)
{
    WNDCLASS    WndClass;
    RECT        WndRect;
    DWORD       dwStyle;

    this->hInstance       = hinstance;
    this->Width           = width;
    this->Height          = height;
    this->Bpp             = bpp;
    this->isFullscreen    = fullscreen;
    this->isActive        = true;
    this->Title           = title;

    memset(&WndClass, 0, sizeof(WNDCLASS));
    WndClass.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    WndClass.lpfnWndProc    = (WNDPROC)WndProc;
    WndClass.hInstance      = this->hInstance;
    WndClass.hIcon          = NULL;
    WndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground  = NULL;
    WndClass.lpszClassName  = this->Title;
    WndClass.lpszMenuName   = NULL;

    if (!RegisterClass(&WndClass)) ErrorMessage("Window creation:", "Can't register window class!\n");

    if (this->isFullscreen==true)
    {
      dwStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
      this->SizeToFullScreen();
      ShowCursor(FALSE);
    }
    else
    {
      dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    }

    WndRect.left    = 0;
    WndRect.right   = this->Width;
    WndRect.top     = 0;
    WndRect.bottom  = this->Height;

    AdjustWindowRect(&WndRect, dwStyle, false);

    this->hWnd = CreateWindow(this->Title, this->Title, dwStyle, 0, 0, this->Width, this->Height, NULL, NULL, this->hInstance, NULL);

    if (this->hWnd==NULL) ErrorMessage("Window creation:", "Can't create window!\n");

    ShowWindow(this->hWnd, SW_SHOWNORMAL);
    UpdateWindow(this->hWnd);
    SetFocus(this->hWnd);
    this->isActive = true;

    return 0;

}

/************************************************************************************************
* OpenGL Initialization                                                                         *
************************************************************************************************/
int cWindow::InitOpenGL()
{
    this->hDC = GetDC(this->hWnd);
    this->SetPixFormat();
    this->hRC = wglCreateContext(this->hDC);
    if (!this->hRC) ErrorMessage("OpenGL initialization:", "Can't create OpenGL context!\n");
    if (!wglMakeCurrent(this->hDC, this->hRC)) ErrorMessage("OpenGL initialization:", "Can't set current OpenGL context!\n");
    this->UpdatePerspective(this->Width, this->Height);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
    glEnable(GL_TEXTURE_2D);

    return 0;
}

/************************************************************************************************
* OpenGL deinitialization                                                                       *
************************************************************************************************/
int cWindow::DeinitOpenGL()
{
    wglMakeCurrent(NULL, NULL);
    if (!wglDeleteContext(this->hRC)) ErrorMessage("OpenGL deinitialization:", "Can't delete OpenGL context!\n");
    if (!ReleaseDC(this->hWnd, this->hDC)) ErrorMessage("OpenGL deinitialization:", "Can't release GDI context!\n");
    if (this->isFullscreen)
    {
        ChangeDisplaySettings(NULL, 0);
        ShowCursor(TRUE);
    }

    return 0;
}

/************************************************************************************************
* Window closing                                                                                *
************************************************************************************************/
int cWindow::Close()
{
    UnregisterClass(this->Title, this->hInstance);
    PostQuitMessage(0);

    return 0;
}

/************************************************************************************************
* Pixel format setting                                                                          *
************************************************************************************************/
int cWindow::SetPixFormat()
{
    PIXELFORMATDESCRIPTOR pfd;
    int                   PixelFormat;

    pfd.nSize             = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion          = 1;
    pfd.dwFlags           = PFD_DRAW_TO_WINDOW |
                            PFD_SUPPORT_OPENGL |
                            PFD_DOUBLEBUFFER;
    pfd.dwLayerMask       = PFD_MAIN_PLANE;
    pfd.iPixelType        = PFD_TYPE_RGBA;
    pfd.cColorBits        = this->Bpp;
    pfd.cDepthBits        = this->Bpp;
    pfd.cAccumBits        = 0;
    pfd.cStencilBits      = 0;

    PixelFormat = ChoosePixelFormat(this->hDC, &pfd);

    if (!PixelFormat) ErrorMessage("Pixel format setting:", "Can't choose pixel fomat!\n");
    if (!SetPixelFormat(this->hDC, PixelFormat, &pfd)) ErrorMessage("Pixel format setting:", "Can't set pixel format!\n");

    return 0;
}

/************************************************************************************************
* Set fullscreen mode                                                                           *
************************************************************************************************/
int cWindow::SizeToFullScreen()
{
    DEVMODE dmScreenSettings;
    int     ret;

    memset(&dmScreenSettings, 0, sizeof(DEVMODE));

    dmScreenSettings.dmSize       = sizeof(DEVMODE);
    dmScreenSettings.dmPelsWidth  = this->Width;
    dmScreenSettings.dmPelsHeight = this->Height;
    dmScreenSettings.dmBitsPerPel = this->Bpp;
    dmScreenSettings.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

    ret = ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
    if (ret!=DISP_CHANGE_SUCCESSFUL)
    {
        switch (ret)
        {
        case  DISP_CHANGE_RESTART:
            ErrorMessage("Set fullscreen mode:", "You need to restart computer to apply this parameters!\n xres : %i \n yres : %i \n bpp : %i", this->Width, this->Height, this->Bpp);
            break;
        case  DISP_CHANGE_BADFLAGS:
            ErrorMessage("Set fullscreen mode:", "Wrong flag set!\n xres : %i \n yres : %i \n bpp : %i", this->Width, this->Height, this->Bpp);
            break;
        case  DISP_CHANGE_BADPARAM:
            ErrorMessage("Set fullscreen mode:", "Wrong parameters!\n xres : %i \n yres : %i \n bpp : %i", this->Width, this->Height, this->Bpp);
            break;
        case  DISP_CHANGE_FAILED:
            ErrorMessage("Set fullscreen mode:", "Video adapter can't set selected mode!\n xres : %i \n yres : %i \n bpp : %i", this->Width, this->Height, this->Bpp);
            break;
        case  DISP_CHANGE_BADMODE:
            ErrorMessage("Set fullscreen mode:", "Selected mode is not supported!\n xres : %i \n yres : %i \n bpp : %i", this->Width, this->Height, this->Bpp);
            break;
        case  DISP_CHANGE_NOTUPDATED:
            ErrorMessage("Set fullscreen mode:", "Can't save parameters to registry!\n xres : %i \n yres : %i \n bpp : %i", this->Width, this->Height, this->Bpp);
            break;
        }
    }

    return 0;
}

/************************************************************************************************
* Perspective update                                                                            *
************************************************************************************************/
void cWindow::UpdatePerspective(int width, int height)
{
    if (height==0) height = 1;
    this->Width   = width;
    this->Height  = height;
    glViewport(0, 0, this->Width, this->Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)this->Width/(GLfloat)this->Height, 0.5f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

