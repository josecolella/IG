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

void Robot :: draw_aux_arm_object(GLuint * id_index, float parent_rotation, float child_rotation)
{
  GLuint id = *id_index; //4 
  //Poner nombre
  glPushName(id);
  glRotatef((GLfloat) parent_rotation, 0.0,0.0,1.0);
  glTranslatef(1.0,0.0,0.0);
  glPushMatrix();
          //Parent
    glScalef(2.0,0.3,0.5);
    if(selectedIndex == id || selectedIndex == *id_index + (id % 6)){
      glColor3f(1.0,0.6,0.0); //yellow
    }else{
      glColor3f(0.0,0.0,1.0);  
    }
    draw_cube();
  glPopMatrix();
  glPopName();
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
  id = id + 1;
  glPushName(id);
  glScalef(2.0,0.3,0.5);
       if(selectedIndex == id || selectedIndex == *id_index + (id % 6)){
         glColor3f(1.0,0.6,0.0); //yellow
       }else{
         glColor3f(0.0,0.0,1.0);  
       }
      
      draw_cube();
      
  glPopMatrix();
  glTranslatef(1.0,0.0,0.0);
  glPushMatrix();
    glTranslatef(0.0,0.0,-0.25);
    glScalef(0.5,0.5,1.0);
    draw_cylinder();
  glPopMatrix();
  glPopName();

}

void Robot :: draw_arm(GLuint * id_index, float *arm_rotations)
{

  glPushMatrix();
  glTranslatef(0.0,0.0,1.0);
  glPushMatrix();
  glTranslatef(0.0,0.0,-1.0);
  glScalef(0.3,0.3,0.3);
  glColor3f(0.0,0.0,1.0);
  draw_sphere(20.0,20.0);
  glPopMatrix();
  glRotatef(-90.0,0.0,1.0,0.0);
  glTranslatef(-1.0,0.0,0.0);
  glPushMatrix();
  //bottom part of arm
  draw_aux_arm_object(id_index,arm_rotations[0], arm_rotations[1]);
  *id_index = *id_index + 2;
      //Draw Fingers
  glPushMatrix();
  glScalef(0.2,0.2,0.45);
  glPushMatrix();
  glTranslatef(0.3,0.0,-0.3);
  draw_aux_arm_object(id_index, arm_rotations[2],arm_rotations[3]);
  *id_index = *id_index + 2;
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.3,0.0,0.3);
  draw_aux_arm_object(id_index, arm_rotations[4],arm_rotations[5]);
  *id_index = *id_index + 2;
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();


}


void Robot :: draw_trash_door( float torso_rotation) {
  if(selectedIndex == 3){
      glColor3f(1.0,0.6,0.0); //yellow
  }else{
    glColor3f(0.0,0.0,1.0);  
  }
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

void Robot :: draw_torso(float torso_rotation) {
  selected = BODY_R;
  glPushName(selected);
  draw_cube();
  glPopName();
  selected = TRASH_DOOR_R;
  glPushName(selected);
  draw_trash_door(torso_rotation);
  glPopName();
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


void Robot :: draw_front_face(float eye_rotation) {
  if(selectedIndex == 2){
      glColor3f(1.0,0.6,0.0); //yellow
  }else{
    glColor3f(0.0,0.0,1.0);  
  }
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
  if(selectedIndex == 2){
      glColor3f(1.0,0.6,0.0); //yellow
  }else{
    glColor3f(0.0,0.0,1.0);  
  }
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


void Robot :: draw_head( float eye_rotation) {
  if(selectedIndex == 2){
      glColor3f(1.0,0.6,0.0); //yellow
  }else{
    glColor3f(0.0,0.0,1.0);  
  }
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
          if(selectedIndex == 2){
              glColor3f(1.0,0.6,0.0); //yellow
          }else{
            glColor3f(0.0,0.0,1.0);  
          }
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
          if(selectedIndex == 2){
              glColor3f(1.0,0.6,0.0); //yellow
          }else{
            glColor3f(0.0,0.0,1.0);  
          }
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
      selected = HEAD_R;
      glLoadName(selected);
      if(selectedIndex == 2){
          glColor3f(1.0,0.6,0.0); //yellow
      }else{
        glColor3f(0.0,0.0,1.0);  
      }
      draw_front_face(eye_rotation);
    glPopMatrix();
  glPopMatrix();
}

void Robot :: draw_body_and_feet(float * body_rotations,float * arm_rotations) {

  id_index = (GLuint) 4;
  glTranslatef(0.0,0.0,(GLfloat) body_rotations[0]);
  glPushMatrix();
  // ID 1 3
  draw_torso(body_rotations[2]);
  glPushMatrix();
  glTranslatef(-0.6,0.2,0.0);
  glRotatef((GLfloat) body_rotations[3], 0.0,0.0,1.0);
  glScalef(0.3,0.3,0.3);
        //Right arm
  draw_arm(&id_index, arm_rotations);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.6,0.2,0.0);
  glRotatef(-(GLfloat) body_rotations[3], 0.0,0.0,1.0);
  glScalef(0.3,0.3,0.3);
        //Left arm  
  draw_arm(&id_index, arm_rotations);
  glPopMatrix();
    //Left Feet
  glPushMatrix();
  glTranslatef(0.8,-0.7,-0.3);
  glRotatef(-90.0,0.0,1.0,0.0);
  glScalef(0.6,0.6,0.6);
      //Left foot
  draw_feet();
  glPopMatrix();
    //Right Feet
  glPushMatrix();
  glTranslatef(-0.5,-0.7,-0.3);
  glRotatef(-90.0,0.0,1.0,0.0);
  glScalef(0.6,0.6,0.6);
      //Right foot
  if(selectedIndex == 1 || this->selectedIndex == 16){
      glColor3f(1.0,0.6,0.0); //yellow
  }else{
    glColor3f(0.0,0.0,1.0);  
  }
  draw_feet();
  glPopMatrix();
  glPopMatrix();

}


void Robot :: draw(visual_t visualization , float *body_rotations, float *arm_rotations, float eye_rotation) {

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

  glInitNames();
  glPushName(0);

  glPushMatrix();
  glRotatef((GLfloat) body_rotations[1], 0.0,1.0,0.0);

      //Nombre para el cuerpo y los pies
  selected = BODY_T;
  glPushName(selected);
  if(selectedIndex == 1 || selectedIndex == 16){
      glColor3f(1.0,0.6,0.0); //yellow
  }else{
    glColor3f(0.0,0.0,1.0); 
     
  }
  draw_body_and_feet(body_rotations, arm_rotations);
  glPopName();

      //Nombre para la cabeza
  selected = HEAD_R;
  glPushName(selected);
  if(selectedIndex == 1 || selectedIndex == 16){
      glColor3f(1.0,0.6,0.0); //yellow
  }else{
    glColor3f(0.0,0.0,1.0); 
     
  }
  draw_head(eye_rotation);
  glPopName();

  glPopMatrix();
  glPopName();
}

void Robot :: setSelectedIndex(int selectedIndex)
{
  this->selectedIndex = selectedIndex;
}

GLuint Robot :: getSelectedIndex()
{
  return this->id_index;
}


void Robot :: printStructure()
{ 
  cout << "-----------------------------------------------------" << endl;
  switch(this->selectedIndex)
  {
    
    case 0:
      cout << "No has seleccionado nada" << endl;
      break;
    case 1: 
      cout << "Has seleccionado la estructura entera. Puedes transladar" << endl;
      break;
    case 2:
      cout << "Has seleccionado la cabeza. Puedes rotar" << endl;
      break;
    case 3:
      cout << "Has seleccionado la puerta de basura. Puedes rotar" << endl;
      break;
    case 4:
    case 10:
      cout << "Has seleccionado uno de los hombros. Puedes rotarlos" << endl;
      break;
    case 5:
    case 11:
      cout << "Has seleccionado uno de los codos. Puedes rotarlos" << endl;
      break;
    case 6:
    case 12:
      cout << "Has seleccionado uno de los indices inferiores izquierdo de los dedos. Puedes rotarlos" << endl;
      break;
    case 7:
    case 13:
      cout << "Has seleccionado unos de los indices superiores izquierdo de los dedos. Puedes rotarlos" << endl;
      break;
    case 8:
    case 14:
      cout << "Has seleccionado unos de los indices inferiores derecho de los dedos. Puedes rotarlos" << endl;
      break;
    case 9:
    case 15:
      cout << "Has seleccionado unos de los indices superiores derecho de los dedos. Puedes rotarlos" << endl;  
      break;
    case 16:
      cout << "Has seleccionado la estructura entera. Puedes rotarla" << endl;
      break;
    default: break;
  }
  cout << "-----------------------------------------------------" << endl;
  
}