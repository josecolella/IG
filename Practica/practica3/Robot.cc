#include <GL/gl.h>
#include <vector>
#include "Robot.h"



void Robot :: draw_sphere(GLint slices, Glint stacks) {
  glutSolidSphere(1.0,slices, stacks);
}

void Robot :: draw_cube() {
  glutSolidCube(1.0);
}

void Robot :: draw_cylinder(){
  static GLUquadricObj * qobj = NULL;
  if(qobj == NULL) {
    qobj = gluNewQuadric();
  }
  gluQuadricDrawStyle(qobj, GLU_LINE);
  gluCylinder(qobj,0.3,0.3,0.5,25,25);

}

void Robot :: draw_hands(GLfloat z_rotation) {

    glPushMatrix();
      //dibujo las manos
      glTranslatef(0.7,0.0,z_rotation);
      glScalef(1.0,0.1,0.25);
      draw_Scube();
    glPopMatrix();
}



void Robot :: draw_trash_door() {
  glPushMatrix();
    glTranslatef(0.0,-0.5,0.5);
    glPushMatrix();
      glRotatef((GLfloat) torso, 1.0,0.0,0.0);
      glTranslatef(0.0,0.35,0.0);
      glScalef(0.7,0.7,0.005);
      glutWireCube(1.0);
    glPopMatrix();
  glPopMatrix();
}

void Robot :: draw_torso() {
  glutWireCube(1.0);
}



void Robot :: draw_arm((GLfloat) shoulder, (GLfloat) elbow)
{
  glPushMatrix();
  glTranslatef(0.0,0.0,1.0);
  glPushMatrix();
      //Shoulder
      glTranslatef(0.0,0.0,-1.0);
      glScalef(0.3,0.3,0.3);
      draw_sphere(20.0,20.0);
    glPopMatrix();
  glRotatef(-90.0,0.0,1.0,0.0);
  glPushMatrix();
  //Moverse al eje x -1
    glTranslatef(-1.0,0.0,0.0);
    glRotatef((GLfloat) shoulder, 0.0,0.0,1.0);
    glTranslatef(1.0,0.0,0.0);
    glPushMatrix();
        glScalef(2.0,0.3,0.5);
        glutSolidCube(1.0);
    glPopMatrix();
    glTranslatef(1.0,0.0,0.0);
    glPushMatrix();
      glTranslatef(0.0,0.0,-0.25);
      glScalef(0.5,0.5,1.0);
      draw_cylinder();
    glPopMatrix();
    glRotatef((GLfloat) elbow, 0.0,0.0,1.0);
    glTranslatef(1.0,0.0,0.0);
    glPushMatrix();
      glScalef(2.0,0.3,0.5);
      glutSolidCube(1.0);
      glPushMatrix();
        //Dibujo el cilindro que contiene las manos
        glTranslatef(0.5,0.0,-0.5);
        glScalef(0.25,1.5,2.0);
        draw_cylinder();
        glPushMatrix();
          //dibujo las manos
          glTranslatef(0.7,0.0,0.1);
          glScalef(1.0,0.1,0.25);
          draw_Scube();
          glTranslatef(1.0,0.0,0.0);
           glPushMatrix();
            glTranslatef(-0.5,0.0,0.0);
            glScalef(0.2,1.5,1.55);
            glRotatef(90.0,0.0,1.0,0.0);
            draw_cylinder();
          glPopMatrix();
          glScalef(0.8,1.0,1.0);
          draw_Scube();
        glPopMatrix();
        glPushMatrix();
          //dibujo las manos
          glTranslatef(0.7,0.0,0.4);
          glScalef(1.0,0.1,0.25);
          draw_Scube();
          glTranslatef(1.0,0.0,0.0);
          glPushMatrix();
            glTranslatef(-0.5,0.0,0.0);
            glScalef(0.2,1.5,1.55);
            glRotatef(90.0,0.0,1.0,0.0);
            draw_cylinder();
          glPopMatrix();
          glPushMatrix();
            //ASK HELP
            glRotatef((GLfloat) retration, 0.0,0.0,1.0);
            glPushMatrix();
              glTranslatef(0.0,0.0,1.0);
              glScalef(0.8,1.0,1.0);
              draw_Scube();
            glPopMatrix();
          glPopMatrix();
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();
  glPopMatrix();
}
