/************************************************************************************************
*                                                                                               *
*                                                                                               *
************************************************************************************************/

#include "gWindow.h"

/************************************************************************************************
* конструктор                                                                                   *
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
* создание окна                                                                                 *
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

    if (!RegisterClass(&WndClass)) ErrorMessage("Создание окна:", "Не удалось зарегистрировать класс окна!\n");

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

    if (this->hWnd==NULL) ErrorMessage("Создание окна:", "Не удалось создать окно!\n");

    ShowWindow(this->hWnd, SW_SHOWNORMAL);
    UpdateWindow(this->hWnd);
    SetFocus(this->hWnd);
    this->isActive = true;

    return 0;

}

/************************************************************************************************
* инициализация OpenGL                                                                          *
************************************************************************************************/
int cWindow::InitOpenGL()
{
    this->hDC = GetDC(this->hWnd);
    this->SetPixFormat();
    this->hRC = wglCreateContext(this->hDC);
    if (!this->hRC) ErrorMessage("Инициализация OpenGL:", "Не удалось создать контекст воспроизведения OpenGL!\n");
    if (!wglMakeCurrent(this->hDC, this->hRC)) ErrorMessage("Инициализация OpenGL:", "Не удалось сделать контекст воспроизведения текущим!\n");
    this->UpdatePerspective(this->Width, this->Height);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
    glEnable(GL_TEXTURE_2D);

    return 0;
}

/************************************************************************************************
* деинициализация OpenGL                                                                        *
************************************************************************************************/
int cWindow::DeinitOpenGL()
{
    wglMakeCurrent(NULL, NULL);
    if (!wglDeleteContext(this->hRC)) ErrorMessage("Деинициализация OpenGL:", "Не удалось удалить контекст воспроизведения OpenGL!\n");
    if (!ReleaseDC(this->hWnd, this->hDC)) ErrorMessage("Деинициализация OpenGL:", "Не удалось освободить контекст устройства GDI!\n");
    if (this->isFullscreen)
    {
        ChangeDisplaySettings(NULL, 0);
        ShowCursor(TRUE);
    }

    return 0;
}

/************************************************************************************************
* уничтожение окна                                                                              *
************************************************************************************************/
int cWindow::Close()
{
    UnregisterClass(this->Title, this->hInstance);
    PostQuitMessage(0);

    return 0;
}

/************************************************************************************************
* установка формата пикселей                                                                    *
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

    if (!PixelFormat) ErrorMessage("Установка формата пикселей:", "Не удалось выбрать формат пикселей\n");
    if (!SetPixelFormat(this->hDC, PixelFormat, &pfd)) ErrorMessage("Установка формата пикселей:", "Не удалось установить формат пикселей\n");

    return 0;
}

/************************************************************************************************
* включение полноэкранного режима                                                               *
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
            ErrorMessage("Смена разрешения экрана:", "Для применения данных параметров необходимо перезаргузить компьютер!\n xres : %i \n yres : %i \n bpp : %i", this->Width, this->Height, this->Bpp);
            break;
        case  DISP_CHANGE_BADFLAGS:
            ErrorMessage("Смена разрешения экрана:", "Недопустимый набор флагов!\n xres : %i \n yres : %i \n bpp : %i", this->Width, this->Height, this->Bpp);
            break;
        case  DISP_CHANGE_BADPARAM:
            ErrorMessage("Смена разрешения экрана:", "Недопустимые параметры!\n xres : %i \n yres : %i \n bpp : %i", this->Width, this->Height, this->Bpp);
            break;
        case  DISP_CHANGE_FAILED:
            ErrorMessage("Смена разрешения экрана:", "Графический адаптер не может определить данный режим!\n xres : %i \n yres : %i \n bpp : %i", this->Width, this->Height, this->Bpp);
            break;
        case  DISP_CHANGE_BADMODE:
            ErrorMessage("Смена разрешения экрана:", "Графический режим не поддерживается!\n xres : %i \n yres : %i \n bpp : %i", this->Width, this->Height, this->Bpp);
            break;
        case  DISP_CHANGE_NOTUPDATED:
            ErrorMessage("Смена разрешения экрана:", "Не удается сохранить параметры в реестре!\n xres : %i \n yres : %i \n bpp : %i", this->Width, this->Height, this->Bpp);
            break;
        }
    }

    return 0;
}

/************************************************************************************************
* обновление перспективы                                                                        *
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

