#include "vertex.h"
#include <vector>

using namespace std;

#ifndef _MALLATVT_H_
#define _MALLATVT_H_

class MallaTVT {

private:
      //Variable estatica de clase que determina
      //como se dibuja el modelo. Se comparte con todas las
      //clases
  static int model;
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
public:
  void initializeObject(const char * filename);
  void initializeRotationalObject(const char * filename);
  void setModel(int model);
  void draw();
  int getModel() const;
  int getInitialVerticesNum() const;

};


#endif
