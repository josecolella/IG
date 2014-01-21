#include <vector>
#include <GL/glut.h>
#include "jpg_imagen.hpp"
#define ARRAY_SIZE 4

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

enum generation_t {NOT_ACTIVE, OBJECT, EYE};


class Texture
{
  private:
    jpg::Imagen * centralImg;
    unsigned long tamx;
    unsigned long tamy;
    unsigned char * texels;
    unsigned int imageSize;
    generation_t gen;
    GLuint idTex;
    GLfloat s[ARRAY_SIZE]; //coeficientes para coordenadas s
    GLfloat t[ARRAY_SIZE]; //coeficientes para coordenadas t

  public:
    Texture(const char * textureFile);
    ~Texture();
    unsigned long getX() const;
    unsigned long getY() const;
    unsigned char * getTexels() const;
    //Para activar la textura
    void activate();

};



#endif