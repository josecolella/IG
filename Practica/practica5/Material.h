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
                spe[MATERIAL_ARRAY_SIZE];
        GLfloat brillo;

    public:
        Material();
        Material(const char * materialFile);
        ~Material();
        void activate();
        void setAmbient(GLfloat amb[MATERIAL_ARRAY_SIZE -1]);
        void setDiffuse(GLfloat dis[MATERIAL_ARRAY_SIZE -1]);
        void setSpecular(GLfloat spe[MATERIAL_ARRAY_SIZE -1]);
        void setBrightness(GLfloat brillo);
        GLfloat * getAmbient() const;
        GLfloat * getDiffuse() const;
        GLfloat * getSpecular() const;
        GLfloat getBrillo() const;
 };
#endif