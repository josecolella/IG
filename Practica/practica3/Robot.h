#ifndef _ROBOT_H_
#define _ROBOT_H_

class Robot
{

  private:
    void draw_cylinder();
    void draw_sphere(GLint slices, Glint stacks);
    void draw_cube();
  public:
    Robot();
    ~Robot();
    void draw_trash_door();
    void draw_torso();
    void draw_arm();
    void draw_head();
    void draw_legs();
    void draw();
};


#endif