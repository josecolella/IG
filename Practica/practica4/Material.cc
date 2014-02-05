#include "Material.h"


Material :: Material()
{
  isIlluminated = false;
  texturePtr = NULL;
  amb[3] = dis[3] = spe[3]  = 1.0;
}
Material :: Material(const char * materialFile)
{
  texturePtr = new Texture(materialFile);
  amb[3] = dis[3] = spe[3]  = 1.0;
}

Material :: ~Material()
{
  if(texturePtr != NULL) 
    delete texturePtr;
}

void Material :: activate() {

  glEnable(GL_LIGHTING);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glEnable(GL_NORMALIZE);


  glMaterialfv(GL_FRONT,GL_AMBIENT,amb);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,dis);
  glMaterialfv(GL_FRONT,GL_SPECULAR,spe);
  glMaterialf(GL_FRONT,GL_SHININESS,brillo);
  GLfloat color[] = {0.1,0.1,0.1};
  glMaterialfv(GL_FRONT, GL_EMISSION, color);

  if(texturePtr!=NULL) 
    texturePtr->activate();
  else
    glDisable(GL_TEXTURE_2D);


}



void Material :: setAmbient(GLfloat amb[MATERIAL_ARRAY_SIZE -1]) {
  for(int i=0;i<MATERIAL_ARRAY_SIZE;i++)
    this->amb[i] = amb[i];
}

void Material :: setDiffuse(GLfloat dis[MATERIAL_ARRAY_SIZE -1]) {
  for(int i=0;i<MATERIAL_ARRAY_SIZE;i++)
    this->dis[i] = dis[i];
}

void Material :: setSpecular(GLfloat spe[MATERIAL_ARRAY_SIZE -1]) {
  for(int i=0;i<MATERIAL_ARRAY_SIZE;i++)
    this->spe[i] = spe[i];
}

void Material :: setBrightness(GLfloat brillo) {
  this->brillo = brillo;
}


GLfloat * Material :: getAmbient() const{
  return (GLfloat *)this->amb;
}

GLfloat * Material :: getDiffuse() const{
  return (GLfloat *)this->dis;
}

GLfloat * Material :: getSpecular() const{
  return (GLfloat *)this->spe;
}

GLfloat Material :: getBrillo() const {
  return this->brillo;
}

