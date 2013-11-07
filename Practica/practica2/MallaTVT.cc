#include "MallaTVT.h"
#include "file_ply_stl.h"
#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <cmath>

using namespace std;

MallaTVT :: MallaTVT()
{
    /*
       GL_POINT, GL_LINE, GL_FILL
       model == 1 -> draw_cube()
    */
    this->model = 1;
}


void MallaTVT :: initialize(const char * filename)
{
    
  ply::read(filename, vertices_ply, caras_ply);
  for (int i = 0; i < vertices_ply.size(); i +=3)
  {
    _vertex3f tmp;
    tmp.x = vertices_ply[i];
    tmp.y = vertices_ply[i+1];
    tmp.z = vertices_ply[i+2];
    this->Vertices.push_back(tmp); 
  
  }
  //Numero inicial de vertices
  numInitialVertices = Vertices.size();
  printf("%d\n",numInitialVertices);
  for (int i = 0; i < caras_ply.size(); i += 3)
  {
    _vertex3ui tmp;
    tmp._0 = caras_ply[i];
    tmp._1 = caras_ply[i+1];
    tmp._2 = caras_ply[i+2];
    this->caras.push_back(tmp);
  }
  
  float angulo = 0.1745;
  int rotation = ((360 / 10) -1);
  //Hacemos las transformaciones 
  for(int j=0;j<rotation;j++){
	
	for(int i = 0;i < numInitialVertices;i++) {
		_vertex3f tmp;		
		tmp.x = cos(angulo) * Vertices[i].x +  sin(angulo) * Vertices[i].z;
	  	tmp.y = Vertices[i].y;
		tmp.z = -sin(angulo) * Vertices[i].x + cos(angulo) * Vertices[i].z;
		this->Vertices.push_back(tmp);
	}
	angulo += 0.1745;
  }


for(int j=0;j<Vertices.size();j++){
	
	if(j%(numInitialVertices -1) && j != 0){
		   _vertex3ui tmp;
	  	   tmp._0 = j;
		   tmp._1 = j+1;
		   tmp._2 = j+numInitialVertices+1;
		   caras.push_back(tmp);
		   tmp._0 = j;
		   tmp._1 = j+numInitialVertices;
		   tmp._2 = j+numInitialVertices+1;
		   caras.push_back(tmp);
		}	
	   
	}
  

}


void MallaTVT :: setModel(int model){

    this->model = model;
}

void MallaTVT :: draw(){
  
 if(model >= 2 && model <= 5){  
   glPointSize(5);
   switch(this->model) {
    case 2:
        glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
        break;
    case 3:
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        break;
    case 4:
    case 5:
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        break;    
    default:
        glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
        break;
     
    }
   
       glBegin(GL_POINTS);
       for (int i = 0; i < caras.size(); i++)
       {
          if(model == 5){
              if(i % 2 == 0)
                glColor3f(0,0,1);
              else
                glColor3f(1,0,0);
          }
          else
            glColor3f(0,1,0);

          glVertex3f(Vertices[caras[i]._0].x,Vertices[caras[i]._0].y,Vertices[caras[i]._0].z);
	  glVertex3f(Vertices[caras[i]._1].x,Vertices[caras[i]._1].y,Vertices[caras[i]._1].z);
          glVertex3f(Vertices[caras[i]._2].x,Vertices[caras[i]._2].y,Vertices[caras[i]._2].z);

        }
        glEnd();  
    }
    


}


int MallaTVT :: getModel() const {
    return this->model;
}

int MallaTVT :: getInitialVerticesNum() const{
   return this-> numInitialVertices;
} 
