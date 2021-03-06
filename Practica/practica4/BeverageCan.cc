#include "BeverageCan.h"
#include <iostream>

using namespace std;

const char * BeverageCan :: textureFile = "text-lata-1.jpg";

BeverageCan :: BeverageCan()
{
  isLight = true;
  can_body = new MallaTVT(textureFile);
  can_body->initializeRotationalObject2("lata-pcue.ply");

  can_bottom = new MallaTVT();
  can_bottom->initializeRotationalObject2("lata-psup.ply");

  can_top = new MallaTVT();
  can_top->initializeRotationalObject2("lata-pinf.ply");


}

BeverageCan :: ~BeverageCan()
{
  delete can_body;
  delete can_top;
  delete can_bottom;
}

void BeverageCan :: draw(visual_t visualization) {

  GLfloat whiteSpecular[] = {1.0, 1.0, 1.0};
  GLfloat blackSpecular[] = {0.0,0.0,0.0};
  GLfloat someDiffuse[] = {0.4,0.4,0.4};
  GLfloat someDiffuse1[] = {0.6,0.6,0.6};
  GLfloat silverAmbient[] = {0.19225,0.19225,0.19225};
  GLfloat silverDiffuse[] = {0.50754,0.50754,0.50754};
  GLfloat silverSpecular[] = {0.508273,0.508273,0.508273};

  can_body->setAmbient(silverAmbient);
  can_body->setDiffuse(silverDiffuse);
  can_body->setSpecular(silverSpecular);
  can_body->setBrightness(0);
  can_body->draw(visualization);

  float shiny = 100.0;
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
  can_bottom->setAmbient(silverAmbient);
  can_bottom->setDiffuse(silverDiffuse);
  can_bottom->setSpecular(silverDiffuse);
  can_bottom->setBrightness(10);
  can_bottom->draw(visualization);

  can_top->setAmbient(silverAmbient);
  can_top->setDiffuse(silverDiffuse);
  can_top->setSpecular(silverDiffuse);
  can_top->setBrightness(30);
  can_top->draw(visualization);


}