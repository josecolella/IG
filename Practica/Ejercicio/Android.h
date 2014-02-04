#include <GL/gl.h>
#include <vector>
#include "vertex.h"
#include "visualtype.h" //Enum que denota que denota la visualizacion
#include "MallaTVT.h"

#ifndef _ANDROID_H_
#define _ANDROID_H_

/**
 * La clase Android representa la representacion
 * grafica de un Android que en este caso es Wall-E
 */
class Android
{

  private:
    visual_t visualization;
    MallaTVT * android_body;
    MallaTVT * android_head;
    //Metodos privados que dibujan objetos simples de glut
    void draw_cylinder();
    void draw_sphere(GLint slices, GLint stacks);
    void draw_cube();
  public:
    Android();
    ~Android();
    //Metodo para dibujar el Android
    void draw(visual_t visualization);
   private:
    //Metodos privados auxiliares para dibujar en Android entero
    void draw_aux_object();
    void draw_body();
    void draw_head();
    void draw_arm();
    void draw_leg();
    void draw_eyes();
    void draw_antenna();
    void draw_robot();


};


#endif
