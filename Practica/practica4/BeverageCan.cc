#include "BeverageCan.h"



BeverageCan :: BeverageCan(const char *body_ply, const char *bottom_ply, const char *top_ply)
{
  this->can_body.initializeRotationalObject(body_ply);
  this->can_bottom.initializeRotationalObject(bottom_ply);
  this->can_bottom.initializeRotationalObject(top_ply);
}



void BeverageCan :: draw(visual_t visualization) {
  this->can_body.draw(visualization);
  this->can_bottom.draw(visualization);
  this->can_top.draw(visualization);
}