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
#include "BeverageCan.h"
#include "visualtype.h"
#include "jpg_imagen.hpp"
#include "LightSource.h"


GLint animate = 0; //Para hacer animation o no
GLint texture = 0;
GLfloat i = 0.0;
//enum que denota los diferentes estados
enum state_t {NONE=0,PLY, ROTATION, HIERARCHY, P4};
bool isP4 = false; //Modo practica 4

const char *rotation_body_file = "poligono.ply";
// tamaño de los ejes
const int AXIS_SIZE=5000;


static GLfloat spin = 0.5;
static GLfloat spin2 = 0.5;
//Variable utilizadas para las animaciones
int 
  animation1 = -1,
  max_range = 5,
  min_range = -5,
  animation6 = 1;
float 
  eye_top = -8.0,
  eye_min = 0.0,
  animation2 = -0.1;


//Variables usadas para contener el modelo PLY, ROTACIONAL, Y JERARQUICO
MallaTVT mallaTVT1;
MallaTVT mallaTVT2;
MallaTVT peonMadera;
MallaTVT peonBlanco;
MallaTVT peonNegro;


Robot robot;
BeverageCan * can = NULL;

//Fuentes de Luz
LightSource * source1 = NULL;
LightSource * source2 = NULL;

//Variable que destaca el estado de dibujo. PLY, ROTACIONAL, HIERARCHY
state_t state = NONE;
//Variable que destaca el modo de visualizacion
visual_t visualization = POINT;
//Variables que se cambian en base a las teclas usadas
static float shoulder = 0, elbow = 0, left_index_rotation = 0, right_finger_rotation = 0, left_top = 0, right_top = 0;
static float torso = 0, arm_rotation = 0;
static float eye_rotation = 0.0, body_y_rotation = 0.0, body_translate = 0.0;

//Vector de Rotaciones
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
  if(arm_rotations[1] < 90)
    arm_rotations[1] += 1;
  if(arm_rotations[1] == 90) {
    eye_rotations = (eye_rotations + animation2);
    if(eye_rotations < eye_top)
    {
      eye_rotations = eye_top;
      animation2 = -animation2;
    }
    else if(eye_rotations > eye_min)
    {
      eye_rotations = eye_min;
      animation2 = -animation2;
    }
    body_rotations[3] = body_rotations[3] + animation1;
    if(body_rotations[3] > max_range) {
      body_rotations[3] = max_range;
      animation1 = -animation1;
    }
    else if(body_rotations[3] < min_range)
    {
      body_rotations[3] = min_range;
      animation1 = -animation1;
    }
  }

  glutPostRedisplay();
}

void animation_3() {
  if(body_rotations[1] < 90)
    body_rotations[1] = (body_rotations[1] + 1.0);
  if(body_rotations[1] == 90) {
    if(body_rotations[0] < 1.0) {
      body_rotations[0] = (body_rotations[0] + 0.05);
    }
    if(body_rotations[2] < 120)
      body_rotations[2]+= 1;

  }
  glutPostRedisplay();
}



void animation_4() {

  if(body_rotations[2] > 0)
   body_rotations[2] -= 1;
 if(body_rotations[1] > 0)
  body_rotations[1] = (body_rotations[1] - 1.0);
if(body_rotations[0] > 0.0)
  body_rotations[0] = (body_rotations[0] - 0.05);

glutPostRedisplay();
}


void animation_5() {

  if(body_rotations[2] < 120)
    body_rotations[2]+= 1;
  if(body_rotations[3] < 90)
    body_rotations[3] = body_rotations[3] + animation6;
  if(body_rotations[3] == 90){
    if(arm_rotations[1] > -35)
      arm_rotations[1] -= 1;
    if(arm_rotations[1] == -35)
      if(arm_rotations[2] > -20 && arm_rotations[4] > -20) {
        arm_rotations[2] -= 1;
        arm_rotations[4] -= 1;
      }
      if(arm_rotations[2] == -20 && arm_rotations[4] == -20) {
        if(arm_rotations[3] > -15 && arm_rotations[5] > -20)
        {
          arm_rotations[3] -= 1;
          arm_rotations[5] -= 1;
        }
      }


    }
    if(arm_rotations[3] == -15 && arm_rotations[4] == -20) {
      if(arm_rotations[1] > -38)
        arm_rotations[1] -= 0.5;
      if(arm_rotations[1] == -38) {
        if(arm_rotations[0] < 10)
          arm_rotations[0] += 1;
        if(arm_rotations[0] == 10){
          if(arm_rotations[1] > -43)
            arm_rotations[1] -= 1;
        }
      }
    }




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

//Modo practica 4
  void p4_scene(){
    // glPushMatrix();
    // glutSolidSphere(1.0,20,16); //Para el ejemplo *QUITAR*
    // glPopMatrix();

    can->draw(visualization); 
    glPushMatrix();
      glScalef(0.2,0.2,0.2);
      glPushMatrix();
        glTranslatef(0.0,1.5,4.0);
        peonMadera.draw(visualization);
        glTranslatef(3.0,0.0,0.0);
        peonBlanco.draw(visualization);
        glTranslatef(3.0,0.0,0.0);
        peonNegro.draw(visualization);
      glPopMatrix();
    glPopMatrix();
  }

//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

  void draw_objects()
  {

    switch(state) {
      case PLY:
      mallaTVT1.draw(visualization);
      break;
      case ROTATION:
      mallaTVT2.draw(visualization);
      break;
      case HIERARCHY:
      robot.draw(visualization ,body_rotations, arm_rotations, eye_rotations);
      break;
      case P4:
      p4_scene();
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
    GLfloat pos[] = {0.0,0.0,1.5,1.0};

    glPushMatrix();
      glTranslatef(0.0,0.0,-5.0);
      glPushMatrix();
        glRotatef((GLfloat) spin, 1.0,0.0,0.0);
        glRotatef((GLfloat) spin2, 0.0,1.0,0.0);
        glLightfv(GL_LIGHT0, GL_POSITION, pos);

      glTranslatef(0.0,0.0,1.5);
      glDisable(GL_LIGHTING);
      glColor3f(0.0,1.0,1.0);
      glutWireCube(0.1);
      glEnable(GL_LIGHTING);
      glPopMatrix();
      // glutSolidTorus(0.275,0.85,8,15);
    glPopMatrix();

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
 void printHelpP1ToP3() {
  cout << "Posibles comandos: " << endl;
  cout << "?: Repetir este menu de ayuda" << endl;
  cout << "p: Visualizar en modo punto" << endl;
  cout << "l: Visualizar en modo linea" << endl;
  cout << "s: Visualizar en modo solido" << endl;
  cout << "a: Visualizar en modo ajedrez" << endl;
  cout << "1: Activar objeto PLY" << endl;
  cout << "2: Activar objeto por revolucion" << endl;
  cout << "3: Activar objeto jerarquico" << endl;
  cout << "4. Entrar en modo Práctica 4" << endl;
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
  cout << "b: Animacion 1 (ESPERAR QUE TERMINE)" << endl;
  cout << "n: Animacion 2 positiva (ESPERAR QUE TERMINE)" << endl;
  cout << "N: Animacion 2 negativa (ESPERAR QUE TERMINE)" << endl;
  cout << "m: Animacion 3 positiva (ESPERAR QUE TERMINE)" << endl;


}


void printHelpP4() {
  cout << "Posibles comandos: " << endl;
  cout << "?: Repetir este menu de ayuda" << endl;
  cout << "A: Aumentar el valor de beta" << endl;
  cout << "Z: Disminuir el valor de beta" << endl;
  cout << "X: Aumentar el valor de alpha" << endl;
  cout << "C: Disminuir el valor de alpha" << endl;

}

void p4_keys(unsigned char Tecla)
{
  switch(Tecla){
    case '?':
    printHelpP4();
    break;
    case '4':
    isP4 = false;
    break;
    case 'A':
              //aumentar el valor de beta
    glutPostRedisplay();
    break;
    case 'Z':
              //disminunir el valor de beta
    glutPostRedisplay();
    break;
    case 'X':
              //aumentar el valor de alpha
    glutPostRedisplay();
    break;
    case 'C':
              //disminuir el valor de alpha
    glutPostRedisplay();
    break;
  }

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
  switch (Tecla1) {
    //if(modo == p4) {tecla_p4(key); return}
    //Esta funcion gestiona todo relevante a la practica4
    //
    case 'Q': exit(0); break;
    case 27: exit(0); break;
    if(isP4)
    {
      cout << "Hello" << endl;
      p4_keys(Tecla1);
    }
    else {
      case '?':
      printHelpP1ToP3();
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
      case '4':
      isP4 = !isP4;
      state = P4;
      case 'p':
      visualization = POINT;
      glutPostRedisplay();
      break;
      case 'l':
      visualization = LINE;
      glutPostRedisplay();
      break;
      case 's':
      visualization = FILL;
      glutPostRedisplay();
      break;
      case 'a':
      visualization = CHECKERED;
      glutPostRedisplay();
      break;
      case 'r':
      spin += 1;
      glutPostRedisplay();
      break;
      case 'y':
      visualization = ILUM_SOFT;
      glutPostRedisplay();
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
        if(arm_rotations[2] < 0)
          arm_rotations[2] = arm_rotations[2] + 1;
        glutPostRedisplay();
      }
      break;
      case 'C':
      if(state == HIERARCHY) {
        animate = 0;
        if(arm_rotations[2] > -45)
          arm_rotations[2] = arm_rotations[2] - 1;
        glutPostRedisplay();
      }
      break;
      case 'v':
      if(state == HIERARCHY) {
        animate = 0;
        if(arm_rotations[3] < 0)
          arm_rotations[3] = arm_rotations[3] + 1;
        glutPostRedisplay();
      }
      break;
      case 'V':
      if(state == HIERARCHY) {
        animate = 0;
        if(arm_rotations[3] > -45)
          arm_rotations[3] = arm_rotations[3] - 1;
        glutPostRedisplay();
      }
      break;
      case 'D':
      if(state == HIERARCHY) {
        animate = 0;
        if(arm_rotations[4] < 0)
          arm_rotations[4] = arm_rotations[4] + 1;
        glutPostRedisplay();
      }
      break;
      case 'd':
      if(state == HIERARCHY) {
        animate = 0;
        if(arm_rotations[4] > -45)
          arm_rotations[4] = arm_rotations[4] - 1;
        glutPostRedisplay();
      }
      break;
      case 'F':
      if(state == HIERARCHY) {
        animate = 0;
        if(arm_rotations[5] < 0)
          arm_rotations[5] = arm_rotations[5] + 1;
        glutPostRedisplay();
      }
      break;
      case 'f':
      if(state == HIERARCHY) {
        animate = 0;
        if(arm_rotations[5] > -45)
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
      case 'b':
      if(state == HIERARCHY) {
        animate = 1;
        if(animate){ glutIdleFunc(animation_1); }
        else glutIdleFunc(NULL);
      }
      break;
      case 'n':
      if(state == HIERARCHY) {
        animate = 1;
        if(animate) glutIdleFunc(animation_3);
        else glutIdleFunc(NULL);
      }
      break;
      case 'N':
      if(state == HIERARCHY) {
        animate = 1;
        if(animate) glutIdleFunc(animation_4);
        else glutIdleFunc(NULL);
      }
      break;
      case 'm':
      if(state == HIERARCHY) {
        animate = 1;
        if(animate) glutIdleFunc(animation_5);
        else glutIdleFunc(NULL);
      }
      break;
      case 'w':
        i += 0.1;
        glutPostRedisplay();
      break;


    }


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

  
  glEnable(GL_LIGHTING); //To enable lighting

  glEnable(GL_LIGHT0);
  //Inicializamos la mallaTVT1 con el fichero
  mallaTVT1.initializeObject(file1);
  mallaTVT2.initializeRotationalObject(rotation_body_file);
  peonMadera.initializeRotationalObject(rotation_body_file);
  peonNegro.initializeRotationalObject(rotation_body_file);
  peonBlanco.initializeRotationalObject(rotation_body_file);
  can = new BeverageCan();
  


  // visualization = ILUM_SOFT;
  // GLfloat ini1[2] = {90.0,90.0};
  // GLfloat ini2[2] = {-100.0,-30.0};
  // source1 = new LightSource(GL_LIGHT0, ini1, _vertex3f(1.0,1.0,1.0));
  // source2 = new LightSource(GL_LIGHT1, ini2, _vertex3f(0.8,0.3,0.2));
  // source1->activate();
  // source2->activate();
  printHelpP1ToP3();
}

//You have to integrate this into key func
void mouse(int button, int state, int x, int y)
{
  switch(button)
  {
    case GLUT_LEFT_BUTTON:
      if(state == GLUT_DOWN){
        spin = (spin + 10);
        glutPostRedisplay(); 
      }
      break;
    case GLUT_RIGHT_BUTTON:
        spin = (spin - 10);
        glutPostRedisplay();
      break;
    case GLUT_MIDDLE_BUTTON:
      spin2 += 10;
      glutPostRedisplay();
    break;
    default:
      break;
  }
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
  glutMouseFunc(mouse);

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
