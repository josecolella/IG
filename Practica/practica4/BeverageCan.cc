#include "BeverageCan.h"



BeverageCan :: BeverageCan(const char * textureFile)
{
  this->can_body.initializeRotationalObject("lata-pcue.ply");
  this->can_bottom.initializeRotationalObject("lata-psup.ply");
  this->can_bottom.initializeRotationalObject("lata-pinf.ply");

  texturePtr = new Texture(textureFile);

}

BeverageCan :: ~BeverageCan()
{
  delete texturePtr;
}

void BeverageCan :: draw(visual_t visualization) {
  glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping ( NEW )
    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                   // Black Background
    glClearDepth(1.0f);                         // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective

  this->can_body.draw(visualization);
  this->can_bottom.draw(visualization);
  this->can_top.draw(visualization);


}