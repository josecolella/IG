#include <GL/gl.h>
#include <vector>
#include "vertex.h"

#ifndef _ROBOT_H_
#define _ROBOT_H_

/**
 * La clase Robot representa la representacion
 * grafica de un Robot que en este caso es Wall-E
 */
class Robot
{

  private:
    int model;
    void draw_cylinder();
    void draw_sphere(GLint slices, GLint stacks);
    void draw_cube();
  public:
    Robot();
    void setModel(int model);
    int getModel() const;
    void draw_hands(float z_rotation);
    void draw_arm(float shoulder_rotation, float elbow_rotation);
    void draw_trash_door(float torso_rotation);
    void draw_torso(float torso_rotation);
    void draw_tire_tracks();
    void draw_feet();
    void draw_eye_socket();
    void draw_front_face(float eye_rotation, float pupil_scale);
    void draw_head(float eye_rotation, float pupil_scale);
    void draw_body_and_feet(float body_y_rotation, float body_translate, float torso_rotation, float shoulder_rotation, float elbow_rotation, float arm_rotation);
    void draw(float body_y_rotation, float body_translate, float torso_rotation, float shoulder_rotation, float elbow_rotation, float eye_rotation, float pupil_scale, float arm_rotation);
};


#endif