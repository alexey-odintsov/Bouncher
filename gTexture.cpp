/************************************************************************************************
*                                                                                               *
*                                                                                               *
************************************************************************************************/

#include "gTexture.h"

/************************************************************************************************
* загрузка текстуры из файла                                                                    *
************************************************************************************************/
unsigned int LoadTexture(char *filename)
{
    unsigned int Texture;

    // загрузка изображения
    AUX_RGBImageRec *texture1;
    texture1 = auxDIBImageLoad(filename);

    // создание текстуры
    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);

    // установка типов фильтрации текстур
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // непосредственное создание текстуры
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

    free(texture1->data);
    free(texture1);

    return Texture;
}