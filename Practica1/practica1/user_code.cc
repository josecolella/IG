//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"
#include "file_ply_stl.h"

//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************

void draw_cube()
{

    std::vector<float> vertices_ply;
    std::vector<int> caras_ply;

    ply::read("ant",vertices_ply,caras_ply);
  //  GLfloat Vertices[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};

    glColor3f(0,1,0);
    glPointSize(4);

    glBegin(GL_POINTS);
    for (unsigned i=0;i<vertices_ply.size();i++){
        glVertex3fv((GLfloat *) &vertices_ply[i]);
        }
    for(unsigned i=0;i<caras_ply.size();i++){
      glVertex3iv((GLint *) &caras_ply[i]);
    }
    glEnd();


}

//**************************************************************************
// Funcion para dibujar vertices
//***************************************************************************

void draw_vertices(vector<float> &Vertices)
{

    glColor3f(0,1,0);
    glPointSize(4);

    glBegin(GL_POINTS);
    for (unsigned i=0;i<Vertices.size();i++){
        glVertex3fv((GLfloat *) &Vertices[i]);
        }
    glEnd();
}

