#include "BeverageCan.h"

const char * BeverageCan :: textureFile = "text-lata-1.jpg";

BeverageCan :: BeverageCan()
{
  isLight = true;
  this->can_body.initializeRotationalObject2("lata-pcue.ply");
  this->can_bottom.initializeRotationalObject2("lata-psup.ply");
  this->can_bottom.initializeRotationalObject2("lata-pinf.ply");

  texturePtr = new Texture(textureFile);
  texturePtr->activate();

}

BeverageCan :: ~BeverageCan()
{
  delete texturePtr;
}

void BeverageCan :: draw(visual_t visualization) {

  this->can_body.draw(visualization);
  this->can_bottom.draw(visualization);
  this->can_top.draw(visualization);


}