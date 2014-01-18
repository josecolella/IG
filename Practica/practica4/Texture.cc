#include "Texture.h"
#include <cassert>

Texture :: Texture(const char *textureFile)
{
  this->centralImg = NULL;
  //cargar la imagen
  this->centralImg = new jpg::Imagen(textureFile);

  this->tamx = centralImg->tamX(); //num.columnas
  this->tamy = centralImg->tamY();
  this->texels = centralImg->leerPixels(); //puntero textes
  this->imageSize = tamx*tamy*3;
  this->gen = NOT_ACTIVE;

  for(int i=0;i<ARRAY_SIZE;i++)
  {
    s[i] = t[i] = 0.0f;
  }
  //hace idTex igual a un nuevo identificador
  glGenTextures(1, &idTex);
  glBindTexture(GL_TEXTURE_2D, idTex); //activa textura con identificado 'idTex'
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, this->tamx, this->tamy, GL_RGB, GL_UNSIGNED_BYTE,this->texels);
  assert(glGetError() == GL_NO_ERROR);
}

Texture :: ~Texture()
{
  delete this->centralImg;
  glDisable(GL_TEXTURE_2D);
}


unsigned long Texture :: getX() const
{
  return this->tamx;
}


unsigned long Texture :: getY() const
{
  return this->tamy;
}


unsigned char * Texture :: getTexels() const
{
  return this->texels;
}

void Texture :: activate()
{


  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, this->idTex);
  if(gen == NOT_ACTIVE){
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
  }
  else
  {
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
               
    glTexGenfv(GL_S, GL_OBJECT_PLANE, s);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, t);

    glEnable( GL_TEXTURE_GEN_S);
    glEnable( GL_TEXTURE_GEN_T);
  }

}