#include "LightSource.h"

LightSource :: LightSource(GLenum lightIndex, GLfloat longitud, GLfloat latitud, _vertex3f color, light_t type, GLfloat position[4]){

  this->lightIndex = lightIndex;
  this->longitud = longitud;
  this->latitud = latitud;
  this->color = color;
  this->type = type;
  for(int i=0;i<4;i++)
    this->position[i] = position[i];


}


void LightSource :: activate()
{
 glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

 glEnable(GL_LIGHTING);
 glEnable(this->lightIndex);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity() ;

 glPushMatrix();
 glRotatef( latitud, 0.0, 1.0, 0.0 ) ;
 glRotatef( longitud, 1.0, 0.0, 0.0 ) ;
 glLightfv(this->lightIndex,GL_POSITION, this->position);
 glLightfv(this->lightIndex, GL_AMBIENT, (GLfloat *) & color);
 glLightfv(this->lightIndex, GL_SPECULAR, (GLfloat *) &color);
 glLightfv(this->lightIndex, GL_DIFFUSE, (GLfloat *) &color);
 glPopMatrix() ;
}


void LightSource :: disactivate()
{
  glPushMatrix();
  glDisable(GL_LIGHTING);
  glDisable(this->lightIndex);
  glPopMatrix();
}



void LightSource :: increaseBeta()
{
 longitud += 3.0;
}

void LightSource :: increaseAlpha(){
  latitud += 3.0;
}
void LightSource :: decreaseBeta()
{
  longitud -= 3.0;
}

void LightSource :: decreaseAlpha()
{
  latitud -= 3.0;
}