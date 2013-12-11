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
#include "Robot.h"


GLint animate = 0; //Para hacer animation o no
//enum que denota los diferentes estados
enum state_t {NONE=0,PLY, ROTATION, HIERARCHY};

// tamaño de los ejes
const int AXIS_SIZE=5000;


MallaTVT mallaTVT1;
MallaTVT mallaTVT2;
Robot robot;

//Variable que destaca el estado de dibujo. PLY, ROTACIONAL, HIERARCHY
state_t state = NONE;
//Variables que se cambian en base a las teclas usadas
static float shoulder = 0, elbow = 0, left_index_rotation = 0, right_finger_rotation = 0, left_top = 0, right_top = 0;
static float torso = 0, arm_rotation = 0;
static float eye_rotation = 0.0, body_y_rotation = 0.0, body_translate = 0.0;


float arm_rotations[6] = {shoulder, elbow, left_index_rotation, left_top, right_finger_rotation, right_top};
float eye_rotations = eye_rotation;
float body_rotations[4] = {body_translate, body_y_rotation, torso, arm_rotation};

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

void animation_1() {
  if(elbow < 90)
    elbow += 1;
  if(elbow == 90) {
    if(eye_rotation > -8.0)
      eye_rotation = (eye_rotation - 0.1);
    if(arm_rotation <= 45)
      arm_rotation = arm_rotation + 1;

  }

  glutPostRedisplay();
}

void animation_2() {

  if(elbow == 90) {
    if(eye_rotation < 0)
      eye_rotation = (eye_rotation + 0.1);
    if(arm_rotation >= -45)
      arm_rotation = arm_rotation - 1;

  }

  glutPostRedisplay();
}



void animation_6() {

  glutPostRedisplay();

}

void animation_3() {
  if(body_y_rotation < 90)
    body_y_rotation = (body_y_rotation + 1.0);
  if(body_y_rotation == 90) {
    if(body_translate < 1.0) {
      body_translate = (body_translate + 0.05);
    }
    if(torso < 120)
      torso += 1;

  }
  glutPostRedisplay();
}



void animation_4() {

  if(torso > 0)
   torso -= 1;
 if(body_y_rotation > 0)
  body_y_rotation = (body_y_rotation - 1.0);

if(body_translate > 0.0)
  body_translate = (body_translate - 0.05);

glutPostRedisplay();
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

void draw_objects()
{

  switch(state) {
    case PLY:
    mallaTVT1.draw();
    break;
    case ROTATION:
    mallaTVT2.draw();
    break;
    case HIERARCHY:
    robot.draw(body_rotations, arm_rotations, eye_rotations);
    break;
  }

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

/**
 * Menu de ayuda donde se denotan las teclas posibles
 */
 void printHelp() {
  cout << "Posibles comandos: " << endl;
  cout << "?: Repetir este menu de ayuda" << endl;
  cout << "p: Visualizar en modo punto" << endl;
  cout << "l: Visualizar en modo linea" << endl;
  cout << "s: Visualizar en modo solido" << endl;
  cout << "a: Visualizar en modo ajedrez" << endl;
  cout << "1: Activar objeto PLY" << endl;
  cout << "2: Activar objeto por revolucion" << endl;
  cout << "3: Activar objeto jerarquico" << endl;
  cout << "Z: Rotacion Hombro positiva" << endl;
  cout << "z: Rotacion Hombro negativa" << endl;
  cout << "X: Rotacion Codo positiva" << endl;
  cout << "x: Rotacion Codo negativa" << endl;
  cout << "C: Rotacion Dedo izquierdo inferior positiva" << endl;
  cout << "c: Rotacion Dedo izquierdo inferior negativa" << endl;
  cout << "V: Rotacion Dedo izquierdo superior positiva" << endl;
  cout << "v: Rotacion Dedo izquierdo superior negativa" << endl;
  cout << "D: Rotacion Dedo derecho inferior positiva" << endl;
  cout << "d: Rotacion Dedo derecho inferior negativa" << endl;
  cout << "F: Rotacion Dedo derecho superior positiva" << endl;
  cout << "f: Rotacion Dedo derecho superior negativa" << endl;
  cout << "G: Rotacion Ojos positiva" << endl;
  cout << "g: Rotacion Ojo negativa" << endl;
  cout << "H: Rotacion Cuerpo positiva" << endl;
  cout << "h: Rotacion Cuerpo negativa" << endl;
  cout << "T: Translacion Cuerpo positiva" << endl;
  cout << "t: Translacion Cuerpo negativa" << endl;
  cout << "J: Rotacion Torso positiva" << endl;
  cout << "j: Rotacion Torso negativa" << endl;

  cout << "n: Animacion 1 positiva (ESPERAR QUE TERMINE)" << endl;
  cout << "N: Animacion 1 negativa (ESPERAR QUE TERMINE)" << endl;
  cout << "m: Animacion 2 positiva (ESPERAR QUE TERMINE)" << endl;
  cout << "M: Animacion 2 negativa (ESPERAR QUE TERMINE)" << endl;



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
    case '?':
    printHelp();
    break;
    case '1':
    state = PLY;
    break;
    case '2':
    state = ROTATION;
    break;
    case '3':
    state = HIERARCHY;
    break;
    case 'p':
    mallaTVT1.setModel(1);
    mallaTVT2.setModel(1);
    robot.setModel(1);
    glutPostRedisplay();
    break;
    case 'l':
    mallaTVT1.setModel(2);
    mallaTVT2.setModel(2);
    robot.setModel(2);
    break;
    case 's':
    mallaTVT1.setModel(3);
    mallaTVT2.setModel(3);
    robot.setModel(3);
    break;
    case 'a':
    mallaTVT1.setModel(4);
    mallaTVT2.setModel(4);
    robot.setModel(4);
    break;
    case 'Z':
    if(state == HIERARCHY) {
      animate = 0;
      if(arm_rotations[0] < 75)
        arm_rotations[0] = (arm_rotations[0] + 1);
      glutPostRedisplay();

    }
    break;
    case 'z':
    if(state == HIERARCHY) {
      animate = 0;
      if(arm_rotations[0] > -45)
        arm_rotations[0] = (arm_rotations[0] - 1);
      glutPostRedisplay();
    }
    break;
    case 'X':
    if(state == HIERARCHY) {
      animate = 0;
      if(arm_rotations[1] < 90)
        arm_rotations[1] = (arm_rotations[1] + 1);
      glutPostRedisplay();
    }
    break;

    case 'x':
    if(state == HIERARCHY) {
      animate = 0;
      if(arm_rotations[1] > 0)
        arm_rotations[1] = (arm_rotations[1] - 1);
      glutPostRedisplay();
    }
    break;
    case 'c':
    if(state == HIERARCHY) {
      animate = 0;
      if(arm_rotations[2] < 45)
        arm_rotations[2] = arm_rotations[2] + 1;
      glutPostRedisplay();
    }
    break;
    case 'C':
    if(state == HIERARCHY) {
      animate = 0;
      if(arm_rotations[2] > 0)
        arm_rotations[2] = arm_rotations[2] - 1;
      glutPostRedisplay();
    }
    break;
    case 'v':
    if(state == HIERARCHY) {
      animate = 0;
      if(arm_rotations[3] < 45)
        arm_rotations[3] = arm_rotations[3] + 1;
      glutPostRedisplay();
    }
    break;
    case 'V':
    if(state == HIERARCHY) {
      animate = 0;
      if(arm_rotations[3] > 0)
        arm_rotations[3] = arm_rotations[3] - 1;
      glutPostRedisplay();
    }
    break;
    case 'D':
    if(state == HIERARCHY) {
      animate = 0;
      if(arm_rotations[4] < 45)
        arm_rotations[4] = arm_rotations[4] + 1;
      glutPostRedisplay();
    }
    break;
    case 'd':
    if(state == HIERARCHY) {
      animate = 0;
      if(arm_rotations[4] > 0)
        arm_rotations[4] = arm_rotations[4] - 1;
      glutPostRedisplay();
    }
    break;
    case 'F':
    if(state == HIERARCHY) {
      animate = 0;
      if(arm_rotations[5] < 45)
        arm_rotations[5] = arm_rotations[5] + 1;
      glutPostRedisplay();
    }
    break;
    case 'f':
    if(state == HIERARCHY) {
      animate = 0;
      if(arm_rotations[5] > 0)
        arm_rotations[5] = arm_rotations[5] - 1;
      glutPostRedisplay();
    }
    break;
    case 'G':
    if(state == HIERARCHY) {
      animate = 0;
      if(eye_rotations < 0)
        eye_rotations = (eye_rotations + 0.5);
      glutPostRedisplay();
    }
    break;
    case 'g':
    if(state == HIERARCHY) {
      animate = 0;
      if(eye_rotations > -8.0)
        eye_rotations = (eye_rotations - 0.5);
      glutPostRedisplay();
    }
    break;
    case 'H':
        if(state == HIERARCHY) {
        animate = 0;
        if(body_rotations[1] <= 180)
          body_rotations[1] = (body_rotations[1] + 1);
        glutPostRedisplay();
      }
        break;
    case 'h':
        if(state == HIERARCHY) {
        animate = 0;
        if(body_rotations[1] >= -180)
          body_rotations[1] = (body_rotations[1] - 1);
        glutPostRedisplay();
        }
        break;
     case 'T':
    if(state == HIERARCHY) {
        animate = 0;
        if(body_rotations[0] < 2.0)
          body_rotations[0] = (body_rotations[0] + 0.05);
        glutPostRedisplay();
      }
        break;
    case 't':
    if(state == HIERARCHY) {
        animate = 0;
        if(body_rotations[0] > -2.0)
          body_rotations[0] = (body_rotations[0] - 0.05);
        glutPostRedisplay();
      }
        break;
    case 'J':
    if(state == HIERARCHY) {
        animate = 0;
        if(body_rotations[2] < 120)
          body_rotations[2] = (body_rotations[2] + 1);
        glutPostRedisplay();
        break;
      }
    case 'j':
    if(state == HIERARCHY) {
        animate = 0;
        if(body_rotations[2] > 0)
          body_rotations[2] = (body_rotations[2] - 1);
        glutPostRedisplay();
      }
       break;
    // case 'n':
    // if(state == HIERARCHY) {
    //     animate = 1;
    //     if(animate) glutIdleFunc(animation_1);
    //     else glutIdleFunc(NULL);
    // }
    //  break;
    // case 'N':
    // if(state == HIERARCHY) {
    //     animate = 1;
    //     if(animate) glutIdleFunc(animation_2);
    //     else glutIdleFunc(NULL);
    //   }
    //   break;
    // case 'm':
    // if(state == HIERARCHY) {
    //     animate = 1;
    //     if(animate) glutIdleFunc(animation_3);
    //     else glutIdleFunc(NULL);
    //   }
    //     break;
    // case 'M':
    // if(state == HIERARCHY) {
    //     animate = 1;
    //     if(animate) glutIdleFunc(animation_4);
    //     else glutIdleFunc(NULL);
    //   }
    //     break;







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

void initialize(const char * file1)
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

  //Inicializamos la mallaTVT1 con el fichero
  mallaTVT1.initializeObject(file1);
  mallaTVT2.initializeRotationalObject("poligono");

  printHelp();
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
