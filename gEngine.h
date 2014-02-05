#ifndef GEMGINEH
#define GENGINEH

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "gGeometry.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include "gTexture.h"

typedef unsigned int texArray[10];

const int lstWalls  = 2;
const int lstSkyBox = 3;

class cBall
{
public:
    vector3f  Pos;
    vector3f  Dir;
    float     Vel;
    float     R;

    cBall() {};
    ~cBall() {};
    void  Init(vector3f pos, vector3f dir, float vel, float r);
    void  MoveForward();
    void  Draw();
};

class cBouncher
{
public:
    vector3f      Pos;
    vector3f      Dir;
    float         Vel;
    float         R;
    float         Size;
    unsigned int  Texture;

    cBouncher() {};
    ~cBouncher() {};

    void  Init(vector3f pos, vector3f dir, float vel, float r, float size, unsigned int texture);
    void  Move(float mx, float my, float mz);
    void  Draw();
};

class cBrick
{
public:
    vector3f    Pos;
    char        Type;

    cBrick() {};
    ~cBrick() {};

    void  Init(vector3f pos, char type);
    void  Draw();
};

class cLevel
{
public:
    float         Width;
    float         Height;
    int           Number;
    float         BricksWidth;
    float         BricksHeight;
    float         BricksDepth;
    cBrick        Bricks[18][10];
    unsigned int  Textures[10];

    cLevel() {};
    ~cLevel() {};

    void  Init(float width, float height);
    void  LoadFromFile(char *filename);
    void  Draw();
    void  KillBrick(int bx, int by);
};

class cWalls
{
public:
    float         Width;
    float         Height;
    float         Size;
    unsigned int  Texture;

    cWalls() {};
    ~cWalls() {};

    void  Init(float width, float height, float size, int texture);
    void  Draw();
};

class cSkyBox
{
public:
    float     Size;
    int       Texture;
    float     Angle;

    cSkyBox() {};
    ~cSkyBox() {};

    void  Init(float size, int texture);
    void  Draw();
};

struct sRecord
{
    char      Name[10];
    int       Score;
    int       LevelsDone;
    void      Zero();
};

class cScores
{
public:
    sRecord   Record[10];

    cScores();
    ~cScores() {};

    void  LoadFromFile(char *filename);
    void  SaveToFile(char *filename);
    void  Insert(sRecord *record);
};

#endif