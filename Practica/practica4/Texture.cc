#include "Texture.h"


Texture :: Texture(const char *textureFile)
{
  this->centralImg = NULL;
  //cargar la imagen
  centralImg = new jpg::Imagen(textureFile);

  tamx = centralImg->tamX(); //num.columnas
  tamy = centralImg->tamY();
  texels = centralImg->leerPixels(); //puntero textes
  imageSize = tamx*tamy*3;

  //hace idTex igual a un nuevo identificador
  glGenTextures(1, &idTex);
  glBindTexture(GL_TEXTURE_2D, idTex); //activa textura con identificado 'idTex'
  //Genera automaticamente versiones a multiples resoluciones
  glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, tamx, tamy, 0, GL_RGB, GL_UNSIGNED_BYTE, texels);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering
  // glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
  // glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
  glBindTexture(GL_TEXTURE_2D, idTex);
}

Texture :: ~Texture()
{
  delete this->centralImg;
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