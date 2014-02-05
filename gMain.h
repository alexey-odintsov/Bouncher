#ifndef GMAINH
#define GMAINH

#include <windows.h>
#include <conio.h>
#include "gDebug.h"
#include "gWindow.h"
#include "gTexture.h"
#include "gFont.h"
#include "gEngine.h"
#include "gKeyCodes.h"

char  SymbolTable[256] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                          ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                          ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0',
                          '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                          '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                          'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', ' ', ' ', ' ', '_',
                          ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                          'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ', ' ', ' ', ' ', ' ',
                          ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                          ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                          ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                          ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                          ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                          ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                          ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                          ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

cWindow       Window;
cBall         Ball;
cBouncher     Bouncher;
cLevel        Level;
cWalls        Walls;
cFont         Font;
cSkyBox       SkyBox;
cScores       ScoreTable;
sRecord       CurrentRecord;

bool          Keys[256];

int           CurrentLevel;
int           Lives;

int           CameraType;

int           GameState;

const int     gsQuit      = 0;
const int     gsIntro     = 1;
const int     gsMainMenu  = 2;
const int     gsGame      = 3;
const int     gsScores    = 4;
const int     gsNameDlg   = 5;

int           CharCount;

int           MenuState;

const int     msResume    = 0;
const int     msNewGame   = 1;
const int     msScores    = 2;
const int     msQuit      = 3;

bool          CanResume;
bool          BouncherHoldBall;

float         angle;

unsigned int  textbgIntro;
unsigned int  textbgMainMenu;
unsigned int  textbgScores;

unsigned int  textmenuResume;
unsigned int  textmenuNewGame;
unsigned int  textmenuScores;
unsigned int  textmenuQuit;

char          *Levels[10] = { "data/levels/level01.dat",
                              "data/levels/level02.dat",
                              "data/levels/level03.dat",
                              "data/levels/level04.dat",
                              "data/levels/level05.dat",
                              "data/levels/level06.dat",
                              "data/levels/level07.dat",
                              "data/levels/level08.dat",
                              "data/levels/level09.dat",
                              "data/levels/level10.dat" };

#endif