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

//**************************************************************************
// Funcion para dibujar vertices
//***************************************************************************

void draw_vertices(vector< _vertex3f > &Vertices, vector<_vertex3ui> caras)
{

  glColor3f(0,1,0);
  glPointSize(5);
  glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < caras.size(); i++)
  {
    glVertex3f(Vertices[caras[i]._0].x,Vertices[caras[i]._0].y,Vertices[caras[i]._0].z);
    glVertex3f(Vertices[caras[i]._1].x,Vertices[caras[i]._1].y,Vertices[caras[i]._1].z);
    glVertex3f(Vertices[caras[i]._2].x,Vertices[caras[i]._2].y,Vertices[caras[i]._2].z);

  }
  glEnd();
}


void draw_lines(vector< _vertex3f >&Vertices, vector< _vertex3ui> caras) {

 glColor3f(0,1,0);
 glPointSize(5);
 glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
 glBegin(GL_TRIANGLES);
 for (int i = 0; i < caras.size(); i++)
 {
  glVertex3f(Vertices[caras[i]._0].x,Vertices[caras[i]._0].y,Vertices[caras[i]._0].z);
  glVertex3f(Vertices[caras[i]._1].x,Vertices[caras[i]._1].y,Vertices[caras[i]._1].z);
  glVertex3f(Vertices[caras[i]._2].x,Vertices[caras[i]._2].y,Vertices[caras[i]._2].z);

}
glEnd();
}

void draw_solid(vector< _vertex3f >&Vertices, vector< _vertex3ui> caras) {

 glColor3f(0,1,0);
 glPointSize(5);
 glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
 glBegin(GL_TRIANGLES);
 for (int i = 0; i < caras.size(); i ++)
 {
  glVertex3f(Vertices[caras[i]._0].x,Vertices[caras[i]._0].y,Vertices[caras[i]._0].z);
  glVertex3f(Vertices[caras[i]._1].x,Vertices[caras[i]._1].y,Vertices[caras[i]._1].z);
  glVertex3f(Vertices[caras[i]._2].x,Vertices[caras[i]._2].y,Vertices[caras[i]._2].z);

  }
  glEnd();
}


void draw_changedColor(vector< _vertex3f >&Vertices, vector< _vertex3ui> caras) {


    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < caras.size(); i++)
    {
      if(i % 2 == 0)
        glColor3f(0,0,1);
      else
        glColor3f(1,0,0);

      glVertex3f(Vertices[caras[i]._0].x,Vertices[caras[i]._0].y,Vertices[caras[i]._0].z);
      glVertex3f(Vertices[caras[i]._1].x,Vertices[caras[i]._1].y,Vertices[caras[i]._1].z);
      glVertex3f(Vertices[caras[i]._2].x,Vertices[caras[i]._2].y,Vertices[caras[i]._2].z);

    }
    glEnd();
}