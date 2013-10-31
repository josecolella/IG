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

    //Codigo que permite visualizar un vector de flotantes en modo puntos
  GLfloat Vertices[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};

  glColor3f(0,1,0);
  glPointSize(4);

  glBegin(GL_POINTS);
  for (int i = 0; i < 8; ++i)
  {
    glVertex3fv((GLfloat *) &Vertices[i]);
  }
  glEnd();


}


