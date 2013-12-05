//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <iostream> //Para cerr
#include "user_code.h"
#include "vertex.h"
#include "file_ply_stl.h"
#include "MallaTVT.h"


// tamaño de los ejes
const int AXIS_SIZE=5000;

//Variable global que dibuja y termina como se dibuja la figura/

MallaTVT mallaTVT;

static int shoulder = 0, elbow = 0, leftarm = 0,rightarm=0,torso = 0;
static float retration = 2.0;
// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glShadeModel(GL_FLAT);
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluPerspective(65.0,)
// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
  glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
  glBegin(GL_LINES);
// eje X, color rojo
  glColor3f(1,0,0);
  glVertex3f(-AXIS_SIZE,0,0);
  glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
  glColor3f(0,1,0);
  glVertex3f(0,-AXIS_SIZE,0);
  glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
  glColor3f(0,0,1);
  glVertex3f(0,0,-AXIS_SIZE);
  glVertex3f(0,0,AXIS_SIZE);
  glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************
void draw_sphere(GLfloat first, GLfloat second) {
  glutSolidSphere(1.0,first,second);
}


void draw_Scube() {
  glutSolidCube(1.0);
}


void draw_cylinder(){
  static GLUquadricObj * qobj = NULL;
  if(qobj == NULL) {
    qobj = gluNewQuadric();
  }
  gluQuadricDrawStyle(qobj, GLU_LINE);
  gluCylinder(qobj,0.3,0.3,0.5,25,25);

}

void draw_hands(GLfloat z_rotation) {

    glPushMatrix();
      //dibujo las manos
      glTranslatef(0.7,0.0,z_rotation);
      glScalef(1.0,0.1,0.25);
      draw_Scube();
    glPopMatrix();
}

void draw_arm()
{
  glPushMatrix();
  glTranslatef(0.0,0.0,1.0);
  glPushMatrix();
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


void draw_trash_door(){
  glPushMatrix();
    glTranslatef(0.0,-0.5,0.5);
    glPushMatrix();
      glRotatef((GLfloat) torso, 1.0,0.0,0.0);
      glTranslatef(0.0,0.35,0.0);
      glScalef(0.7,0.7,0.005);
      glutSolidCube(1.0);
    glPopMatrix();
  glPopMatrix();
}

void draw_torso()
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glutSolidCube(1.0);
  draw_trash_door();
}



void draw_objects()
{
  // if(mallaTVT.getModel() == 1)
  //   draw_cube();
  // else
    //La clase gestiona el dibujo
  //mallaTVT.draw();
  //draw_cube();
  //
  //draw_arm();
  //

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // glTranslatef(0.0,1.0,0.0);
  // glPushMatrix();
  //   glScalef(1.0,0.7,1.5);
  //   draw_cylinder();
  //   glPushMatrix();
  //     glTranslatef(0.15,0.0,0.0);
  //     glScalef(0.3,0.3,0.5);
  //     draw_cylinder();
  //   glPopMatrix();
  //   glPushMatrix();
  //     glTranslatef(-0.15,0.0,0.0);
  //     glScalef(0.3,0.3,0.5);
  //     draw_cylinder();
  //   glPopMatrix();
  // glPopMatrix();

  glPushMatrix();
    glScalef(0.5,0.5,0.5);
    glPushMatrix();
      glTranslatef(-0.6,0.0,0.0);
      glScalef(1.0,0.1,1.5);
      draw_Scube();
      glPushMatrix();
        glRotatef(90.0,1.0,0.0,0.0);
        draw_Scube();
      glPopMatrix();
    glPopMatrix();
    glPushMatrix();

    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.6,0.0,0.0);
      glScalef(1.0,0.1,1.5);
      draw_Scube();
    glPopMatrix();
  glPopMatrix();


  //draw_cylinder();
  /*
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


  draw_torso();

  glPushMatrix();
    glTranslatef(-0.6,0.2,0.0);
    glRotatef((GLfloat) leftarm, 0.0,0.0,1.0);
    glPushMatrix();
      glScalef(0.3,0.3,0.3);
      draw_arm();
    glPopMatrix();
  glPopMatrix();
   glPushMatrix();
    glTranslatef(0.6,0.2,0.0);
    glRotatef((GLfloat) rightarm, 0.0,0.0,1.0);
    glPushMatrix();
      glScalef(0.3,0.3,0.3);
      draw_arm();
    glPopMatrix();
  glPopMatrix();
  */
  //--------------------------------



  // glScalef(0.5,1.0,0.2);
  // glutSolidCube(1.0);
  // glPushMatrix();
  //   glTranslatef(1.0,0.0,0.0);
  //   glutSolidCube(1.0);
  // glPopMatrix();
  // glRotatef((GLfloat) shoulder,1.0,0.0,0.0);
  // glPushMatrix();
  //   glTranslatef(0.0,1.0,0.0);
  //   glScalef(1.0,1.0,0.4);
  //   glutSolidCube(1.0);e
  // glPopMatrix();
  // glRotatef((GLfloat) elbow,1.0,0.0,0.0);
  // glPushMatrix();
  //   glTranslatef(1.0,1.0,0.0);
  //   glScalef(1.0,1.0,0.4);
  //   glutSolidCube(1.0);
  // glPopMatrix();
    //glTranslatef(1.0,0.0,0.0);
    //glutSolidCube(1.0);

  // glBegin(GL_LINE_LOOP);
  //   glVertex3f(0.0,0.0,0.0);
  //   glVertex3f(0.0,2.0,0.0);
  //   glVertex3f(2.0,2.0,0.0);
  //   glVertex3f(2.0,0.0,0.0);
  // glEnd();

  // glBegin(GL_LINE_LOOP);
  //   glVertex3f(0.0,0.0,0.2);
  //   glVertex3f(0.0,2.0,0.2);
  //   glVertex3f(2.0,2.0,0.2);
  //   glVertex3f(2.0,0.0,0.2);
  // glEnd();
}



//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

  clear_window();
  change_observer();
  draw_axis();
  draw_objects();
  glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
  //change_projection();
  glViewport(0,0,Ancho1,Alto1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0,Ancho1/Alto1, 1.0,20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0,0.0,-5.0);
  glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
  //En base a la tecla tocada, se determina que se dibuja y como
  switch ((Tecla1)) {

    case 'Q': exit(0); break;
    case 27: exit(0); break;
    case 's':
        if(shoulder < 90)
          shoulder = (shoulder + 1);
        glutPostRedisplay();
        break;
    case 'S':
      if(shoulder > -90)
        shoulder = (shoulder - 1);
      glutPostRedisplay();
      break;
    case 'e':
        if(elbow < 90)
          elbow = (elbow + 1);
        glutPostRedisplay();
        break;
    case 'E':
        if(elbow > 0)
          elbow = (elbow - 1);
        glutPostRedisplay();
        break;
    case 'a':
        if(retration < 90)
          retration = (retration + 1);
        glutPostRedisplay();
        break;
    case 'A':
        if(retration > 0)
          retration = (retration - 1);
        glutPostRedisplay();
        break;
    case 'r':
        if(rightarm < 90)
          rightarm = (rightarm + 1);
        glutPostRedisplay();
        break;
    case 'R':
        if(rightarm > 0)
          rightarm = (rightarm - 1);
        glutPostRedisplay();
        break;
    case 't':
        if(torso < 90)
          torso = (torso + 1);
        glutPostRedisplay();
        break;
    case 'T':
        if(torso > 0)
          torso = (torso - 1);
        glutPostRedisplay();
        break;
    default: glutPostRedisplay(); break;

  }
  glutPostRedisplay();
}
//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

  switch (Tecla1){
   case GLUT_KEY_LEFT:Observer_angle_y--;break;
   case GLUT_KEY_RIGHT:Observer_angle_y++;break;
   case GLUT_KEY_UP:Observer_angle_x--;break;
   case GLUT_KEY_DOWN:Observer_angle_x++;break;
   case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
   case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
 }
 glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(const char * file)
{
// se inicalizan la ventana y los planos de corte
  Window_width=.5;
  Window_height=.5;
  Front_plane=1;
  Back_plane=1000;

// se inicia la posicion del observador, en el eje z
  Observer_distance=3*Front_plane;
  Observer_angle_x=0;
  Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
  glClearColor(1,1,1,1);

// se habilita el z-bufer
  glEnable(GL_DEPTH_TEST);
  change_projection();
  glViewport(0,0,UI_window_width,UI_window_height);

  //Inicializamos la mallaTVT con el fichero
  mallaTVT.initialize(file);

}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
    // se llama a la inicialización de glut
  glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
  glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
  glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
  glutCreateWindow(argv[0]);

    // asignación de la funcion llamada "dibujar" al evento de dibujo
  glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
  glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
  glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
  glutSpecialFunc(special_keys);

  // funcion de inicialización
  // Vemos si el usuario ha insertado el nombre del fichero al cual se leera
  // Si el usuario no mete ningun nombre se pone el ply del coche "big_dodge"
  if(argc != 2)
    std::cerr << "Error: Numero invalido de argumentos.\nError:./practica1 [nombreDelFicheroPlySinExtension]" << std::endl;
  else {
    //Si mete el nombre se abre ese
    initialize(argv[1]);
    // inicio del bucle de eventos
    glutMainLoop();
  }
  return 0;
}
