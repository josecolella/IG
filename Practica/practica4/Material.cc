#include "Material.h"


Material :: Material()
{
  amb[3] = dis[3] = spe[3] = brillo[3] = 1.0;
}
Material :: Material(const char * materialFile)
{
  texturePtr = NULL;
  texturePtr = new Texture(materialFile);
  amb[3] = dis[3] = spe[3] = brillo[3] = 1.0;
}

Material :: ~Material()
{
  delete texturePtr;
}