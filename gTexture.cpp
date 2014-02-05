/************************************************************************************************
*                                                                                               *
*                                                                                               *
************************************************************************************************/

#include "gTexture.h"

/************************************************************************************************
* Load texture from file                                                                        *
************************************************************************************************/
unsigned int LoadTexture(char *filename)
{
    unsigned int Texture;

    // image loading
    AUX_RGBImageRec *texture1;
    texture1 = auxDIBImageLoad(filename);

    // Teture generation
    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);

    // Texture filters applying
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Texture creation
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

    free(texture1->data);
    free(texture1);

    return Texture;
}