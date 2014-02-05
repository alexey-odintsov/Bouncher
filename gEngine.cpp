/************************************************************************************************
*                                                                                               *
*                                                                                               *
************************************************************************************************/

#include "gEngine.h"

/************************************************************************************************
* Ball initialization                                                                           *
************************************************************************************************/
void cBall::Init(vector3f pos, vector3f dir, float vel, float r)
{
    this->Pos = vInit(pos);
    this->Dir = vInit(dir);
    this->Vel = vel;
    this->R   = r;
}

/************************************************************************************************
* Move ball forward                                                                             *
************************************************************************************************/
void cBall::MoveForward()
{
    this->Pos = vAdd(this->Pos, vScale(this->Dir, this->Vel));
}

/************************************************************************************************
* Ball drawing                                                                                  *
************************************************************************************************/
void cBall::Draw()
{
    glPushMatrix();
      glTranslatef(this->Pos.x, this->Pos.y, this->Pos.z);
      glColor3f(1.0f, 1.0f, 1.0f);
      auxSolidSphere(this->R);
    glPopMatrix();
}

/************************************************************************************************
* Bouncher initialization                                                                       *
************************************************************************************************/
void cBouncher::Init(vector3f pos, vector3f dir, float vel, float r, float size, unsigned int texture)
{
    this->Pos     = vInit(pos);
    this->Dir     = vInit(dir);
    this->Vel     = vel;
    this->R       = r;
    this->Size    = size;
    this->Texture = texture;
}

/************************************************************************************************
* Bouncher moving                                                                               *
************************************************************************************************/
void cBouncher::Move(float mx, float my, float mz)
{
    this->Pos = vAdd(this->Pos, vInit(mx, my, mz));
}

/************************************************************************************************
* Bouncher drawing                                                                              *
************************************************************************************************/
void cBouncher::Draw()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, this->Texture);
    glPushMatrix();
      glTranslatef(this->Pos.x, this->Pos.y, this->Pos.z);
      glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Size/2, this->R, this->R);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Size/2, this->R, this->R);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Size/2, this->R,-this->R);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Size/2, this->R,-this->R);

        glNormal3f(0.0f,-1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Size/2,-this->R, this->R);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Size/2,-this->R, this->R);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Size/2,-this->R,-this->R);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Size/2,-this->R,-this->R);

        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Size/2,-this->R, this->R);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Size/2,-this->R, this->R);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Size/2, this->R,-this->R);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Size/2, this->R,-this->R);

        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Size/2, this->R,-this->R);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Size/2, this->R,-this->R);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Size/2,-this->R,-this->R);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Size/2,-this->R,-this->R);
      glEnd();
    glPopMatrix();
}

/************************************************************************************************
* Brick initialization                                                                          *
************************************************************************************************/
void cBrick::Init(vector3f pos, char type)
{
    this->Pos   = pos;
    this->Type  = type;
}

/************************************************************************************************
* Brick drawing                                                                                 *
************************************************************************************************/
void cBrick::Draw()
{
    glPushMatrix();
      glTranslatef(this->Pos.x, this->Pos.y, this->Pos.z);
      glCallList(10+atoi(&this->Type));
    glPopMatrix();
}

/************************************************************************************************
* Level initialization                                                                          *
************************************************************************************************/
void cLevel::Init(float width, float height)
{
    int i;
    this->Width         = width;
    this->Height        = height;
    this->BricksWidth   = 6.0f;
    this->BricksHeight  = 3.0f;
    this->BricksDepth   = 1.5f;

    this->Textures[0] = LoadTexture("data/images/bricks/brick01.bmp");
    this->Textures[1] = LoadTexture("data/images/bricks/brick02.bmp");
    this->Textures[2] = LoadTexture("data/images/bricks/brick03.bmp");
    this->Textures[3] = LoadTexture("data/images/bricks/brick04.bmp");
    this->Textures[4] = LoadTexture("data/images/bricks/brick05.bmp");
    this->Textures[5] = LoadTexture("data/images/bricks/brick06.bmp");
    this->Textures[6] = LoadTexture("data/images/bricks/brick07.bmp");
    this->Textures[7] = LoadTexture("data/images/bricks/brick08.bmp");
    this->Textures[8] = LoadTexture("data/images/bricks/brick09.bmp");
    this->Textures[9] = LoadTexture("data/images/bricks/brick10.bmp");

    for (i=0; i<10; i++)
    {
        glNewList(11+i, GL_COMPILE);
          glBindTexture(GL_TEXTURE_2D, this->Textures[i]);
          glBegin(GL_QUADS);
            glNormal3f( 0.0f, 1.0f, 0.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->BricksWidth/2, this->BricksDepth/2, this->BricksHeight/2);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( this->BricksWidth/2, this->BricksDepth/2, this->BricksHeight/2);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( this->BricksWidth/2, this->BricksDepth/2,-this->BricksHeight/2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->BricksWidth/2, this->BricksDepth/2,-this->BricksHeight/2);

            glNormal3f( 0.0f,-1.0f, 0.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->BricksWidth/2,-this->BricksDepth/2, this->BricksHeight/2);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( this->BricksWidth/2,-this->BricksDepth/2, this->BricksHeight/2);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( this->BricksWidth/2,-this->BricksDepth/2,-this->BricksHeight/2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->BricksWidth/2,-this->BricksDepth/2,-this->BricksHeight/2);

            glNormal3f( 0.0f, 0.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->BricksWidth/2,-this->BricksDepth/2, this->BricksHeight/2);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( this->BricksWidth/2,-this->BricksDepth/2, this->BricksHeight/2);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( this->BricksWidth/2, this->BricksDepth/2, this->BricksHeight/2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->BricksWidth/2, this->BricksDepth/2, this->BricksHeight/2);

            glNormal3f( 0.0f, 0.0f,-1.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->BricksWidth/2,-this->BricksDepth/2,-this->BricksHeight/2);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( this->BricksWidth/2,-this->BricksDepth/2,-this->BricksHeight/2);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( this->BricksWidth/2, this->BricksDepth/2,-this->BricksHeight/2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->BricksWidth/2, this->BricksDepth/2,-this->BricksHeight/2);

            glNormal3f( 1.0f, 0.0f, 0.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f( this->BricksWidth/2,-this->BricksDepth/2,-this->BricksHeight/2);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( this->BricksWidth/2,-this->BricksDepth/2, this->BricksHeight/2);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( this->BricksWidth/2, this->BricksDepth/2, this->BricksHeight/2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f( this->BricksWidth/2, this->BricksDepth/2,-this->BricksHeight/2);

            glNormal3f(-1.0f, 0.0f, 0.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->BricksWidth/2,-this->BricksDepth/2,-this->BricksHeight/2);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(-this->BricksWidth/2,-this->BricksDepth/2, this->BricksHeight/2);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(-this->BricksWidth/2, this->BricksDepth/2, this->BricksHeight/2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->BricksWidth/2, this->BricksDepth/2,-this->BricksHeight/2);
          glEnd();
        glEndList();
    }
}

/************************************************************************************************
* Load level from file                                                                          *
************************************************************************************************/
void cLevel::LoadFromFile(char *filename)
{
    FILE    *file;
    int     i, j;

    this->Number = 0;
    file = fopen(filename, "r");
    if (file==NULL) MessageBox(0, "Can't open level file!", "Error", MB_OK | MB_ICONERROR);
    
    for (i=0; i<10; i++)
    {
        for (j=0; j<18; j++)
        {
            fscanf(file, "%c", &this->Bricks[j][i].Type);
            if (this->Bricks[j][i].Type!='0')
            {
                this->Number++;
                this->Bricks[j][i].Pos.x = -this->Width/2+this->BricksWidth/2+j*this->BricksWidth+j+1.5f;
                this->Bricks[j][i].Pos.z = -this->Height/2+i*this->BricksHeight+i+4;
            }
        }
        fseek(file, i*20+20, SEEK_SET);
    }
    fclose(file);
}

/************************************************************************************************
* Level drawing                                                                                 *
************************************************************************************************/
void cLevel::Draw()
{
    int i,j;

    for (i=0; i<10; i++)
    {
        for (j=0; j<18; j++)
        {
            if (this->Bricks[j][i].Type!='0') this->Bricks[j][i].Draw();
        }
    }
}

/************************************************************************************************
* Brick destroying                                                                              *
************************************************************************************************/
void cLevel::KillBrick(int bx, int by)
{
    this->Bricks[by][bx].Type = '0';
    this->Number--;
}

/************************************************************************************************
* Walls initialization                                                                          *
************************************************************************************************/
void cWalls::Init(float width, float height, float size, int texture)
{
	this->Width     = width;
	this->Height    = height;
	this->Size      = size;
	this->Texture   = texture;

	glNewList(lstWalls, GL_COMPILE);
		glBindTexture(GL_TEXTURE_2D, this->Texture);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
			// Front edge
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Width/2,-this->Size/2, this->Height/2);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Width/2,-this->Size/2, this->Height/2);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Width/2, this->Size/2, this->Height/2);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Width/2, this->Size/2, this->Height/2);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Width/2-this->Size,-this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Width/2+this->Size,-this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Width/2+this->Size, this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Width/2-this->Size, this->Size/2, this->Height/2+this->Size);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Width/2-this->Size, this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Width/2+this->Size, this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Width/2,            this->Size/2, this->Height/2           );
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Width/2,            this->Size/2, this->Height/2           );

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Width/2-this->Size,-this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Width/2+this->Size,-this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Width/2,           -this->Size/2, this->Height/2           );
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Width/2,           -this->Size/2, this->Height/2           );

			// Back edge
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Width/2,-this->Size/2,-this->Height/2);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Width/2,-this->Size/2,-this->Height/2);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Width/2, this->Size/2,-this->Height/2);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Width/2, this->Size/2,-this->Height/2);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Width/2-this->Size,-this->Size/2,-this->Height/2-this->Size);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Width/2+this->Size,-this->Size/2,-this->Height/2-this->Size);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Width/2+this->Size, this->Size/2,-this->Height/2-this->Size);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Width/2-this->Size, this->Size/2,-this->Height/2-this->Size);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Width/2-this->Size, this->Size/2,-this->Height/2-this->Size);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Width/2+this->Size, this->Size/2,-this->Height/2-this->Size);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Width/2,            this->Size/2,-this->Height/2           );
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Width/2,            this->Size/2,-this->Height/2           );

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Width/2-this->Size,-this->Size/2,-this->Height/2-this->Size);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Width/2+this->Size,-this->Size/2,-this->Height/2-this->Size);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Width/2,           -this->Size/2,-this->Height/2           );
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Width/2,           -this->Size/2,-this->Height/2           );
		
			// Left edge
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Width/2,-this->Size/2,-this->Height/2);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-this->Width/2,-this->Size/2, this->Height/2);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-this->Width/2, this->Size/2, this->Height/2);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Width/2, this->Size/2,-this->Height/2);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Width/2-this->Size,-this->Size/2,-this->Height/2-this->Size);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-this->Width/2-this->Size,-this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-this->Width/2-this->Size, this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Width/2-this->Size, this->Size/2,-this->Height/2-this->Size);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Width/2-this->Size, this->Size/2,-this->Height/2-this->Size);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-this->Width/2-this->Size, this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-this->Width/2,            this->Size/2, this->Height/2           );
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Width/2,            this->Size/2,-this->Height/2           );

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Width/2-this->Size,-this->Size/2,-this->Height/2-this->Size);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-this->Width/2-this->Size,-this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-this->Width/2,           -this->Size/2, this->Height/2           );
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Width/2,           -this->Size/2,-this->Height/2           );

			// Right edge
			glTexCoord2f(0.0f, 0.0f); glVertex3f( this->Width/2,-this->Size/2,-this->Height/2);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Width/2,-this->Size/2, this->Height/2);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Width/2, this->Size/2, this->Height/2);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( this->Width/2, this->Size/2,-this->Height/2);

			glTexCoord2f(0.0f, 0.0f); glVertex3f( this->Width/2+this->Size,-this->Size/2,-this->Height/2-this->Size);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Width/2+this->Size,-this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Width/2+this->Size, this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( this->Width/2+this->Size, this->Size/2,-this->Height/2-this->Size);

			glTexCoord2f(0.0f, 0.0f); glVertex3f( this->Width/2+this->Size, this->Size/2,-this->Height/2-this->Size);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Width/2+this->Size, this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Width/2,            this->Size/2, this->Height/2           );
			glTexCoord2f(0.0f, 1.0f); glVertex3f( this->Width/2,            this->Size/2,-this->Height/2           );

			glTexCoord2f(0.0f, 0.0f); glVertex3f( this->Width/2+this->Size,-this->Size/2,-this->Height/2-this->Size);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Width/2+this->Size,-this->Size/2, this->Height/2+this->Size);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Width/2,           -this->Size/2, this->Height/2           );
			glTexCoord2f(0.0f, 1.0f); glVertex3f( this->Width/2,           -this->Size/2,-this->Height/2           );
		glEnd();
	glEndList();
}

/************************************************************************************************
* Walls drawing                                                                                 *
************************************************************************************************/
void cWalls::Draw()
{
	glPushMatrix();
		glCallList(lstWalls);
	glPopMatrix();
}

/************************************************************************************************
* SkyBox initialization                                                                         *
************************************************************************************************/
void cSkyBox::Init(float size, int texture)
{
	this->Size		= size;
	this->Texture	= texture;
	this->Angle		= 0;
	
	glNewList(lstSkyBox, GL_COMPILE);
		glBindTexture(GL_TEXTURE_2D, this->Texture);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Size/2,-this->Size/2,-this->Size/2);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Size/2,-this->Size/2,-this->Size/2);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Size/2, this->Size/2,-this->Size/2);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Size/2, this->Size/2,-this->Size/2);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Size/2,-this->Size/2, this->Size/2);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Size/2,-this->Size/2, this->Size/2);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Size/2, this->Size/2, this->Size/2);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Size/2, this->Size/2, this->Size/2);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Size/2, this->Size/2, this->Size/2);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Size/2, this->Size/2, this->Size/2);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Size/2, this->Size/2,-this->Size/2);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Size/2, this->Size/2,-this->Size/2);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Size/2,-this->Size/2, this->Size/2);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Size/2,-this->Size/2, this->Size/2);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Size/2,-this->Size/2,-this->Size/2);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Size/2,-this->Size/2,-this->Size/2);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->Size/2,-this->Size/2, this->Size/2);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-this->Size/2,-this->Size/2,-this->Size/2);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-this->Size/2, this->Size/2,-this->Size/2);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->Size/2, this->Size/2, this->Size/2);

			glTexCoord2f(0.0f, 0.0f); glVertex3f( this->Size/2,-this->Size/2, this->Size/2);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( this->Size/2,-this->Size/2,-this->Size/2);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( this->Size/2, this->Size/2,-this->Size/2);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( this->Size/2, this->Size/2, this->Size/2);
		glEnd();
	glEndList();
}

/************************************************************************************************
* SkyBox drawing                                                                                *
************************************************************************************************/
void cSkyBox::Draw()
{
	this->Angle += 0.01f;
	glPushMatrix();
		glRotatef(this->Angle, 1, 1, 1);
		glCallList(lstSkyBox);
	glPopMatrix();
}

/************************************************************************************************
* Records zeroing                                                                               *
************************************************************************************************/
void sRecord::Zero()
{
	strcpy(this->Name, "----------");
	this->Score = 0;
	this->LevelsDone = 0;
}

/************************************************************************************************
* Records initialization                                                                        *
************************************************************************************************/
cScores::cScores()
{
	for (int i=9; i>=0; i--)
	{
		strcpy(this->Record[i].Name, "----------");
		this->Record[i].Score = 0;
		this->Record[i].LevelsDone = 0;
	}
}

/************************************************************************************************
* Load records from file                                                                        *
************************************************************************************************/
void cScores::LoadFromFile(char *filename)
{
	FILE	*file;

	file = fopen(filename, "r");
	fseek(file, 0L, SEEK_SET);
	for (int i=0; i<10; i++)
	{
		fscanf(file, "%s %d %d", &this->Record[i].Name, &this->Record[i].Score, &this->Record[i].LevelsDone);
		printf("%10s %8i %3i \n", &this->Record[i].Name, this->Record[i].Score, this->Record[i].LevelsDone);
	}
	fclose(file);
}

/************************************************************************************************
* Save records to file                                                                          *
************************************************************************************************/
void cScores::SaveToFile(char *filename)
{
	FILE	*file;

	file = fopen(filename, "w+t");
	fseek(file, 0L, SEEK_SET);

	for (int i=0; i<10; i++)
	{
		fprintf(file, "%s %d %d \n", &this->Record[i].Name, this->Record[i].Score, this->Record[i].LevelsDone);
	}
	fclose(file);
}

/************************************************************************************************
* Add new record                                                                                *
************************************************************************************************/
void cScores::Insert(sRecord *record)
{
	int	index;
	
	index = 0;
	for (int i=0; i<20; i++)
	{
		if (record->Score<this->Record[i].Score) index++;
	}
	if (index<10)
	{
		for (int i=9; i>index; i--)
		{
			strcpy(this->Record[i].Name, this->Record[i-1].Name);
			this->Record[i].Score = this->Record[i-1].Score;
			this->Record[i].LevelsDone = this->Record[i-1].LevelsDone;
		}
		strcpy(this->Record[index].Name, record->Name);
		this->Record[index].Score = record->Score;
		this->Record[index].LevelsDone = record->LevelsDone;
	}
}