#include "vertex.h"
#include "MallaTVT.h" //Mallas para crear la lata
#include <vector>
#include <GL/glut.h>
#include "visualtype.h" //For enum
#include "Texture.h"

using namespace std;


#ifndef _BEVERAGECAN_H_
#define _BEVERAGECAN_H_

class BeverageCan
{
    private:
      //OpenGL puede gestionar mas de
      //una textura a la vez. Para diferenciarlas
      //usa un valor entero unico para cada una de ellas
      MallaTVT can_body;
      MallaTVT can_bottom;
      MallaTVT can_top;
      Texture * texturePtr;
    public:
      BeverageCan(const char * textureFile);
      ~BeverageCan();
      void draw(visual_t visualization);

};


#endif