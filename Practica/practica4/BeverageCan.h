#include "vertex.h"
#include "MallaTVT.h" //Mallas para crear la lata
#include <vector>
#include <GL/glut.h>
#include "visualtype.h" //For enum

using namespace std;


#ifndef _BEVERAGECAN_H_
#define _BEVERAGECAN_H_

class BeverageCan
{
    private:
      MallaTVT can_body;
      MallaTVT can_bottom;
      MallaTVT can_top;
    public:
      BeverageCan(){ };
      BeverageCan(const char * body_ply,const char * bottom_ply,const char * top_ply);
      void draw(visual_t visualization);

};


#endif