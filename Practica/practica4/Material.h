#include "Texture.h"
#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>

#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#define MATERIAL_ARRAY_SIZE 4

class Material
 {
    private:
        bool isIlluminated;
        Texture * texturePtr;
        GLuint idTex;
        GLfloat amb[MATERIAL_ARRAY_SIZE], //Primeros tres componentes son RGB mas opaco 1
                dis[MATERIAL_ARRAY_SIZE],
                spe[MATERIAL_ARRAY_SIZE],
                brillo[MATERIAL_ARRAY_SIZE];

    public:
        Material();
        Material(const char * materialFile);
        ~Material();
        void activate();

     /* data */
 };
#endif