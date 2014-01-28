#include <GL/gl.h>
#include <vector>
#include "vertex.h"
#include "visualtype.h" //Enum que denota que denota la visualizacion

#ifndef _ROBOT_H_
#define _ROBOT_H_

/**
 * La clase Robot representa la representacion
 * grafica de un Robot que en este caso es Wall-E
 */
class Robot
{

  private:
    visual_t visualization;
    //Metodos privados que dibujan objetos simples de glut
    void draw_cylinder();
    void draw_sphere(GLint slices, GLint stacks);
    void draw_cube();
  public:
    Robot() {visualization = POINT;};
    //Metodo para dibujar el robot
    void draw(GLenum mode,visual_t visualization,float *body_rotations, float *arm_rotations, float eye_rotation);
   private:
    //Metodos privados auxiliares para dibujar en robot entero
    void draw_aux_arm_object(GLenum mode,float parent_rotation, float child_rotation);
    void draw_arm(GLenum mode,float * arm_rotations);
    void draw_trash_door(GLenum mode,float torso_rotation);
    void draw_torso(GLenum mode,float torso_rotation);
    void draw_tire_tracks();
    void draw_feet();
    void draw_eye_socket();
    void draw_front_face(GLenum mode, float eye_rotation);
    void draw_head(GLenum mode, float eye_rotation);
    void draw_body_and_feet(GLenum mode, float * body_rotations,float * arm_rotations);

};


#endif
