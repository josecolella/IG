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


void draw_branch()
{

  glPointSize(4);

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


  glBegin(GL_LINES);
  for (int i = 0; i < 9; i++)
  {
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

  }
  glEnd();

}

void draw_three_trunk()
{

//Hacer Copia de configuracion
draw_branch();
//Left-Branch
glPushMatrix();
    //Insertamos el tronco izquierdo
    glPushMatrix();
        glTranslatef(-0.5,3.0,0.0);
        glScalef(0.5,0.5,0.5);
        draw_branch();
        //Insertamos segundo tronco izquierdo
        glPushMatrix();
            glTranslatef(-0.5,3.0,0.0);
            glScalef(0.5,0.5,0.5);
            draw_branch();
            //Insertamos tronco a la izquierda
            glPushMatrix();
                glTranslatef(-0.5,3.0,0.0);
                glScalef(0.5,0.5,0.5);
                draw_branch();
                //Insertamos tronco a la derecha
                glPushMatrix();
                    glTranslatef(1.5,2.5,0.0);
                    glScalef(0.7,0.7,0.7);
                    glRotatef(-45.0,0.0,0.0,1.0);
                    draw_branch();
                    glPushMatrix();
                    //Insertamos tronco a la derecha
                        glTranslatef(1.5,2.5,0.0);
                        glScalef(0.7,0.7,0.7);
                        glRotatef(-45.0,0.0,0.0,1.0);
                        draw_branch();
                    glPopMatrix();
                    glPushMatrix();
                    //Insertamos a la izquierda
                        glTranslatef(-0.5,3.0,0.0);
                        glScalef(0.5,0.5,0.5);
                        draw_branch();
                    glPopMatrix();
                glPopMatrix();
                //Insertamos tronco a la izquierda
                glPushMatrix();
                    glTranslatef(-0.5,3.0,0.0);
                    glScalef(0.5,0.5,0.5);
                    draw_branch();
                glPopMatrix();
            glPopMatrix();
            //Insertamos tronco a la derecha
            glPushMatrix();
                glTranslatef(1.5,2.5,0.0);
                glScalef(0.7,0.7,0.7);
                glRotatef(-45.0,0.0,0.0,1.0);
                draw_branch();
                //Insertamos tronco a la derecha
                glPushMatrix();
                    glTranslatef(1.5,2.5,0.0);
                    glScalef(0.7,0.7,0.7);
                    glRotatef(-45.0,0.0,0.0,1.0);
                    draw_branch();
                    glPushMatrix();
                    //Insertamos tronco a la derecha
                        glTranslatef(1.5,2.5,0.0);
                        glScalef(0.7,0.7,0.7);
                        glRotatef(-45.0,0.0,0.0,1.0);
                        draw_branch();
                    glPopMatrix();
                    glPushMatrix();
                    //Insertamos a la izquierda
                        glTranslatef(-0.5,3.0,0.0);
                        glScalef(0.5,0.5,0.5);
                        draw_branch();
                    glPopMatrix();
                glPopMatrix();
                //Insertamos tronco a la izquierda
                glPushMatrix();
                    glTranslatef(-0.5,3.0,0.0);
                    glScalef(0.5,0.5,0.5);
                    draw_branch();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        //Insertamos tronco a la derecha
        glPushMatrix();
            glTranslatef(1.5,2.5,0.0);
            glScalef(0.7,0.7,0.7);
            glRotatef(-45.0,0.0,0.0,1.0);
            draw_branch();
            //Insertamos tronco a la derecha
            glPushMatrix();
                //Insertamos tronco a la derecha
                 glTranslatef(1.5,2.5,0.0);
                 glScalef(0.7,0.7,0.7);
                 glRotatef(-45.0,0.0,0.0,1.0);
                 draw_branch();
                 glPushMatrix();
                    //Insertamos un tronco derecho
                    glTranslatef(1.5,2.5,0.0);
                    glScalef(0.7,0.7,0.7);
                    glRotatef(-45.0,0.0,0.0,1.0);
                    draw_branch();
                    glPushMatrix();
                    //Insertamos tronco a la derecha
                        glTranslatef(1.5,2.5,0.0);
                        glScalef(0.7,0.7,0.7);
                        glRotatef(-45.0,0.0,0.0,1.0);
                        draw_branch();
                    glPopMatrix();
                    glPushMatrix();
                    //Insertamos a la izquierda
                        glTranslatef(-0.5,3.0,0.0);
                        glScalef(0.5,0.5,0.5);
                        draw_branch();
                        glPushMatrix();
                        //Insertamos tronco a la derecha
                            glTranslatef(1.5,2.5,0.0);
                            glScalef(0.7,0.7,0.7);
                            glRotatef(-45.0,0.0,0.0,1.0);
                            draw_branch();
                        glPopMatrix();
                        glPushMatrix();
                        //Insertamos a la izquierda
                            glTranslatef(-0.5,3.0,0.0);
                            glScalef(0.5,0.5,0.5);
                            draw_branch();
                        glPopMatrix();
                    glPopMatrix();
                 glPopMatrix();
                 glPushMatrix();
                  //Insertamos un tronco izquierdo
                    glTranslatef(-0.5,3.0,0.0);
                    glScalef(0.5,0.5,0.5);
                    draw_branch();
                    glPushMatrix();
                    //Insertamos tronco a la derecha
                        glTranslatef(1.5,2.5,0.0);
                        glScalef(0.7,0.7,0.7);
                        glRotatef(-45.0,0.0,0.0,1.0);
                        draw_branch();
                    glPopMatrix();
                    glPushMatrix();
                    //Insertamos a la izquierda
                        glTranslatef(-0.5,3.0,0.0);
                        glScalef(0.5,0.5,0.5);
                        draw_branch();
                    glPopMatrix();
                 glPopMatrix();
            glPopMatrix();
            //Insertamos tronco a la izquierda
            glPushMatrix();
                glTranslatef(-0.5,3.0,0.0);
                glScalef(0.5,0.5,0.5);
                draw_branch();
                //Insertar tronco derecho
                glPushMatrix();
                    glTranslatef(1.5,2.5,0.0);
                    glScalef(0.7,0.7,0.7);
                    glRotatef(-45.0,0.0,0.0,1.0);
                    draw_branch();
                    glPushMatrix();
                    //Insertamos tronco a la derecha
                        glTranslatef(1.5,2.5,0.0);
                        glScalef(0.7,0.7,0.7);
                        glRotatef(-45.0,0.0,0.0,1.0);
                        draw_branch();
                    glPopMatrix();
                    glPushMatrix();
                    //Insertamos a la izquierda
                        glTranslatef(-0.5,3.0,0.0);
                        glScalef(0.5,0.5,0.5);
                        draw_branch();
                    glPopMatrix();
                 glPopMatrix();
                 //Insertar tronco izquierdo
                 glPushMatrix();
                    glTranslatef(-0.5,3.0,0.0);
                    glScalef(0.5,0.5,0.5);
                    draw_branch();
                 glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    //Guardamos la configuracion del tronco primero derecho
    glPushMatrix();
        //Le insertamos un tronco derecho
        glTranslatef(1.5,2.5,0.0);
        glScalef(0.7,0.7,0.7);
        glRotatef(-45.0,0.0,0.0,1.0);
        draw_branch();
        //Le insertamos un tronco derecho
        glPushMatrix();
            glTranslatef(1.5,2.5,0.0);
            glScalef(0.7,0.7,0.7);
            glRotatef(-45.0,0.0,0.0,1.0);
            draw_branch();
            glPushMatrix();
                //Le insertamos un tronco derecho
                glTranslatef(1.5,2.5,0.0);
                glScalef(0.7,0.7,0.7);
                glRotatef(-45.0,0.0,0.0,1.0);
                draw_branch();
                glPushMatrix();
                    //Le insertamos un tronco derecho
                    glTranslatef(1.5,2.5,0.0);
                    glScalef(0.7,0.7,0.7);
                    glRotatef(-45.0,0.0,0.0,1.0);
                    draw_branch();
                    glPushMatrix();
                        //Le insertamos un tronco derecho
                        glTranslatef(1.5,2.5,0.0);
                        glScalef(0.7,0.7,0.7);
                        glRotatef(-45.0,0.0,0.0,1.0);
                        draw_branch();
                    glPopMatrix();
                    glPushMatrix();
                        //Le insertamos un tronco izquierdo
                        glTranslatef(-0.5,3.0,0.0);
                        glScalef(0.5,0.5,0.5);
                        draw_branch();
                    glPopMatrix();
                glPopMatrix();
                glPushMatrix();
                    //Le insertamos un tronco izquierdo
                    glTranslatef(-0.5,3.0,0.0);
                    glScalef(0.5,0.5,0.5);
                    draw_branch();
                    glPushMatrix();
                        //Le insertamos un tronco derecho
                        glTranslatef(1.5,2.5,0.0);
                        glScalef(0.7,0.7,0.7);
                        glRotatef(-45.0,0.0,0.0,1.0);
                        draw_branch();
                    glPopMatrix();
                    glPushMatrix();
                        //Le insertamos un tronco izquierdo
                        glTranslatef(-0.5,3.0,0.0);
                        glScalef(0.5,0.5,0.5);
                        draw_branch();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
            glPushMatrix();
                //Le insertamos un tronco izquierdo
                glTranslatef(-0.5,3.0,0.0);
                glScalef(0.5,0.5,0.5);
                draw_branch();
                glPushMatrix();
                    //Le insertamos un tronco derecho
                    glTranslatef(1.5,2.5,0.0);
                    glScalef(0.7,0.7,0.7);
                    glRotatef(-45.0,0.0,0.0,1.0);
                    draw_branch();
                    glPushMatrix();
                        //Le insertamos uno derecho
                        glTranslatef(1.5,2.5,0.0);
                        glScalef(0.7,0.7,0.7);
                        glRotatef(-45.0,0.0,0.0,1.0);
                        draw_branch();
                    glPopMatrix();
                    glPushMatrix();
                        //Le insertamos uno izquierdo
                        glTranslatef(-0.5,3.0,0.0);
                        glScalef(0.5,0.5,0.5);
                        draw_branch();
                    glPopMatrix();
                glPopMatrix();
                glPushMatrix();
                    //Le insertamos un tronco izquiedo
                    glTranslatef(-0.5,3.0,0.0);
                    glScalef(0.5,0.5,0.5);
                    draw_branch();
                    glPushMatrix();
                        //Le insertamos un tronco derecho
                        glTranslatef(1.5,2.5,0.0);
                        glScalef(0.7,0.7,0.7);
                        glRotatef(-45.0,0.0,0.0,1.0);
                        draw_branch();
                    glPopMatrix();
                    glPushMatrix();
                        //Le insertamos un tronco izquierdo
                        glTranslatef(-0.5,3.0,0.0);
                        glScalef(0.5,0.5,0.5);
                        draw_branch();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        //Le insertamos un tronco izquierdo
        glPushMatrix();
            glTranslatef(-0.5,3.0,0.0);
            glScalef(0.5,0.5,0.5);
            draw_branch();
            //Le insertamos un tronco derecho
            glPushMatrix();
                glTranslatef(1.5,2.5,0.0);
                glScalef(0.7,0.7,0.7);
                glRotatef(-45.0,0.0,0.0,1.0);
                draw_branch();
                //Le insertamos un tronco derecho
                glPushMatrix();
                    glTranslatef(1.5,2.5,0.0);
                    glScalef(0.7,0.7,0.7);
                    glRotatef(-45.0,0.0,0.0,1.0);
                    draw_branch();
                    //Le insertamos un tronco derecho
                    glPushMatrix();
                        glTranslatef(1.5,2.5,0.0);
                        glScalef(0.7,0.7,0.7);
                        glRotatef(-45.0,0.0,0.0,1.0);
                        draw_branch();
                    glPopMatrix();
                    //Le insertamos un tronco izquierdo
                    glPushMatrix();
                        glTranslatef(-0.5,3.0,0.0);
                        glScalef(0.5,0.5,0.5);
                        draw_branch();
                    glPopMatrix();
                glPopMatrix();
                //Le insertamos un tronco izquierdo
                glPushMatrix();
                    glTranslatef(-0.5,3.0,0.0);
                    glScalef(0.5,0.5,0.5);
                    draw_branch();
                    glPushMatrix();
                        //Le insertamos un tronco derecho
                        glTranslatef(1.5,2.5,0.0);
                        glScalef(0.7,0.7,0.7);
                        glRotatef(-45.0,0.0,0.0,1.0);
                        draw_branch();
                    glPopMatrix();
                    glPushMatrix();
                        //Le insertamos un tronco izquierdo
                        glTranslatef(-0.5,3.0,0.0);
                        glScalef(0.5,0.5,0.5);
                        draw_branch();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
            //Le insertamos un tronco izquierdo
            glPushMatrix();
                glTranslatef(-0.5,3.0,0.0);
                glScalef(0.5,0.5,0.5);
                draw_branch();
                glPushMatrix();
                    //Le insertamos un tronco derecho
                    glTranslatef(1.5,2.5,0.0);
                    glScalef(0.7,0.7,0.7);
                    glRotatef(-45.0,0.0,0.0,1.0);
                    draw_branch();
                glPopMatrix();
                glPushMatrix();
                    //Le insertamos un tronco izquierdo
                    glTranslatef(-0.5,3.0,0.0);
                    glScalef(0.5,0.5,0.5);
                    draw_branch();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
glPopMatrix();

}

void draw_cube()
{

    //Codigo que permite visualizar un vector de flotantes en modo puntos
  //GLfloat Vertices[9][3]= {{0.0,0.0,0.0},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};
  //draw_branch();
draw_three_trunk();
}





void draw_small_branch(float rotation, float x_rotation, float y_rotation, float trans_x, float trans_y)
{
  glPushMatrix();
      glTranslatef(trans_x,trans_y,0.0);
      glScalef(0.5,0.5,0.5);
      draw_branch();
    glPopMatrix();
}
