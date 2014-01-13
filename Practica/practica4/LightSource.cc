#include "LightSource.h"

LightSource :: LightSource(GLenum lightIndex, GLfloat * iniPositions, _vertex3f type)
{
    this->lightIndex = lightIndex;
    memcpy(this->iniPositions, iniPositions, sizeof(GLfloat) * INI_SIZE);
    this->lightPositions[0] = this->iniPositions[0]; //longitud
    this->lightPositions[1] = this->iniPositions[1]; //latitud
    ambientVector = _vertex3f(0.2,0.2,0.2);
    diffuseVector = type;
    specularVector = type;
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
      glRotatef( this->lightPositions[0], 0.0, 1.0, 0.0 ) ;
      glRotatef( this->lightPositions[1], 1.0, 0.0, 0.0 ) ;
      glLightfv(this->lightIndex,GL_POSITION, pos);
      glLightfv(this->lightIndex, GL_AMBIENT, (GLfloat *) &ambientVector);
      glLightfv(this->lightIndex, GL_SPECULAR, (GLfloat *) &diffuseVector);
      glLightfv(this->lightIndex, GL_DIFFUSE, (GLfloat *) &specularVector);
   glPopMatrix() ;
}


