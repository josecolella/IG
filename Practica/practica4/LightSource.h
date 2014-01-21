#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
#include <string.h>
#include "vertex.h"
#include "visualtype.h"


#ifndef _LIGHT_SOURCE_H_
#define _LIGHT_SOURCE_H_



class LightSource
{
    private:
        GLenum lightIndex;
        _vertex3f color;
        light_t type;
        GLfloat longitud;
        GLfloat latitud;
        GLfloat position[4];
    public:
        LightSource(GLenum lightIndex, GLfloat longitud, GLfloat latitud, _vertex3f color, light_t type, GLfloat position[4]);
        void changeBeta(GLfloat value);
        void changeAlpha(GLfloat value);
        void activate();
        void disactivate();

    
};


#endif