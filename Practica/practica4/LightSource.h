#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
#include <string.h>
#include "vertex.h"


#ifndef _LIGHT_SOURCE_H_
#define _LIGHT_SOURCE_H_
#define INI_SIZE 2

class LightSource
{
    private:
        GLenum lightIndex; //Esta variable diferencia entre GL_LIGHT0,GL_LIGHT1
        GLfloat iniPositions[INI_SIZE];
        GLfloat lightPositions[INI_SIZE]; // long - (0 -360) y lang (-90 y 90)
        _vertex3f ambientVector;
        _vertex3f diffuseVector;
        _vertex3f specularVector;
    public:
        LightSource(GLenum lightIndex, GLfloat * iniPositions, _vertex3f type);
        void activate();

    
};


#endif