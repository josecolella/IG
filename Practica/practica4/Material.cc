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

    // if(isIlluminated){
          glEnable(GL_LIGHTING);
          glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
          glEnable(GL_NORMALIZE);

          glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
          glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
       
          // parte delantera
          glMaterialfv(GL_FRONT,GL_AMBIENT,(GLfloat *) & amb);
          glMaterialfv(GL_FRONT,GL_DIFFUSE,(GLfloat *) & dis);
          glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) & spe);
          glMaterialf(GL_FRONT,GL_SHININESS,brillo);
       

    //    } else {
    //       glDisable(GL_LIGHTING);
    //       //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (GLfloat *) & color);
    //    }
         
       if(texturePtr!=NULL) 
          texturePtr->activate();


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