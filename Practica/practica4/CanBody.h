#include "SpecializedMallaTVT.h"
#include "Texture.h"
#include "Material.h"
#include "visualtype.h"

#ifndef _CANBODY_H_
#define _CANBODY_H_

class CanBody {
    private:
        SpecializedMallaTVT can_body;
        Material * texturePtr;
    public:
        CanBody(const char * textureFile);
        CanBody(const char * filename, const char * textureFile);
        ~CanBody();
        void draw(visual_t visualization);
};

#endif


