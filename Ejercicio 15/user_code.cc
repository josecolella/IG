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


void gancho() {


  glPolygonMode(GL_FRONT,GL_FILL);

  glBegin(GL_LINE_STRIP);
    glVertex2f(0.0,0.0);
    glVertex2f(1.0,0.0);
    glVertex2f(1.0,1.0);
    glVertex2f(0.0,1.0);
    glVertex2f(0.0,2.0);
  glEnd();

}

/**
  Este codigo crea el poligono usando glPushMatrix() y glPopMatrix()
*/
void gancho_x4_1()
{

    gancho();
    glPushMatrix();
      glTranslatef(0.0,2.0,0.0);
      glRotatef(90.0,0.0,0.0,1.0);
      gancho();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-2.0,2.0,0.0);
      glRotatef(180.0,0.0,0.0,1.0);
      gancho();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-2.0,-0.0,0.0);
      glRotatef(-90.0,0.0,0.0,1.0);
      gancho();
    glPopMatrix();



}

/**
 * Este metodo crea el poligono sin usar glPushMatirix() y glPopMatrix(0)
 */
void gancho_x4_2()
{
  //Las matrices de transformaciones se van acumulando
  //si no se usa glPushMatrix() y glPopMatrix()
  gancho();
  glTranslatef(0.0,2.0,0.0);
  glRotatef(90.0,0.0,0.0,1.0);
  gancho();
  glTranslatef(0.0,2.0,0.0);
  glRotatef(90.0,0.0,0.0,1.0);
  gancho();
  glTranslatef(0.0,2.0,0.0);
  glRotatef(90.0,0.0,0.0,1.0);
  gancho();
}

void draw_cube()
{

  gancho_x4_2();
}

