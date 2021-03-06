#include "vertex.h"
#include <vector>

using namespace std;

#ifndef _MALLATVT_H_
#define _MALLATVT_H_

class MallaTVT {

	private:
        int model;
        //Los vertices del modelo ply
	    vector<float> vertices_ply;
        //Las caras del modelo ply
        vector<int> caras_ply;
        //Vector de vectores de flotantes que representan
        //los vertuces
        vector< _vertex3f > Vertices;
        //Vector de vectores de enteros que representa
        //las caras
        vector< _vertex3ui > caras;
    public:
        MallaTVT();
        void initializeVerticesAndFaces(const char * filename);
        void setModel(int model);
        void draw();
        int getModel() const;

};


#endif
