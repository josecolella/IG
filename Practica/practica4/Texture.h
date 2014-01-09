#include "vertex.h"
#include "MallaTVT.h" //Mallas para crear la lata
#include <vector>
#include <GL/glut.h>
#include "jpg_imagen.hpp"


#ifndef _TEXTURE_H_
#define _TEXTURE_H_


class Texture
{
  private:
    jpg::Imagen * centralImg;
    unsigned long tamx;
    unsigned long tamy;
    unsigned char * texels;
    unsigned int imageSize;
    GLuint idTex;


  public:
    Texture(const char * textureFile);
    ~Texture();
    unsigned long getX() const;
    unsigned long getY() const;
    unsigned char * getTexels() const;

};



#endif