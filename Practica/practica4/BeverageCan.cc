#include "BeverageCan.h"
#include <iostream>

using namespace std;

const char * BeverageCan :: textureFile = "text-lata-1.jpg";

BeverageCan :: BeverageCan()
{
  isLight = true;
  can_body = new CanBody(textureFile);
  this->can_bottom.initializeRotationalObject("lata-psup.ply");
  this->can_top.initializeRotationalObject("lata-pinf.ply");

  //texturePtr = new Texture(textureFile);


}

BeverageCan :: ~BeverageCan()
{
  delete texturePtr;
  delete can_body;
}

void BeverageCan :: draw(visual_t visualization) {

  //texturePtr->activate();
  this->can_body->draw(visualization);
  this->can_bottom.draw(visualization);
  this->can_top.draw(visualization);


}