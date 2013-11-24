//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"

//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************



void figura_simple() {


  glPolygonMode(GL_FRONT,GL_LINE);

  glBegin(GL_LINE_LOOP);
    glVertex2f(0.0,0.0);
    glVertex2f(2.0,0.0);
    glVertex2f(2.0,2.0);
    glVertex2f(0.0,2.0);
  glEnd();

  glBegin(GL_TRIANGLES);
    glVertex2f(0.2,0.2);
    glVertex2f(0.6,0.2);
    glVertex2f(0.4,0.8);
  glEnd();


}

//Funcion recursiva para dibujar la figura
void figura_compleja_rec(int depth)
{

  if(depth == 0)
  {
    figura_simple();
  }
  else{
    glPushMatrix();
      glTranslatef(2.0,0.0,0.0);
      glScalef(0.5,0.5,0.5);
      figura_simple();
      figura_compleja_rec(depth-1);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(2.0,1.0,0.0);
      glScalef(0.5,0.5,0.5);
      figura_simple();
      figura_compleja_rec(depth-1);
    glPopMatrix();

   figura_compleja_rec(depth-1);
  }

}



void figura_compleja()
{
  figura_simple();
  glPushMatrix();
    glTranslatef(3.0,4.0,0.0);
    glScalef(1.0,1.0,1.0);
    glRotatef(135.0,0.0,0.0,1.0);
    figura_simple();
  glPopMatrix();

}


void draw_cube()
{

  figura_compleja_rec(3);
}

