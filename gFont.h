#ifndef GFONTH
#define GFONTH

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glaux.h>
#include "gTexture.h"

class cFont
{
public:
    int           Base;
    unsigned int  Texture;
    float         Color[4];

    cFont() {};
    ~cFont() {};

    void  Init(char *filename);
    void  LoadFromBMP(char *filename);
    void  SetColor(float r, float g, float b, float a);
    void  Print(float x, float y, char *string, float k);
    void  OutText(float x, float y, float scale, const char *fmt, ...);
    void  Kill();
};

#endif