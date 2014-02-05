/************************************************************************************************
*                                                                                               *
*                                                                                               *
************************************************************************************************/

#include "gMain.h"

/************************************************************************************************
* инициализация данных                                                                          *
************************************************************************************************/
void InitGameData()
{
	GameState		= gsIntro;
	MenuState		= msNewGame;
	CanResume		= false;
	CurrentLevel	= 1;
	CameraType		= 3;

	Log("Загрузка текстур...");
	textbgIntro		= LoadTexture("data/images/bgintro.bmp");
	textbgMainMenu	= LoadTexture("data/images/bgmenu.bmp");
	textbgScores	= LoadTexture("data/images/bgscores.bmp");
	textmenuResume	= LoadTexture("data/images/menuresume.bmp");
	textmenuNewGame	= LoadTexture("data/images/menunewgame.bmp");
	textmenuScores	= LoadTexture("data/images/menuscores.bmp");
	textmenuQuit	= LoadTexture("data/images/menuquit.bmp");
	Log("ОК\n");

	Walls.Init(128.0f, 96.0f, 4.0f, LoadTexture("data/images/wall.bmp"));
	Ball.Init(vInit(0.0f, 0.0f, 0.0f), vInit(0.5f, 0.0f, -0.7f), 0.12f, 1.5f);
	Bouncher.Init(vInit(0.0f, 0.0f, 40.0f), vInit(-1.0f, 0.0f, 0.0f), 1.0f, 1.0f, 10.0f, LoadTexture("data/images/wall.bmp"));
	Level.Init(Walls.Width, Walls.Height);
	Level.LoadFromFile(Levels[CurrentLevel-1]);

	SkyBox.Init(1000.0f, LoadTexture("data/images/sky.bmp"));
	
	Log("Загрузка шрифта...");
	Font.Init("data/fonts/fnt1.bmp");
	Log("ОК\n");

	Log("Загрузка таблицы рекордов...");
	ScoreTable.LoadFromFile("data/score.dat");
	Log("ОК\n");

	CharCount = 0;
}

/************************************************************************************************
* деинициализация данных                                                                        *
************************************************************************************************/
void DeinitGameData()
{
	Font.Kill();
	glDeleteLists(1, 500);
}

/************************************************************************************************
* инициализация новой игры                                                                      *
************************************************************************************************/
void NewGame()
{
	Lives				= 3;
	BouncherHoldBall	= true;
	GameState			= gsGame;
	CanResume			= true;
	CurrentLevel		= 1;
	Level.LoadFromFile(Levels[CurrentLevel-1]);
	CurrentRecord.Zero();
}

/************************************************************************************************
* обработка событий вступления                                                                  *
************************************************************************************************/
void ProcessIntro()
{
	if (Keys[key_space])
	{
		Keys[key_space]	= false;
		GameState		= gsMainMenu;
	}
}

/************************************************************************************************
* воспроизведение вступления                                                                    *
************************************************************************************************/
void RenderIntro()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 0, 12, 0, 0, 0, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, textbgIntro);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.4f, -4.8f, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 6.4f, -4.8f, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 6.4f,  4.8f, 0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.4f,  4.8f, 0.0);
	glEnd();

	Font.SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	Font.OutText(30.0f, 20.0f, 1.0f, "Devoider's test bouncher game v 0.1");
}

/************************************************************************************************
* обработка событий главного меню                                                               *
************************************************************************************************/
void ProcessMainMenu()
{
	if (Keys[VK_ESCAPE])
	{
		Keys[VK_ESCAPE] = false;
		GameState		= gsQuit;
	}

	if (Keys[key_up])
	{
		Keys[key_up]	= false;
		if ((MenuState==msNewGame) && (!CanResume)) MenuState = msQuit;
		else MenuState = MenuState - 1;
		if (MenuState<msResume) MenuState = msQuit;
	}

	if (Keys[key_down])
	{
		Keys[key_down]	= false;
		if ((MenuState==msQuit) && (!CanResume)) MenuState = msNewGame;
		else MenuState = MenuState + 1;
		if (MenuState>msQuit) MenuState = msResume;
	}

	if (Keys[key_enter] && MenuState==msQuit)
	{
		Keys[key_enter]	= false;
		GameState		= gsQuit;
	}

	if (Keys[key_enter] && MenuState==msScores)
	{
		Keys[key_enter]	= false;
		GameState		= gsScores;
	}

	if (CanResume) if (Keys[key_enter] && MenuState==msResume)
	{
		Keys[key_enter]	= false;
		GameState		= gsGame;
	}

	if (Keys[key_enter] && MenuState==msNewGame)
	{
		Keys[key_enter]	= false;
		NewGame();
	}
}

/************************************************************************************************
* прорисовка главного меню                                                                      *
************************************************************************************************/
void RenderMainMenu()
{
	float	mzResume;
	float	mzNewGame;
	float	mzScores;
	float	mzQuit;

	switch (MenuState)
	{
	case msResume:
		{
			mzResume	= 62.0f;
			mzNewGame	= 60.0f;
			mzScores	= 60.0f;
			mzQuit		= 60.0f;
			break;
		}
	case msNewGame:
		{
			mzResume	= 60.0f;
			mzNewGame	= 62.0f;
			mzScores	= 60.0f;
			mzQuit		= 60.0f;
			break;
		}
	case msScores:
		{
			mzResume	= 60.0f;
			mzNewGame	= 60.0f;
			mzScores	= 62.0f;
			mzQuit		= 60.0f;
			break;
		}
	case msQuit:
		{
			mzResume	= 60.0f;
			mzNewGame	= 60.0f;
			mzScores	= 60.0f;
			mzQuit		= 62.0f;
			break;
		}
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 0, 70, 0, 0, 0, 0, 1, 0);
	angle += 0.01f;
	glPushMatrix();
		glRotatef(angle, 0, 0, 1);
		glColor4f(1, 1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, textbgMainMenu);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-64,-48, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 64,-48, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 64, 48, 0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-64, 48, 0);
		glEnd();
	glPopMatrix();

	glEnable(GL_BLEND);
	glColor4f(0, 1, 0, 1);
	glDisable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, textmenuResume);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-4, 1.0f, mzResume);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 4, 1.0f, mzResume);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 4, 2.0f, mzResume);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-4, 2.0f, mzResume);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textmenuNewGame);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-4, 0.0f, mzNewGame);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 4, 0.0f, mzNewGame);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 4, 1.0f, mzNewGame);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-4, 1.0f, mzNewGame);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textmenuScores);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-4,-1.0f, mzScores);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 4,-1.0f, mzScores);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 4, 0.0f, mzScores);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-4, 0.0f, mzScores);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textmenuQuit);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-4,-2.0f, mzQuit);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 4,-2.0f, mzQuit);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 4,-1.0f, mzQuit);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-4,-1.0f, mzQuit);
	glEnd();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

/************************************************************************************************
* воспроизведение игры                                                                          *
************************************************************************************************/
void ProcessGame()
{
	int		j,i;
	POINT	CurPos;
	float	bxm;

	if (Keys[VK_ESCAPE])
	{
		Keys[VK_ESCAPE] = false;
		GameState = gsMainMenu;
	}

	if (Lives<0)
	{
		CanResume = false;
		GameState = gsNameDlg;
		strcpy(CurrentRecord.Name, "");
		CharCount = 0;
	}
	else
	{
		if (Keys[key_1]) { Keys[key_1] = false; CameraType = 1; }
		if (Keys[key_2]) { Keys[key_2] = false; CameraType = 2; }
		if (Keys[key_3]) { Keys[key_3] = false; CameraType = 3; }
		if (Keys[key_4]) { Keys[key_4] = false; CameraType = 4; }
		if (Keys[key_5]) { Keys[key_5] = false; CameraType = 5; }

		if (Keys[key_space]) BouncherHoldBall = false;

		if (Level.Number==0)
		{
			CurrentLevel++;
			CurrentRecord.LevelsDone++;
			if (CurrentLevel>10) CurrentLevel = 1;
			Level.LoadFromFile(Levels[CurrentLevel-1]);
			BouncherHoldBall = true;
			Ball.Pos = vInit(Bouncher.Pos);
			Ball.Pos.z = Ball.Pos.z - Ball.R - Bouncher.R - 0.1f;
		}
		GetCursorPos(&CurPos);
		bxm = (float)((CurPos.x-Window.Width/2)/10);
		SetCursorPos(Window.Width/2, Window.Height/2);

		if (!BouncherHoldBall) Ball.MoveForward();
		else
		{
			Ball.Pos = vInit(Bouncher.Pos);
			Ball.Pos.z = Ball.Pos.z - Ball.R - Bouncher.R - 0.1f;
		}

		Bouncher.Move(bxm, 0, 0);

		if ((Bouncher.Pos.x-Bouncher.Size/2)<-Walls.Width/2) Bouncher.Pos.x = -Walls.Width/2+Bouncher.Size/2;
		if ((Bouncher.Pos.x+Bouncher.Size/2)>Walls.Width/2) Bouncher.Pos.x = Walls.Width/2-Bouncher.Size/2;

		// проверка столеновений мяча и Bouncher'а
		if ((Ball.Pos.x+Ball.R>=Bouncher.Pos.x-Bouncher.Size/2)	&&
			(Ball.Pos.x-Ball.R<=Bouncher.Pos.x+Bouncher.Size/2)	&&
			(Ball.Pos.z+Ball.R>=Bouncher.Pos.z-Bouncher.R)		&&
			(Ball.Pos.z-Ball.R<=Bouncher.Pos.z+Bouncher.R))
		{
			Ball.Dir.z = -Ball.Dir.z;
		}
		// проверка столкновения мяча с блоками
		for (i=0; i<10; i++)
		{
			for (j=0; j<18; j++)
			{
				if (Level.Bricks[j][i].Type!='0')
				{
					if (((Ball.Pos.z-Ball.R <= Level.Bricks[j][i].Pos.z+Level.BricksHeight/2)	&&
						 (Ball.Pos.z+Ball.R >= Level.Bricks[j][i].Pos.z-Level.BricksHeight/2))	&&
						((Ball.Pos.x-Ball.R <= Level.Bricks[j][i].Pos.x+Level.BricksWidth/2)	&&
						 (Ball.Pos.x+Ball.R >= Level.Bricks[j][i].Pos.x-Level.BricksWidth/2)))
					{
						vector3f v = vInit(vSub(Level.Bricks[j][i].Pos, Ball.Pos));
						if (fabs(v.x)<fabs(v.z))
						{
							Level.KillBrick(i, j);
							Ball.Dir.z = -Ball.Dir.z;
							CurrentRecord.Score +=50;
							break;
						}
						else
						{
							Level.KillBrick(i, j);
							Ball.Dir.x = -Ball.Dir.x;
							CurrentRecord.Score +=50;
							break;
						}
					}
				}
			}
		}
		// проверка столкновений мяча и стен
		if ((Ball.Pos.x+Ball.R>=Walls.Width/2) | (Ball.Pos.x-Ball.R<=-Walls.Width/2))
		{
			Ball.Dir.x = -Ball.Dir.x;
		}
		if (Ball.Pos.z+Ball.R>=Walls.Height/2)
		{
			Ball.Dir.z = -Ball.Dir.z;
			BouncherHoldBall = true;
			Ball.Pos = vInit(Bouncher.Pos);
			Ball.Pos.z = Ball.Pos.z - Ball.R - Bouncher.R - 0.1f;
			Lives--;
		}
		if (Ball.Pos.z-Ball.R<=-Walls.Height/2)
		{
			Ball.Dir.z = -Ball.Dir.z;
		}
	}
}

/************************************************************************************************
* обработка событий игрового процесса                                                           *
************************************************************************************************/
void RenderGame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glDisable(GL_BLEND);

	switch (CameraType)
	{
	case 1:
		{
			gluLookAt(0.0f, 170.0f, 150.0f, Ball.Pos.x, Ball.Pos.y, Ball.Pos.z, 0.0f, 1.0f, 0.0f);
			break;
		}
	case 2:
		{
			gluLookAt(0.0f, 200.0f, 0.0f, Ball.Pos.x, Ball.Pos.y, Ball.Pos.z, 0.0f, 1.0f, 0.0f);
			break;
		}
	case 3:
		{
			gluLookAt(0.0f, 200.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f);
			break;
		}
	case 4:
		{
			gluLookAt(Bouncher.Pos.x, 30.0f, Bouncher.Pos.z+50, Ball.Pos.x, -10.0f, -50.0f, 0.0f, 1.0f, 0.0f);
			break;
		}
	case 5:
		{
			gluLookAt(Ball.Pos.x, 100.0f, Ball.Pos.z, Ball.Pos.x, Ball.Pos.y, Ball.Pos.z-1, 0.0f, 1.0f, 0.0f);
			break;
		}
	}

	SkyBox.Draw();
	Walls.Draw();
	Level.Draw();
	Bouncher.Draw();
	Ball.Draw();

	Font.OutText(60.0f, 650.0f, 1.5f, "Left: %3i", Level.Number);
	Font.OutText(50.0f, 50.0f, 1.5f, "Score: %7i", CurrentRecord.Score);
	Font.OutText(750.0f, 50.0f, 1.5f, "Lifes: %2i", Lives);
	Font.OutText(750.0f, 650.0f, 1.5f, "Done: %2i", CurrentRecord.LevelsDone);

}

/************************************************************************************************
*                                                                                   *
************************************************************************************************/
void ProcessScores()
{
	if (Keys[VK_ESCAPE])
	{
		Keys[VK_ESCAPE] = false;
		GameState = gsMainMenu;
	}
}

/************************************************************************************************
* воспроизведение таблицы рекордов                                                              *
************************************************************************************************/
void RenderScores()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 0, 7, 0, 0, 0, 0, 1, 0);

	glBindTexture(GL_TEXTURE_2D, textbgScores);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0f, -3.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 4.0f, -3.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 4.0f,  3.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.0f,  3.0f, 0.0f);
	glEnd();

	for (int i=0; i<10; i++)
	{
		Font.OutText(100.0f, 100+50.0f*i, 2.0f, "%2i    %10s %8i %3i", (10-i), ScoreTable.Record[9-i].Name, ScoreTable.Record[9-i].Score, ScoreTable.Record[9-i].LevelsDone);
	}
}

/************************************************************************************************
* обработка событий жиалога ввода имени                                                         *
************************************************************************************************/
void ProcessNameDlg()
{
	for (int i=0; i<256; i++)
	{
		if (Keys[key_enter])
		{
			Keys[key_enter] = false;
			ScoreTable.Insert(&CurrentRecord);
			ScoreTable.SaveToFile("data/score.dat");
			GameState = gsScores;
		}
		else
		{
			if (CharCount<10)
			{
				if (Keys[i])
				{
					Keys[i] = false;
					strncpy(CurrentRecord.Name+CharCount, &SymbolTable[i], 1);
					CharCount++;
				}
				for (int jk=0; jk<30000; jk++)
				{
					int j;
					j = jk;
				}
			}
		}
	}
}

/************************************************************************************************
* воспроизведение диалога ввода имени                                                           *
************************************************************************************************/
void RenderNameDlg()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 0, 7, 0, 0, 0, 0, 1, 0);

	glBindTexture(GL_TEXTURE_2D, textbgScores);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0f, -3.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 4.0f, -3.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 4.0f,  3.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.0f,  3.0f, 0.0f);
	glEnd();

	Font.OutText(150, 500, 3, "Enter your name:");
	Font.OutText(200, 300, 3, CurrentRecord.Name);
}

/************************************************************************************************
* собственная функция обработки сообщений                                                       *
************************************************************************************************/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
	case WM_CLOSE:
		DeinitGameData();
		Window.DeinitOpenGL();
		Window.Close();
		break;
	case WM_KEYDOWN:
		Keys[wparam] = true;
		break;
	case WM_KEYUP:
		Keys[wparam] = false;
		break;
	case WM_SIZE:
		Window.UpdatePerspective(LOWORD(lparam), HIWORD(lparam));
		break;
	default:
		return DefWindowProc(hwnd, message, wparam, lparam);
	}
	return 0;
}

/************************************************************************************************
* точка входа программы                                                                         *
************************************************************************************************/
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int cmdshow)
{
	MSG	msg;
	ClearLog();
	Log("Создание окна...");
	Window.Create("test", 1024, 768, 32, true, hinstance);
	Log("ОК\n");

	Log("Инициализация OpenGL...");
	Window.InitOpenGL();
	Log("ОК\n");

	Log("Инициализация игровых данных...\n");
	InitGameData();

	Log("Начало цикла программы...\n");
	while (Window.isActive)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else return true;
		}

		switch (GameState)
		{
		case gsIntro:
			{
				ProcessIntro();
				RenderIntro();
				break;
			}
		case gsMainMenu:
			{
				ProcessMainMenu();
				RenderMainMenu();
				break;
			}
		case gsGame:
			{
				ProcessGame();
				RenderGame();
				break;
			}
		case gsScores:
			{
				ProcessScores();
				RenderScores();
				break;
			}
		case gsNameDlg:
			{
				ProcessNameDlg();
				RenderNameDlg();
				break;
			}
		case gsQuit:
			{
				PostQuitMessage(0);
				break;
			}
		}
		SwapBuffers(Window.hDC);
	}
	return 0;
}