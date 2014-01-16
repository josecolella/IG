#include "MallaTVT.h"
#include "visualtype.h"

#ifndef _SPECIALIZEDMALLATVT_H_
#define _SPECIALIZEDMALLATVT_H_

class SpecializedMallaTVT : public MallaTVT
{
  public:
  void initializeRotationalObject(const char * filename);
  void draw(visual_t visualization);
};

#endif