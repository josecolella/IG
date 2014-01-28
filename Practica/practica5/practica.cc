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
#define BUFSIZE 512


GLint animate = 0; //Para hacer animation o no
GLint texture = 0;
//enum que denota los diferentes estados
enum state_t {NONE=0,PLY, ROTATION, HIERARCHY, P4};
enum mouse_t {LEFT, RIGHT, MIDDLE};
bool isP4 = false; //Modo practica 4
mouse_t mouse_state; // El estado del raton





//Variables de gestion de raton
int mouse_x,
mouse_y,
ynew,
xn;

int isSelected = 0; // Si un elemento esta seleccionado
int selectedIndex = -1; //No hay indice de elemento escogido

const char *rotation_body_file = "poligono.ply";
// tamaño de los ejes
const int AXIS_SIZE=5000;


static GLfloat spin = 0.0;
static GLfloat spin2 = 0.0;
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
MallaTVT * peonMadera;
MallaTVT * peonBlanco;
MallaTVT * peonNegro;

//Robot de la practica3
Robot robot;
BeverageCan * can = NULL;

//Fuentes de Luz
LightSource * source1 = NULL;
LightSource * source2 = NULL;

//Variable que destaca el estado de dibujo. PLY, ROTACIONAL, HIERARCHY
state_t state = NONE;
state_t lastState = NONE;
//Variable que destaca el modo de visualizacion
visual_t visualization = POINT;
visual_t last_visualization = POINT;
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
    glPushMatrix();
    glScalef(3.0,3.0,3.0);
    can->draw(visualization);
    glPopMatrix();
    glPushMatrix();
    glScalef(0.5,0.5,0.5);
    glPushMatrix();
    glTranslatef(0.0,1.5,4.0);
    glPushMatrix();
    GLfloat shiny = 100.0;
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    peonMadera->draw(visualization);
    glPopMatrix();
    glTranslatef(3.5,0.0,0.0);
    peonBlanco->draw(visualization);
    glTranslatef(3.5,0.0,0.0);
    GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0};
    peonNegro->draw(visualization);
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
      //glutWireCube(1.0);
      mallaTVT1.draw(visualization);
      break;
      case ROTATION:
      mallaTVT2.draw(visualization);
      break;
      case HIERARCHY:
      robot.draw(GL_RENDER,visualization ,body_rotations, arm_rotations, eye_rotations);
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
    GLfloat positional[] = {-3.0,-15.0, 1.0, 1.0};
    GLfloat directional[] = {3.0,15.0,0.0,0.0};
    if(state == P4) {
      light_t type1 = DIRECTIONAL;
      light_t type2 = POSITIONAL;
      source1 = new LightSource(GL_LIGHT0, 0.0, 0.0, _vertex3f(1.0,1.0,1.0), type2, positional);
      source2 = new LightSource(GL_LIGHT1, spin, spin2, _vertex3f(0.6,0.6,0.6), type1, directional);
      source1->activate();
      source2->activate();
    }
    else{
      glDisable(GL_LIGHTING);
      if(source1!= NULL)
        source1->disactivate();
      if(source2 != NULL)
        source2->disactivate();
    }
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
  cout << endl;
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

//Menu de ayuda de la practica 4
void printHelpP4() {

  cout << endl;
  cout << "-----Posibles comandos: ------------" << endl;
  cout << "?: Repetir este menu de ayuda" << endl;
  cout << "1: Sombreado plano" << endl;
  cout << "2: Sombreado de suave" << endl;
  cout << "4: Salir de modo Práctica 4" << endl;
  cout << "A: Aumentar el valor de beta" << endl;
  cout << "Z: Disminuir el valor de beta" << endl;
  cout << "X: Aumentar el valor de alpha" << endl;
  cout << "C: Disminuir el valor de alpha" << endl;

}

//Funcion que define las teclas de la practica 4
bool p4_keys(unsigned char Tecla)
{
  bool actualizar = true;
  switch(toupper(Tecla)) {
    case '?':
    printHelpP4();
    break;
    case '1':
    visualization = ILUM_PLANO;
    glutPostRedisplay();
    break;
    case '2':
    visualization = ILUM_SOFT;
    glutPostRedisplay();
    break;
    case '4':
    isP4 = false;
    state = lastState;
    visualization = last_visualization;
    printHelpP1ToP3();
    break;
    case 'A':
    spin = (spin + 3);
    glutPostRedisplay();
    break;
    case 'Z':
    spin = (spin - 3);
    glutPostRedisplay();
    break;
    case 'X':
    spin2 += 3;
    glutPostRedisplay();
    break;
    case 'C':
    spin2 -= 3;
    glutPostRedisplay();
    break;
    default:
    glutPostRedisplay();
    break;
  }
  return actualizar;

}

//Funcion que define las teclas de la practica 1 - 3
bool p1_to_p3_keys(unsigned char Tecla)
{
  bool actualizar = true;
  switch(Tecla) {
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
    isP4 = true;
    //Guardar el ultimo estado
    lastState = state;
    state = P4;
    last_visualization = visualization;
    printHelpP4();
    visualization = ILUM_PLANO;
    break;
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
    default: glutPostRedisplay(); break;
  }
  return actualizar;
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
  bool actualizar = true;;
  switch (Tecla1) {
    case 'Q': exit(0); break;
    case 27: exit(0); break;
    default:
    switch(isP4) {
      case true:
      printHelpP4();
      actualizar = p4_keys(Tecla1);
      glutPostRedisplay();
      break;
      case false:
      printHelpP1ToP3();
      actualizar = p1_to_p3_keys(Tecla1);
      glutPostRedisplay();
      break;
      default:
      glutPostRedisplay(); break;

    }
    if(actualizar)
      glutPostRedisplay();
    break;


  }

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
   case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break; //Zoom out
   case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break; //Zoom in
 }
 glutPostRedisplay();
}


void processHits(GLint hits, GLuint *buffer)
{
  unsigned int i,j;
  GLuint names;
  GLuint *ptr;
  printf("%d\n", hits);
  for(int i=0;i<hits;i++)
  {
    names = *ptr;
    printf("number of names for hit = %d\n", names);
  }
}

//Seleccionar elementos
int pick(int x, int y, int * selected, int * i)
{
  GLuint selectBuf[BUFSIZE];
  GLint hits, viewport[4];
  glSelectBuffer (BUFSIZE, selectBuf);
  glGetIntegerv (GL_VIEWPORT, viewport);
  (void) glRenderMode (GL_SELECT);
  glInitNames();
  glPushName(0);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPickMatrix ( x, viewport[3] - y, 5.0, 5.0, viewport);
    // glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
    //draw ();
  hits = glRenderMode (GL_RENDER);
  
  //processHits(hits, selectBuf);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glutPostRedisplay();
    // glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}
//Se llama cuando se actue sobre algun boton del raton
void mouse(int button, int estado, int x, int y)
{
  switch(button)
  {
    case GLUT_RIGHT_BUTTON:
    if(estado == GLUT_DOWN){
      mouse_state = RIGHT;
      mouse_x = x; //Posicion x del raton
      mouse_y = y; //Posicion y del raton
      glutPostRedisplay();
    }
    else{
      mouse_state = RIGHT;
    }
    break;
    case GLUT_LEFT_BUTTON:
    {
      if(estado == GLUT_DOWN) {
        mouse_state = LEFT; 
        if(state == HIERARCHY){
          mouse_x = x;
          mouse_y = y;
          // pick(mouse_x,mouse_y, &isSelected, &selectedIndex);
        }
      }
    }
    glutPostRedisplay();
    break;

    case 3:
    if (estado == GLUT_UP) return;
    //Zoom in
    Observer_distance/=1.2;
    glutPostRedisplay();
    break;
    case 4:
    //Zoom out
    Observer_distance*=1.2;
    glutPostRedisplay();
    break;
    default:
    break;
  }
}

//Posicion del cursor, almacenar el estado de los botones del raton
//Comprueba si el boton derecho esta pulsado
void RatonMovido(int x, int y)
{
  if(mouse_state == RIGHT)
  {
    //Posiciones de la camara
    xn = Observer_angle_y + (x - mouse_x);
    ynew = Observer_angle_x + (y - mouse_y);

    Observer_angle_x = ynew;
    Observer_angle_y = xn;

    mouse_x = x;
    mouse_y = y;
    glutPostRedisplay();
  }
  else if(mouse_state == LEFT)
  {

    mouse_x = x;
    mouse_y = y;
    glutPostRedisplay();
  }
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


  mallaTVT1.initializeObject(file1);
  mallaTVT2.initializeRotationalObject(rotation_body_file);

  GLfloat whiteSpecular[] = {1.0, 1.0, 1.0};
  GLfloat blackSpecular[] = {0.0,0.0,0.0};
  GLfloat lowAmbient[] = {0.3, 0.3, 0.3};
  GLfloat a[] = {0.1,0.1,0.1};

  peonMadera = new MallaTVT("text-madera.jpg");
  peonMadera->initializeRotationalObject(rotation_body_file);

  peonMadera->setAmbient(a);
  peonMadera->setDiffuse(whiteSpecular);
  peonMadera->setSpecular(whiteSpecular);
  peonMadera->setBrightness(30);


  peonBlanco = new MallaTVT();
  peonBlanco->initializeRotationalObject(rotation_body_file);
  peonBlanco->setAmbient(lowAmbient);
  peonBlanco->setDiffuse(whiteSpecular);
  peonBlanco->setSpecular(blackSpecular);
  peonBlanco->setBrightness(30);

  peonNegro = new MallaTVT();
  peonNegro->initializeRotationalObject(rotation_body_file);
  peonNegro->setAmbient(blackSpecular);
  peonNegro->setDiffuse(lowAmbient);
  peonNegro->setSpecular(whiteSpecular);
  peonNegro->setBrightness(30);

  can = new BeverageCan();

  printHelpP1ToP3();
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
  //Funcion creada para gestionar eventos del raton
  glutMouseFunc(mouse);
  glutMotionFunc(RatonMovido);
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
