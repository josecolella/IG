#include "vertex.h"
#include <vector>
#include <GL/glut.h>
#include "visualtype.h" //For enum
#include "Texture.h"
#include "MallaTVT.h"

using namespace std;


#ifndef _BEVERAGECAN_H_
#define _BEVERAGECAN_H_

class BeverageCan
{
    private:
      //OpenGL puede gestionar mas de
      //una textura a la vez. Para diferenciarlas
      //usa un valor entero unico para cada una de ellas
      static const char * textureFile;
      bool isLight;
      MallaTVT * can_body;
      MallaTVT * can_bottom;
      MallaTVT * can_top;
    public:
      BeverageCan();
      ~BeverageCan();
      void draw(visual_t visualization);

};


#endif