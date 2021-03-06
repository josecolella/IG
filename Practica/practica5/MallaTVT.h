#include "vertex.h"
#include <vector>
#include <GL/glut.h>
#include "visualtype.h" //For enum
#include <math.h>
#include "Material.h"

using namespace std;

#ifndef _MALLATVT_H_
#define _MALLATVT_H_
#define MATERIAL_ARRAY_SIZE 4

class MallaTVT {

protected:
      //Variable estatica de clase que determina
      //como se dibuja el modelo. Se comparte con todas las
      //clases
      // model = 1 POINT
      // model = 2 LINE
      // model = 3 FILL
      // model = 4 CHECKERED
      // model = 5 ILUM_PLANO
      // model = 6
  int numInitialVertices;
      //Los vertices del modelo ply
  vector<float> vertices_ply;
        //Las caras del modelo ply
  vector<int> caras_ply;
        //Vector de vertices de flotantes que representan
        //los vertuces
  vector< _vertex3f > Vertices;
        //Vector de vertices de enteros que representa
        //las caras
  vector< _vertex3ui > caras;
      	//Vector de vertices de normales
  vector< _vertex3f > normal_vertices;
      	//Vector de caras de normales
  vector< _vertex3f > normal_caras;
        //Vector de texturas
  vector<_vertex2f> vector_texturas;
  Material * materialPtr;
public:
  MallaTVT();
  MallaTVT(const char * textureFile);
  ~MallaTVT();
  void initializeObject(const char * filename);
  void initializeRotationalObject(const char * filename);
  void initializeRotationalObject2(const char * filename);
  void draw(visual_t visualization);
  int getInitialVerticesNum() const;
  void setAmbient(GLfloat amb[MATERIAL_ARRAY_SIZE -1]);
  void setDiffuse(GLfloat dis[MATERIAL_ARRAY_SIZE -1]);
  void setSpecular(GLfloat spe[MATERIAL_ARRAY_SIZE -1]);
  void setBrightness(GLfloat brillo);
};


#endif
