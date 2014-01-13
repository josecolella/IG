#include "Texture.h"
#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

class Material
 {
    private:
        bool isIlluminated;
        Texture * texturePtr;
        GLuint idTex;
    public:
        Material(const char * materialFile);
        ~Material();
        void activate();
 
     /* data */
 }; 
#endif