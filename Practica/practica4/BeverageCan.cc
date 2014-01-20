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

  
  can_body->draw(visualization);
  can_bottom->draw(visualization);
  can_top->draw(visualization);


}