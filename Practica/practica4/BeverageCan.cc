#include "BeverageCan.h"



BeverageCan :: BeverageCan(const char *body_ply, const char *bottom_ply, const char *top_ply)
: BeverageCan()
{

  this->can_body.initializeRotationalObject(body_ply);
  this->can_bottom.initializeRotationalObject(bottom_ply);
  this->can_bottom.initializeRotationalObject(top_ply);
}



void BeverageCan :: draw() {
  this->can_body.draw();
  this->can_bottom.draw();
  this->can_top.draw();
}