#ifndef _ROBOT_H_
#define _ROBOT_H_

/**
 * La clase Robot representa la representacion
 * grafica de un Robot que en este caso es Wall-E
 */
class Robot
{

  private:

    void draw_cylinder();
    void draw_sphere(GLint slices, Glint stacks);
    void draw_cube();
  public:
    Robot();
    ~Robot();
    void draw_hands(float z_rotation);
    void draw_arm(float shoulder_rotation, float elbow_rotation);
    void draw_trash_door(float torso_rotation);
    void draw_torso();
    void draw_tire_tracks();
    void draw_feet();
    void draw_eye_socket();
    void draw_front_face();
    void draw_head();
    void draw_body_and_feet();
    void draw();
};


#endif