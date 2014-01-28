#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <iostream>
#include "Robot.h"

using namespace std;


void Robot :: draw_sphere(GLint slices, GLint stacks) {
  switch(this->visualization) {
      case 1:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glutSolidSphere(1.0,slices, stacks);
        break;
      case 2:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glutWireSphere(1.0,slices, stacks);
        break;
      case 3:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutSolidSphere(1.0,slices, stacks);
        break;
      case 4:
        glColor3f(0.0,0.0,0.0); //black
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutSolidSphere(1.0,slices, stacks);
        glColor3f(0.0,0.0,1.0); //Blue
        break;

    }

}

void Robot :: draw_cube() {
  switch(this->visualization) {
      case 1:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glutSolidCube(1.0);
        break;
      case 2:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glutSolidCube(1.0);
        break;
      case 3:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutSolidCube(1.0);
        break;
      case 4:
        glColor3f(1.0,0.6,0.0); //yellow
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutSolidCube(1.0);
        glColor3f(0.0,0.0,1.0); //Blue

        break;
    }
}



void Robot :: draw_cylinder(){
  static GLUquadricObj * qobj = NULL;
  if(qobj == NULL) {
    qobj = gluNewQuadric();
  }
  switch(this->visualization){
    case 1:
      gluQuadricDrawStyle(qobj, GLU_POINT);
      break;
    case 2:
      gluQuadricDrawStyle(qobj, GLU_LINE);
      break;
    case 3:
      gluQuadricDrawStyle(qobj, GLU_FILL);
      break;
    case 4:
      glColor3f(0.6,0.6,0.6); //Gray
      gluQuadricDrawStyle(qobj, GLU_FILL);
      break;

  }
  gluCylinder(qobj,0.3,0.3,0.5,25,25);
  glColor3f(0.0,0.0,1.0); //Blue
}

void Robot :: draw_aux_arm_object(GLenum mode, float parent_rotation, float child_rotation)
{
      glRotatef((GLfloat) parent_rotation, 0.0,0.0,1.0);
      glTranslatef(1.0,0.0,0.0);
      glPushMatrix();
          //Parent
          glScalef(2.0,0.3,0.5);
          draw_cube();
      glPopMatrix();
      glTranslatef(1.0,0.0,0.0);
      glPushMatrix();
        glTranslatef(0.0,0.0,-0.25);
        glScalef(0.5,0.5,1.0);
        draw_cylinder();
      glPopMatrix();
      glRotatef((GLfloat) child_rotation, 0.0,0.0,1.0);
      glTranslatef(1.0,0.0,0.0);
      glPushMatrix();
        //Child
        glScalef(2.0,0.3,0.5);
        draw_cube();
      glPopMatrix();
      glTranslatef(1.0,0.0,0.0);
      glPushMatrix();
        glTranslatef(0.0,0.0,-0.25);
        glScalef(0.5,0.5,1.0);
        draw_cylinder();
      glPopMatrix();
}

void Robot :: draw_arm(GLenum mode, float *arm_rotations)
{
  glPushMatrix();
  glTranslatef(0.0,0.0,1.0);
    glPushMatrix();
      glTranslatef(0.0,0.0,-1.0);
      glScalef(0.3,0.3,0.3);
      draw_sphere(20.0,20.0);
    glPopMatrix();
    glRotatef(-90.0,0.0,1.0,0.0);
    glTranslatef(-1.0,0.0,0.0);
    glPushMatrix();
      draw_aux_arm_object(mode, arm_rotations[0], arm_rotations[1]);
      //Draw Fingers
      glPushMatrix();
        glScalef(0.2,0.2,0.45);
        glPushMatrix();
          glTranslatef(0.3,0.0,-0.3);
          draw_aux_arm_object(mode, arm_rotations[2],arm_rotations[3]);
        glPopMatrix();
        glPushMatrix();
          glTranslatef(0.3,0.0,0.3);
          draw_aux_arm_object(mode, arm_rotations[4],arm_rotations[5]);
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();


}


void Robot :: draw_trash_door(GLenum mode, float torso_rotation) {
  glPushMatrix();
    glTranslatef(0.0,-0.5,0.5);
    glPushMatrix();
      glRotatef((GLfloat) torso_rotation, 1.0,0.0,0.0);
      glTranslatef(0.0,0.35,0.0);
      glScalef(0.7,0.7,0.005);
      draw_cube();
    glPopMatrix();
  glPopMatrix();
}

void Robot :: draw_torso(GLenum mode,float torso_rotation) {
  draw_cube();
  draw_trash_door(mode, torso_rotation);
}

void Robot :: draw_tire_tracks() {
    switch(this->visualization) {
      case 1:
        glBegin(GL_POINTS);
        break;
      case 2:
      case 3:
      case 4:
        glBegin(GL_LINE_LOOP);
        break;
    }


    glVertex3f(-0.2,-0.5,0.0);
    glVertex3f(-0.2,-0.5,0.5);
    glVertex3f(-0.1,-0.5,0.5);
    glVertex3f(-0.1,-0.5,0.0);

    glVertex3f(0.0,-0.5,0.0);
    glVertex3f(0.0,-0.5,0.5);

    glVertex3f(0.1,-0.5,0.5);
    glVertex3f(0.1,-0.5,0.0);

    glVertex3f(0.2,-0.5,0.0);
    glVertex3f(0.2,-0.5,0.5);

    glVertex3f(0.3,-0.5,0.5);
    glVertex3f(0.3,-0.5,0.0);

    glVertex3f(0.4,-0.5,0.0);
    glVertex3f(0.4,-0.5,0.5);

    glVertex3f(0.5,-0.5,0.5);
    glVertex3f(0.5,-0.5,0.0);

    glVertex3f(0.6,-0.5,0.0);
    glVertex3f(0.6,-0.5,0.5);

    glVertex3f(0.7,-0.5,0.5);
    glVertex3f(0.7,-0.5,0.0);

    glVertex3f(0.8,-0.5,0.0);
    glVertex3f(0.8,-0.5,0.5);

    glVertex3f(0.9,-0.5,0.5);
    glVertex3f(0.9,-0.5,0.0);

    glVertex3f(1.0,-0.5,0.0);
    glVertex3f(1.0,-0.5,0.5);

    glVertex3f(1.1,-0.5,0.5);
    glVertex3f(1.1,-0.5,0.0);

    glVertex3f(1.2,-0.4,0.0);
    glVertex3f(1.2,-0.4,0.5);

    glVertex3f(1.25,-0.3,0.5);
    glVertex3f(1.25,-0.3,0.0);

    glVertex3f(1.25,-0.2,0.0);
    glVertex3f(1.25,-0.2,0.5);

    glVertex3f(1.20,-0.1,0.5);
    glVertex3f(1.20,-0.1,0.0);

    glVertex3f(1.15,0.0,0.0);
    glVertex3f(1.15,0.0,0.5);

    glVertex3f(1.1,0.1,0.5);
    glVertex3f(1.1,0.1,0.0);

    glVertex3f(1.0,0.2,0.0);
    glVertex3f(1.0,0.2,0.5);

    glVertex3f(0.9,0.3,0.5);
    glVertex3f(0.9,0.3,0.0);

    glVertex3f(0.8,0.4,0.0);
    glVertex3f(0.8,0.4,0.5);

    glVertex3f(0.7,0.5,0.5);
    glVertex3f(0.7,0.5,0.0);

    glVertex3f(0.6,0.6,0.0);
    glVertex3f(0.6,0.6,0.5);

    glVertex3f(0.5,0.7,0.5);
    glVertex3f(0.5,0.7,0.0);

    glVertex3f(0.4,0.8,0.0);
    glVertex3f(0.4,0.8,0.5);

    glVertex3f(0.3,0.9,0.5);
    glVertex3f(0.3,0.9,0.0);


    glVertex3f(0.2,1.0,0.0);
    glVertex3f(0.2,1.0,0.5);

    glVertex3f(0.1,1.0,0.5);
    glVertex3f(0.1,1.0,0.0);


    glVertex3f(0.0,0.9,0.0);
    glVertex3f(0.0,0.9,0.5);

    glVertex3f(-0.05,0.8,0.5);
    glVertex3f(-0.05,0.8,0.0);


    glVertex3f(-0.05,0.7,0.0);
    glVertex3f(-0.05,0.7,0.5);

    glVertex3f(-0.07,0.6,0.5);
    glVertex3f(-0.07,0.6,0.0);


    glVertex3f(-0.1,0.5,0.0);
    glVertex3f(-0.1,0.5,0.5);

    glVertex3f(-0.17,0.4,0.5);
    glVertex3f(-0.17,0.4,0.0);


    glVertex3f(-0.17,0.3,0.0);
    glVertex3f(-0.17,0.3,0.5);

    glVertex3f(-0.2,0.2,0.5);
    glVertex3f(-0.2,0.2,0.0);


    glVertex3f(-0.3,0.1,0.0);
    glVertex3f(-0.3,0.1,0.5);

    glVertex3f(-0.35,0.0,0.5);
    glVertex3f(-0.35,0.0,0.0);


    glVertex3f(-0.35,-0.1,0.0);
    glVertex3f(-0.35,-0.1,0.5);

    glVertex3f(-0.35,-0.2,0.5);
    glVertex3f(-0.35,-0.2,0.0);

    glVertex3f(-0.35,-0.3,0.0);
    glVertex3f(-0.35,-0.3,0.5);

    glVertex3f(-0.3,-0.4,0.5);
    glVertex3f(-0.3,-0.4,0.0);





  glEnd();
  switch(this->visualization) {
      case 1:
        glBegin(GL_POINTS);
        break;
      case 2:
      case 3:
      case 4:
        glBegin(GL_LINE_LOOP);
        break;
    }
    //Bottom part
    glVertex3f(-0.2,-0.55,0.0);
    glVertex3f(-0.2,-0.55,0.5);
    glVertex3f(-0.1,-0.55,0.5);
    glVertex3f(-0.1,-0.55,0.0);

    glVertex3f(0.0,-0.55,0.0);
    glVertex3f(0.0,-0.55,0.5);

    glVertex3f(0.1,-0.55,0.5);
    glVertex3f(0.1,-0.55,0.0);

    glVertex3f(0.2,-0.55,0.0);
    glVertex3f(0.2,-0.55,0.5);

    glVertex3f(0.3,-0.55,0.5);
    glVertex3f(0.3,-0.55,0.0);

    glVertex3f(0.4,-0.55,0.0);
    glVertex3f(0.4,-0.55,0.5);

    glVertex3f(0.5,-0.55,0.5);
    glVertex3f(0.5,-0.55,0.0);

    glVertex3f(0.6,-0.55,0.0);
    glVertex3f(0.6,-0.55,0.5);

    glVertex3f(0.7,-0.55,0.5);
    glVertex3f(0.7,-0.55,0.0);

    glVertex3f(0.8,-0.55,0.0);
    glVertex3f(0.8,-0.55,0.5);

    glVertex3f(0.9,-0.55,0.5);
    glVertex3f(0.9,-0.55,0.0);

    glVertex3f(1.0,-0.55,0.0);
    glVertex3f(1.0,-0.55,0.5);

    glVertex3f(1.1,-0.55,0.5);
    glVertex3f(1.1,-0.55,0.0);

    glVertex3f(1.2,-0.45,0.0);
    glVertex3f(1.2,-0.45,0.5);

    glVertex3f(1.25,-0.35,0.5);
    glVertex3f(1.25,-0.35,0.0);

    glVertex3f(1.25,-0.25,0.0);
    glVertex3f(1.25,-0.25,0.5);

    glVertex3f(1.20,-0.15,0.5);
    glVertex3f(1.20,-0.15,0.0);

    glVertex3f(1.15,0.05,0.0);
    glVertex3f(1.15,0.05,0.5);

    glVertex3f(1.1,0.15,0.5);
    glVertex3f(1.1,0.15,0.0);

    glVertex3f(1.0,0.25,0.0);
    glVertex3f(1.0,0.25,0.5);

    glVertex3f(0.9,0.35,0.5);
    glVertex3f(0.9,0.35,0.0);

    glVertex3f(0.8,0.45,0.0);
    glVertex3f(0.8,0.45,0.5);

    glVertex3f(0.7,0.55,0.5);
    glVertex3f(0.7,0.55,0.0);

    glVertex3f(0.6,0.65,0.0);
    glVertex3f(0.6,0.65,0.5);

    glVertex3f(0.5,0.75,0.5);
    glVertex3f(0.5,0.75,0.0);

    glVertex3f(0.4,0.85,0.0);
    glVertex3f(0.4,0.85,0.5);

    glVertex3f(0.3,0.95,0.5);
    glVertex3f(0.3,0.95,0.0);


    glVertex3f(0.2,1.05,0.0);
    glVertex3f(0.2,1.05,0.5);

    glVertex3f(0.1,1.05,0.5);
    glVertex3f(0.1,1.05,0.0);


    glVertex3f(0.0,0.95,0.0);
    glVertex3f(0.0,0.95,0.5);

    glVertex3f(-0.05,0.85,0.5);
    glVertex3f(-0.05,0.85,0.0);


    glVertex3f(-0.05,0.75,0.0);
    glVertex3f(-0.05,0.75,0.5);

    glVertex3f(-0.07,0.65,0.5);
    glVertex3f(-0.07,0.65,0.0);


    glVertex3f(-0.1,0.55,0.0);
    glVertex3f(-0.1,0.55,0.5);

    glVertex3f(-0.17,0.45,0.5);
    glVertex3f(-0.17,0.45,0.0);


    glVertex3f(-0.17,0.35,0.0);
    glVertex3f(-0.17,0.35,0.5);

    glVertex3f(-0.2,0.25,0.5);
    glVertex3f(-0.2,0.25,0.0);


    glVertex3f(-0.3,0.15,0.0);
    glVertex3f(-0.3,0.15,0.5);

    glVertex3f(-0.35,0.05,0.5);
    glVertex3f(-0.35,0.05,0.0);


    glVertex3f(-0.35,-0.15,0.0);
    glVertex3f(-0.35,-0.15,0.5);

    glVertex3f(-0.35,-0.25,0.5);
    glVertex3f(-0.35,-0.25,0.0);

    glVertex3f(-0.35,-0.35,0.0);
    glVertex3f(-0.35,-0.35,0.5);

    glVertex3f(-0.3,-0.45,0.5);
    glVertex3f(-0.3,-0.45,0.0);

  glEnd();
}


void Robot :: draw_feet() {

  //Walle Feet

  glPushMatrix();
    draw_cylinder();
    glPushMatrix();
      glTranslatef(1.0,-0.07,0.0);
      glScalef(0.7,0.7,1.0);
      draw_cylinder();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.55,-0.1,0.25);
      glScalef(0.5,0.4,0.5);
      draw_cube();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.98,0.22,0.15);
      glScalef(0.1,0.1,0.1);
      draw_sphere(20,20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.3,0.9,0.15);
        glRotatef(90.0,0.0,1.0,0.0);
        glPushMatrix();
          glRotatef(45.0,1.0,0.0,0.0);
          glScalef(0.3,0.3,1.8);
          draw_cylinder();
       glPopMatrix();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.16,0.98,0.0);
      glScalef(0.55,0.55,0.7);
      draw_cylinder();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.125,0.825,0.15);
      glRotatef(90.0,1.0,0.0,0.0);
      glPushMatrix();
       glRotatef(-25.0,0.0,1.0,0.0);
       glScalef(0.2,0.2,1.0);
       draw_cylinder();
      glPopMatrix();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-0.09,0.38,0.15);
      glScalef(0.1,0.1,0.1);
      draw_sphere(20,20);
    glPopMatrix();
  glPopMatrix();


  glPushMatrix();
    glTranslatef(0.0,0.2,0.0);
    draw_tire_tracks();
  glPopMatrix();
}


void Robot :: draw_eye_socket() {
  //WallE eye socket
  for(float i=0;i<=2.0;i+=0.05) {
    switch(this->visualization){
      case 1:
          glBegin(GL_POINTS);
          break;
      case 2:
      case 3:
      case 4:
          glBegin(GL_LINE_STRIP);
          break;
    }

    glVertex3f(-2.0,0.0,(GLfloat) i);
    glVertex3f(2.0,0.0,(GLfloat) i);
    glVertex3f(2.1,-0.1,(GLfloat) i);
    glVertex3f(2.2,-0.2,(GLfloat) i);
    glVertex3f(2.4,-0.4,(GLfloat) i);
    glVertex3f(2.5,-0.5,(GLfloat) i);
    glVertex3f(2.7,-0.7,(GLfloat) i);
    glVertex3f(2.75,-0.8,(GLfloat) i);
    glVertex3f(2.80,-0.9,(GLfloat) i);
    glVertex3f(2.85,-1.0,(GLfloat) i);
    glVertex3f(2.90,-1.1,(GLfloat) i);
    glVertex3f(2.95,-1.2,(GLfloat) i);
    glVertex3f(3.0,-1.3,(GLfloat) i);
    glVertex3f(3.05,-1.4,(GLfloat) i);
    glVertex3f(3.1,-1.5,(GLfloat) i);
    glVertex3f(3.1,-2.5,(GLfloat) i);
    glVertex3f(3.05,-2.6,(GLfloat) i);
    glVertex3f(3.0,-2.7,(GLfloat) i);
    glVertex3f(2.95,-2.8,(GLfloat) i);
    glVertex3f(2.90,-2.9,(GLfloat) i);
    glVertex3f(2.85,-3.0,(GLfloat) i);
    glVertex3f(2.80,-3.1,(GLfloat) i);
    glVertex3f(2.75,-3.2,(GLfloat) i);
    glVertex3f(2.7,-3.3,(GLfloat) i);
    glVertex3f(2.5,-3.4,(GLfloat) i);
    glVertex3f(2.1,-3.6,(GLfloat) i);
    glVertex3f(0.5,-3.6,(GLfloat) i);
    glVertex3f(0.0,-3.5,(GLfloat) i);
    glVertex3f(-0.5,-3.4,(GLfloat) i);
    glVertex3f(-1.0,-3.0,(GLfloat) i);
    glVertex3f(-1.5,-2.5,(GLfloat) i);
    glVertex3f(-2.0,-1.5,(GLfloat) i);
    glVertex3f(-2.0,0.0,(GLfloat) i);
  glEnd();
}
}


void Robot :: draw_front_face(GLenum mode,float eye_rotation) {
    glPushMatrix();
      glRotatef((GLfloat) eye_rotation, 0.0,0.0,1.0);
      glPushMatrix();
        glTranslatef(2.1,1.0,0.0);
        draw_eye_socket();
      glPopMatrix();
      glPushMatrix();
        glTranslatef(1.5,-0.5,0.0);
        glScalef(4.0,4.0,4.0);
        draw_cylinder();
        glPushMatrix();
          glScalef(0.8,0.8,1.0);
          draw_cylinder();
        glPopMatrix();
      glPopMatrix();
      glPushMatrix();
        glTranslatef(2.3,-0.5,-2.0);
        glScalef(3.5,3.0,4.0);
        draw_cube();
      glPopMatrix();
    glPopMatrix();

    glPushMatrix();
      glRotatef(-(GLfloat) eye_rotation, 0.0,0.0,1.0);
      glPushMatrix();
        glRotatef(180.0,0.0,1.0,0.0);
        glTranslatef(2.1,1.0,-2.0);
        draw_eye_socket();
      glPopMatrix();
      glPushMatrix();
        glTranslatef(-1.5,-0.5,0.0);
        glScalef(4.0,4.0,4.0);
        draw_cylinder();
        glPushMatrix();
          glScalef(0.8,0.8,1.0);
          draw_cylinder();
        glPopMatrix();
      glPopMatrix();
      glPushMatrix();
        glTranslatef(-2.3,-0.5,-2.0);
        glScalef(3.5,3.0,4.0);
        draw_cube();
      glPopMatrix();
    glPopMatrix();
}


void Robot :: draw_head(GLenum mode, float eye_rotation) {
    glPushMatrix();
      glTranslatef(0.0,0.6,0.0);
      glScalef(0.3,0.3,0.3);
        glPushMatrix();
          glScalef(1.0,0.8,0.8);
          glRotatef(-15.0,1.0,0.0,0.0);
            glPushMatrix();
              glRotatef(90.0,0.0,1.0,0.0);
              glPushMatrix();
                glScalef(2.0,0.2,0.52);
                draw_cube();
              glPopMatrix();
              glPushMatrix();
                glTranslatef(-1.0,0.0,-0.26);
                glScalef(0.3,0.3,1.05);
                draw_cylinder();
              glPopMatrix();
              glPushMatrix();
                glTranslatef(1.0,0.0,-0.26);
                glScalef(0.3,0.3,1.05);
                draw_cylinder();
              glPopMatrix();
              glPushMatrix();
                glTranslatef(-0.5,0.9,0.0);
                glRotatef(60.0,0.0,0.0,1.0);
                glScalef(2.0,0.15,0.52);
                draw_cube();
              glPopMatrix();
              glPushMatrix();
                glTranslatef(0.0,1.8,-0.26);
                glScalef(0.3,0.3,1.05);
                draw_cylinder();
              glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
          glTranslatef(0.0,2.0,0.0);
          glScalef(0.3,0.3,0.3);
          draw_front_face(mode, eye_rotation);
        glPopMatrix();
    glPopMatrix();
}

void Robot :: draw_body_and_feet(GLenum mode,float * body_rotations,float * arm_rotations) {


  glTranslatef(0.0,0.0,(GLfloat) body_rotations[0]);

  glPushMatrix();
    // glPushNames(0);
    draw_torso(mode, body_rotations[2]);
    glPushMatrix();
	    glTranslatef(-0.6,0.2,0.0);
	    glRotatef((GLfloat) body_rotations[3], 0.0,0.0,1.0);
	    //glPushMatrix();
        glScalef(0.3,0.3,0.3);
        draw_arm(mode, arm_rotations);
      //glPopMatrix();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.6,0.2,0.0);
      glRotatef(-(GLfloat) body_rotations[3], 0.0,0.0,1.0);
      //glPushMatrix();
        glScalef(0.3,0.3,0.3);
        draw_arm(mode, arm_rotations);
      //glPopMatrix();
    glPopMatrix();
    //Left Feet
    glPushMatrix();
      glTranslatef(0.8,-0.7,-0.3);
      glRotatef(-90.0,0.0,1.0,0.0);
      glScalef(0.6,0.6,0.6);
      draw_feet();
    glPopMatrix();
    //Right Feet
    glPushMatrix();
      glTranslatef(-0.5,-0.7,-0.3);
      glRotatef(-90.0,0.0,1.0,0.0);
      glScalef(0.6,0.6,0.6);
      draw_feet();
    glPopMatrix();
  glPopMatrix();

}


void Robot :: draw(GLenum mode,visual_t visualization , float *body_rotations, float *arm_rotations, float eye_rotation) {

    glPointSize(2.0);
    this->visualization = visualization;
    switch(visualization) {
      case POINT:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        break;
      case FILL:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
      case LINE:
      case CHECKERED:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
      default:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        break;

    }


    glRotatef((GLfloat) body_rotations[1], 0.0,1.0,0.0);
    glPushMatrix();
    glLoadName(1);
    draw_body_and_feet(mode, body_rotations, arm_rotations);
    glLoadName(2);
    draw_head(mode, eye_rotation);
    glPopMatrix();
}

