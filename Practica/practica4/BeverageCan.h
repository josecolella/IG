#include "vertex.h"
#include "SpecializedMallaTVT.h" //Mallas para crear la lata
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
      static const char * textureFile;
      bool isLight;
      SpecializedMallaTVT can_body;
      SpecializedMallaTVT can_bottom;
      SpecializedMallaTVT can_top;
      Texture * texturePtr;
    public:
      BeverageCan();
      ~BeverageCan();
      void draw(visual_t visualization);

};


#endif