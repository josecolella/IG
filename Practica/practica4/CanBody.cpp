#include "CanBody.h"


CanBody :: CanBody(const char *textureFile) {
    can_body.initializeRotationalObject("lata-pcue.ply");
    texturePtr = new Material(textureFile);
}

CanBody :: CanBody(const char *filename, const char *textureFile) {
    can_body.initializeRotationalObject(filename);
    texturePtr = new Material(textureFile);
    GLfloat dis[3] = {0.7,0.7,0.7};
    texturePtr->setDiffuse(dis);
    texturePtr->setSpecular(dis);
    texturePtr->setBrightness(30);
}

CanBody :: ~CanBody()
{
    delete texturePtr;
}


void CanBody :: draw(visual_t visualization)
{   
    GLfloat color[4] =  {0.9,0.8,0.8,1};
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

    texturePtr->activate();
    this->can_body.draw(visualization);
}