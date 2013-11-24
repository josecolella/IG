#include "user_code.h"
#include "file_ply_stl.h"


/**
 * La funcion tronco dibuja un tronco basico de un arbol
 */
void tronco()
{

  glPointSize(4);
  glLineWidth(3);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


  glBegin(GL_LINE_LOOP);
    glColor3f(0,0,1);
    glVertex2f(0.0,0.0); //0
    glVertex2f(1.0,0.0); //1
    glVertex2f(1.0,1.0); //2
    glVertex2f(2.0,2.0); //3
    glVertex2f(1.5,2.5); //4
    glVertex2f(0.5,1.5); //5
    glVertex2f(0.0,3.0); //6
    glVertex2f(-0.5,3.0); //7
    glVertex2f(0.0,1.5); //8
  glEnd();

}

/**
 * La funcion arbol dibuja un arbol con profundidad
 * dependiente del parametro de entrada
 * @param depth La profundidad del arbol
 */
void arbol(int depth)
{

  if(depth == 0)
    //Dibujar el tronco
    tronco();
  else{
    glPushMatrix();
        //Insertamos tronco a la derecha
        glTranslatef(1.5,2.5,0.0);
        glScalef(0.7,0.7,0.7);
        glRotatef(-45.0,0.0,0.0,1.0);
        tronco();
        arbol(depth - 1);
    glPopMatrix();
    glPushMatrix();
        //Insertamos a la izquierda
        glTranslatef(-0.5,3.0,0.0);
        glScalef(0.5,0.5,0.5);
        tronco();
        arbol(depth - 1);
    glPopMatrix();
    arbol(depth-1);
  }



}


void draw_cube()
{
  //Llamada para la creacion del arbol
  arbol(6);
}
