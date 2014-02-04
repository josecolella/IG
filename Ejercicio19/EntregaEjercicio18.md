Ejercicio 19
============

Jose Miguel Colella
--------------------

- El código que visualizar el Android que puede rotar en los brazos y en la cabeza es el siguiente. 

A continuación podemos ver lo que se ha agregado a la clase Android para habilitar las rotaciones de los brazos y de la cabeza. Se ha modificado los metodos
`draw_head` y `draw_body`, agregando los parametros necesarios. 

```cpp

void Android :: draw_head(int head_rotation)
{
  
  glPushMatrix();
    glRotatef(head_rotation, 0.0,1.0,0.0);
  glPushMatrix();
    glTranslatef(0.0,-0.75,0.0);
    glScalef(1.9,1.9,1.9);
    android_head->draw(visualization);
    glPushMatrix();
      glTranslatef(0.0,1.0,0.5);
      glPushMatrix();
        glTranslatef(0.3,0.0,0.0);
        draw_eyes();
      glPopMatrix();
      glPushMatrix();
        glTranslatef(-0.3,0.0,0.0);
        draw_eyes();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();
  glPushMatrix();
    glPushMatrix();
      glTranslatef(0.8,2.2,0.0);
      glScalef(0.1,0.5,0.1);
      glRotatef(-50.0,0.0,0.0,1.0);
      draw_antenna();
    glPopMatrix();  
    glPushMatrix();
      glTranslatef(-0.8,2.2,0.0);
      glScalef(0.1,0.5,0.1);
      glRotatef(50.0,0.0,0.0,1.0);
      glColor3f(0.0,1.0,0.0);
      draw_antenna();
    glPopMatrix();
  glPopMatrix();
  glPopMatrix();
}

void Android :: draw_body(int left_arm_rotation, int right_arm_rotation)
{
  glPushMatrix();
    glScalef(2.0,2.5,2.0);
    glTranslatef(0.0,-0.5,0.0);
    android_body->draw(visualization);
  glPopMatrix();
  glPushMatrix();
    glScalef(0.8,0.8,0.8);
    glPushMatrix();
      glRotatef(right_arm_rotation, 1.0,0.0,0.0);
      glTranslatef(0.0,-0.5,0.0);
      glPushMatrix();
        glTranslatef(-1.5,0.5,0.0);
        draw_arm();
      glPopMatrix();
    glPopMatrix();
    glPushMatrix();
      glRotatef(left_arm_rotation, 1.0,0.0,0.0);
      glTranslatef(0.0,-0.5,0.0);
      glPushMatrix();
        glTranslatef(1.5,0.5,0.0);
        glColor3f(0.0,1.0,0.0);
        draw_arm();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0.0,-1.0,0.0);
    glScalef(1.1,0.5,1.1);
    glPushMatrix();
      glTranslatef(-0.5,0.0,0.0);
      draw_leg();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.5,0.0,0.0);
      draw_leg();
    glPopMatrix();
  glPopMatrix();
}
```


Para la parte de la rotación he asignado acciones correspondientes a pulsaciones de teclas

```cpp
 if(left_arm_rotation > -90)
      left_arm_rotation = left_arm_rotation - 1;
    glutPostRedisplay();
    break;
    case 'Z':
    if(left_arm_rotation < 45)
      left_arm_rotation = left_arm_rotation + 1;
    glutPostRedisplay();
    break;
    case 'x':
    if(right_arm_rotation > -90)
      right_arm_rotation = right_arm_rotation - 1;
    glutPostRedisplay();
    break;
    case 'X':
    if(right_arm_rotation < 45)
      right_arm_rotation = right_arm_rotation + 1;
    glutPostRedisplay();
    break;
    case 'c':
    if(head_rotation > -45)
      head_rotation = head_rotation - 1;
    glutPostRedisplay();
    break;
    case 'C':
    if(head_rotation < 45)
      head_rotation = head_rotation + 1;
    glutPostRedisplay();
    break;
```

En la siguientes imagenes podemos visualizar el robot con las correspondinetes rotaciones de brazo y de cabeza

!["1"](https://raw.github.com/josecolella/IG/master/Ejercicio19/animated.gif?token=1974588__eyJzY29wZSI6IlJhd0Jsb2I6am9zZWNvbGVsbGEvSUcvbWFzdGVyL0VqZXJjaWNpbzE5L2FuaW1hdGVkLmdpZiIsImV4cGlyZXMiOjEzOTIxMzE1NDB9--1b5a581c24614d3155080149274412a846147add)

Si quiere visualizar el video bien, recomiendo 