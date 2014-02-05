/************************************************************************************************
*                                                                                               *
*                                                                                               *
************************************************************************************************/

#include "gFont.h"

/************************************************************************************************
* Font initialization                                                                           *
************************************************************************************************/
void cFont::Init(char *filename)
{
    float cx, cy;

    this->LoadFromBMP(filename);
    this->Base = glGenLists(256);
    glBindTexture(GL_TEXTURE_2D, this->Texture);

    for (int loop=0; loop<256; loop++)
    {
        cx = float(loop%16)/16.0f;
        cy = float(loop/16)/16.0f;

        glNewList(this->Base+loop, GL_COMPILE);
          glBegin(GL_QUADS);
            glTexCoord2f(cx, 1-cy-0.0625f);
            glVertex2i(0, 0);
            glTexCoord2f(cx+0.0625f, 1-cy-0.0625f);
            glVertex2i(16, 0);
            glTexCoord2f(cx+0.0625f, 1-cy);
            glVertex2i(16, 16);
            glTexCoord2f(cx, 1-cy);
            glVertex2i(0, 16);
          glEnd();
          glTranslated(16, 0, 0);
        glEndList();
    }
}

/************************************************************************************************
* Load font from BMP file                                                                       *
************************************************************************************************/
void cFont::LoadFromBMP(char *filename)
{
    AUX_RGBImageRec *texture1;
    texture1 = auxDIBImageLoad(filename);

    // texture generation
    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);

    // Set texture filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // texture creation
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

    free(texture1->data);
    free(texture1);
}

/************************************************************************************************
* Font color initialization                                                                     *
************************************************************************************************/
void cFont::SetColor(float r, float g, float b, float a)
{
    this->Color[0] = r;
    this->Color[1] = g;
    this->Color[2] = b;
    this->Color[3] = a;
}

/************************************************************************************************
* Message printing on scren                                                                     *
************************************************************************************************/
void cFont::Print(float x, float y, char *string, float k)
{
    glEnable(GL_BLEND);
    glLoadIdentity();
    glColor4fv(this->Color);
    glBindTexture(GL_TEXTURE_2D, this->Texture);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
      glLoadIdentity();
      glOrtho(0, GetSystemMetrics(SM_CXFULLSCREEN), 0, GetSystemMetrics(SM_CYFULLSCREEN), -1, 1);
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
        glLoadIdentity();
        glTranslatef(x, y, 0.5f);
        glListBase(this->Base);
        glScalef(k, k, 1.0f);
        glCallLists(strlen(string), GL_BYTE, string);
        glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}

/************************************************************************************************
* Message printing on scren with parameters                                                     *
************************************************************************************************/
void cFont::OutText(float x, float y, float scale, const char *fmt, ...)
{
    char text[256];
    va_list ap;

    va_start(ap, fmt);
      vsprintf(text, fmt, ap);
    va_end(ap);

    this->Print(x, y, text, scale);
}

/************************************************************************************************
* Font deinitialization                                                                         *
************************************************************************************************/
void cFont::Kill()
{
    glDeleteLists(this->Base, 256);
}
