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

 GLfloat pos[4] = {1.0,1.0,1.0,1.0};

 glPushMatrix();
 glRotatef( latitud, 0.0, 1.0, 0.0 ) ;
 glRotatef( longitud, 1.0, 0.0, 0.0 ) ;
 glLightfv(this->lightIndex,GL_POSITION, pos);
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



void LightSource :: changeBeta(GLfloat value)
{
 if (latitud+1.0>=90.0)
  latitud = 90.0;
else
  latitud +=1.0;
}
void LightSource :: changeAlpha(GLfloat value)
{
  longitud += 1.0;
}