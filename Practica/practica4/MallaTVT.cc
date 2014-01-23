#include "MallaTVT.h"
#include "file_ply_stl.h"
#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <cmath>
#include <iostream>
#include <cassert>
using namespace std;


MallaTVT :: MallaTVT() {
  materialPtr = new Material();
}

MallaTVT :: MallaTVT(const char * textureFile) {
  materialPtr = new Material(textureFile);
}

MallaTVT :: ~MallaTVT() {
  if(materialPtr != NULL)
  {
    delete materialPtr;
  }
}


void MallaTVT :: initializeObject(const char * filename) {
  ply::read(filename, vertices_ply, caras_ply);
  for (int i = 0; i < vertices_ply.size(); i +=3)
  {
    _vertex3f tmp;
    tmp.x = vertices_ply[i];
    tmp.y = vertices_ply[i+1];
    tmp.z = vertices_ply[i+2];
    this->Vertices.push_back(tmp);
  }
  for (int i = 0; i < caras_ply.size(); i += 3)
  {
    _vertex3ui tmp;
    tmp._0 = caras_ply[i];
    tmp._1 = caras_ply[i+1];
    tmp._2 = caras_ply[i+2];
    this->caras.push_back(tmp);
  }
}




void MallaTVT :: initializeRotationalObject(const char * filename)
{
  initializeObject(filename);

  numInitialVertices = this->Vertices.size();
  float angulo = 0.1745;
  float rotation = ((360 / 10) -1);
  //Hacemos las transformaciones
  for(int j=0;j<rotation;j++){

   for(int i = 0;i < numInitialVertices;i++) {
    _vertex3f tmp;
    tmp.x = cos(angulo) * Vertices[i].x +  sin(angulo) * Vertices[i].z;
    tmp.y = Vertices[i].y;
    tmp.z = -sin(angulo) * Vertices[i].x + cos(angulo) * Vertices[i].z;
    this->Vertices.push_back(tmp);
  }
  angulo += 0.1745;
}
  //cout << Vertices.size() << endl;

int i = 0;
int j = 0;
  //Construimos las caras para el modelo
for(i=0;i<Vertices.size()-numInitialVertices;i+=numInitialVertices){

 for(j = i;j<i+numInitialVertices-1;j++){
   _vertex3ui tmp;
   tmp._0 = j;
   tmp._1 = j+numInitialVertices+1;
   tmp._2 = j+numInitialVertices;
   caras.push_back(tmp);
   tmp._0 = j;
   tmp._1 = j+1;
   tmp._2 = j+numInitialVertices+1;
   caras.push_back(tmp);
 }
}

//Agregamos la caras que conectan el ultimo Vertice con el primero
for(int l=0,k=Vertices.size()-numInitialVertices;l<numInitialVertices-1;l++,k++){
 _vertex3ui tmp;
 tmp._0 = k;
 tmp._1 = l+1;
 tmp._2 = l;
 caras.push_back(tmp);
 tmp._0 = k;
 tmp._1 = k+1;
 tmp._2 = l+1;
 caras.push_back(tmp);
}

//Queda crear las tapas y las caras para las tapas
//Hay que agregar dos vertices al final del vector
//Agregamos el vertice superior e inferior

//Vertice inferior
_vertex3f tmp;
tmp.x = 0;
tmp.y = Vertices[0].y;
tmp.z = 0;
this->Vertices.push_back(tmp);
//Vertice superior
tmp.x = 0;
tmp.y = Vertices[Vertices.size() -2].y;
tmp.z = 0;
this->Vertices.push_back(tmp);




_vertex3ui tmp2;

  //Tapa inferior para el ultimo vertice y el primero
tmp2._0 = Vertices.size()-2-numInitialVertices;
tmp2._1 = Vertices.size()-2;
tmp2._2 = 0;
caras.push_back(tmp2);


   //Crear las caras para el punto el inferior
for(int i=0;i<Vertices.size()-2;i+=numInitialVertices){
  _vertex3ui tmp;
  tmp._0 = i;
  tmp._1 = i+numInitialVertices;
  tmp._2 = Vertices.size() -2;
  caras.push_back(tmp);
}



  //Tapa superior para el primer punto del ultimo vertice con el primero
  tmp2._0 = Vertices.size()-3; //El ultimo punto del ultimo vertice
  tmp2._1 = Vertices.size()-1; //El punto del centro
  tmp2._2 = numInitialVertices-1; //El ultimo punto del primer vertice
  caras.push_back(tmp2);


  //Crear las caras para el superior
  //Vamos hacia Vertices.size() -3 debido a que tenemos
  //que considerar la cara que se ha tenido que hacer
  //manualmente para la tapa inferior
  for(int i=numInitialVertices-1;i<Vertices.size()-3;i+=numInitialVertices){
   _vertex3ui tmp;
   tmp._0 = i;
   tmp._1 = Vertices.size()-1;
   tmp._2 = i+numInitialVertices;
   caras.push_back(tmp);
 }
//Quitar las tapas de la malla
//Dada una cara triangular con vertices A,B,C

 for (int i = 0; i < caras.size(); i++){
   _vertex3f tmp1,tmp2;
   tmp1 = Vertices[caras[i]._1] - Vertices[caras[i]._0];
   tmp2 = Vertices[caras[i]._2] - Vertices[caras[i]._0];
   normal_caras.push_back((tmp1.cross_product(tmp2)).normalize());
 }

 //Limpiamos el vector de la basura que puede contener
 this->normal_vertices.clear();
 //Lo rellenamos de 0
 this->normal_vertices.resize(Vertices.size(), _vertex3f(0,0,0));

 //Este bucle calcula en cada iteraccion parte de la normal
 //de cada vertice
 for(int i=0;i<this->normal_caras.size();i++)
 {
  //Para calcular el normal de vertices de cada normal de cara
   this->normal_vertices[caras[i]._0] += this->normal_caras[i];
   this->normal_vertices[caras[i]._1] += this->normal_caras[i];
   this->normal_vertices[caras[i]._2] += this->normal_caras[i];


 }


 //Normalizamos el resultado, y obtenemos los normales de vertices
 for(int i=0;i<this->normal_vertices.size();i++)
 {
  this->normal_vertices[i].normalize();
}

//Calculo de vector de texturas
_vertex2f pairValues;
vector<GLfloat> tmpVector;

float sum = 0.0;
tmpVector.push_back(sum);
for(int j = 1;j <this->numInitialVertices + 1;j++)
{
  sum += sqrt(pow(this->Vertices[j].x - this->Vertices[j-1].x,2) + pow(this->Vertices[j].y - this->Vertices[j-1].y,2) + pow(this->Vertices[j].z - this->Vertices[j-1].z,2));
  tmpVector.push_back(sum);
}

for(int i=0;i<int(rotation) + 1;i++)
{
  pairValues.s = (float(i)/rotation);
  for(int k = 0;k<tmpVector.size();k++)
  {
    pairValues.t = 1.0 - tmpVector[k]/tmpVector[tmpVector.size()-1];
    vector_texturas.push_back(pairValues);
  }
}

}


void MallaTVT :: initializeRotationalObject2(const char * filename)
{

  initializeObject(filename);

  numInitialVertices = this->Vertices.size();
  float angulo = 0.1745;
  float rotation = float(360 / 10);
  //Hacemos las transformaciones
  for(int j=0;j<int(rotation);j++){

   for(int i = 0;i < numInitialVertices;i++) {
    _vertex3f tmp;
    tmp.x = cos(angulo) * Vertices[i].x +  sin(angulo) * Vertices[i].z;
    tmp.y = Vertices[i].y;
    tmp.z = -sin(angulo) * Vertices[i].x + cos(angulo) * Vertices[i].z;
    this->Vertices.push_back(tmp);
  }
  angulo += 0.1745;
}

  //Construimos las caras para el modelo
for(int i=0, j=numInitialVertices-1;i<Vertices.size()-(numInitialVertices+1);i++){

  if((i-j) != 0 || i==0){
   _vertex3ui tmp;
   tmp._0 = i;
   tmp._1 = i+numInitialVertices+1;
   tmp._2 = i+numInitialVertices;
   caras.push_back(tmp);
   tmp._0 = i;
   tmp._1 = i+1;
   tmp._2 = i+numInitialVertices+1;
   caras.push_back(tmp);
 }
 else
  j+=numInitialVertices;
}


for (int i = 0; i < caras.size(); i++){
 _vertex3f tmp1,tmp2;
 tmp1 = Vertices[caras[i]._1] - Vertices[caras[i]._0];
 tmp2 = Vertices[caras[i]._2] - Vertices[caras[i]._0];
 normal_caras.push_back((tmp1.cross_product(tmp2)).normalize());
}

 //Limpiamos el vector de la basura que puede contener
this->normal_vertices.clear();
 //Lo rellenamos de 0
this->normal_vertices.resize(Vertices.size(), _vertex3f(0,0,0));

 //Este bucle calcula en cada iteraccion parte de la normal
 //de cada vertice
for(int i=0;i<this->normal_caras.size();i++)
{
  //Para calcular el normal de vertices de cada normal de cara
 this->normal_vertices[caras[i]._0] += this->normal_caras[i];
 this->normal_vertices[caras[i]._1] += this->normal_caras[i];
 this->normal_vertices[caras[i]._2] += this->normal_caras[i];


}


 //Normalizamos el resultado, y obtenemos los normales de vertices
for(int i=0;i<this->normal_vertices.size();i++)
{
  this->normal_vertices[i].normalize();
}
  ///Coordenadas
 //Rellenar texturas

_vertex2f pairValues;
vector<GLfloat> tmpVector;

float sum = 0.0;
tmpVector.push_back(sum);
for(int j = 1;j <this->numInitialVertices;j++)
{
    //x y z
  sum += sqrt(pow(this->Vertices[j].x - this->Vertices[j-1].x,2) + pow(this->Vertices[j].y - this->Vertices[j-1].y,2) + pow(this->Vertices[j].z - this->Vertices[j-1].z,2));
  tmpVector.push_back(sum);
}

for(int i=0;i<int(rotation) + 1;i++)
{
  pairValues.s = (float(i)/rotation);
  for(int k = 0;k<tmpVector.size();k++)
  {
    pairValues.t = 1.0 - tmpVector[k]/tmpVector[tmpVector.size()-1];
    vector_texturas.push_back(pairValues);
  }
}
}

void MallaTVT :: draw(visual_t visualization){

 if(visualization >= 1 && visualization <= 6){
   glPointSize(5);
   switch(visualization) {
    case POINT:
    glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
    break;
    case LINE:
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    break;
    case FILL:
    case CHECKERED:
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    break;
    case ILUM_PLANO:
    case ILUM_SOFT:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
    default:
    // glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
    break;

  }

  if(visualization ==  ILUM_PLANO)
  {
    glShadeModel(GL_FLAT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    materialPtr->activate();

    glBegin(GL_TRIANGLES);
    for(int i=0;i<normal_caras.size();i++)
    {
      if(!vector_texturas.empty())
        glTexCoord2d(vector_texturas[ caras[i]._0 ]._0 , vector_texturas[ caras[i]._0 ]._1);
      glNormal3f(normal_caras[ caras[i]._0 ].x, normal_caras[ caras[i]._0 ].y, normal_caras[ caras[i]._0 ].z);
      glVertex3f(Vertices[caras[i]._0].x,Vertices[caras[i]._0].y,Vertices[caras[i]._0].z);

      if(!vector_texturas.empty())
        glTexCoord2d(vector_texturas[ caras[i]._1 ]._0 , vector_texturas[ caras[i]._1 ]._1);
      glNormal3f(normal_caras[ caras[i]._1 ].x, normal_caras[ caras[i]._1 ].y, normal_caras[ caras[i]._1 ].z);
      glVertex3f(Vertices[caras[i]._1].x,Vertices[caras[i]._1].y,Vertices[caras[i]._1].z);

      if(!vector_texturas.empty())
        glTexCoord2d(vector_texturas[ caras[i]._2 ]._0 , vector_texturas[ caras[i]._2 ]._1);
      glNormal3f(normal_caras[ caras[i]._2 ].x, normal_caras[ caras[i]._2 ].y, normal_caras[ caras[i]._2 ].z);
      glVertex3f(Vertices[caras[i]._2].x,Vertices[caras[i]._2].y,Vertices[caras[i]._2].z);

    }
    glEnd();
  }
  else if(visualization == ILUM_SOFT)
  {
    glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Se activa el material
    materialPtr->activate();
    glBegin(GL_TRIANGLES);
    for(int i=0;i<caras.size();i++)
    {
      if(!vector_texturas.empty())
        glTexCoord2d(vector_texturas[ caras[i]._0 ]._0 , vector_texturas[ caras[i]._0 ]._1);
      glNormal3f(normal_vertices[ caras[i]._0 ].x, normal_vertices[ caras[i]._0 ].y, normal_vertices[ caras[i]._0 ].z);
      glVertex3f(Vertices[caras[i]._0].x,Vertices[caras[i]._0].y,Vertices[caras[i]._0].z);

      if(!vector_texturas.empty())
        glTexCoord2d(vector_texturas[ caras[i]._1 ]._0 , vector_texturas[ caras[i]._1 ]._1);
      glNormal3f(normal_vertices[ caras[i]._1 ].x, normal_vertices[ caras[i]._1 ].y, normal_vertices[ caras[i]._1 ].z);
      glVertex3f(Vertices[caras[i]._1].x,Vertices[caras[i]._1].y,Vertices[caras[i]._1].z);

      if(!vector_texturas.empty())
        glTexCoord2d(vector_texturas[ caras[i]._2 ]._0 , vector_texturas[ caras[i]._2 ]._1);
      glNormal3f(normal_vertices[ caras[i]._2 ].x, normal_vertices[ caras[i]._2 ].y, normal_vertices[ caras[i]._2 ].z);
      glVertex3f(Vertices[caras[i]._2].x,Vertices[caras[i]._2].y,Vertices[caras[i]._2].z);

    }
    glEnd();
  }
  else {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < caras.size(); i++)
    {
      if(visualization == CHECKERED){
        if(i % 2 == 0)
          glColor3f(0,0,1);
        else
          glColor3f(1,0,0);
      }
      else
        glColor3f(0,1,0);
      glDisable(GL_LIGHTING);
      glDisable(GL_TEXTURE_2D);
      glVertex3f(Vertices[caras[i]._0].x,Vertices[caras[i]._0].y,Vertices[caras[i]._0].z);
      glVertex3f(Vertices[caras[i]._1].x,Vertices[caras[i]._1].y,Vertices[caras[i]._1].z);
      glVertex3f(Vertices[caras[i]._2].x,Vertices[caras[i]._2].y,Vertices[caras[i]._2].z);

    }
    glEnd();
  }
}



}

int MallaTVT :: getInitialVerticesNum() const{
 return this->numInitialVertices;
}


void MallaTVT :: setAmbient(GLfloat amb[MATERIAL_ARRAY_SIZE -1]){
  this->materialPtr->setAmbient(amb);
}

void MallaTVT :: setDiffuse(GLfloat dis[MATERIAL_ARRAY_SIZE -1])
{
  materialPtr->setDiffuse(dis);
}

void MallaTVT :: setSpecular(GLfloat spe[MATERIAL_ARRAY_SIZE -1])
{
  materialPtr->setSpecular(spe);
}

void MallaTVT :: setBrightness(GLfloat brillo){
  materialPtr->setBrightness(brillo);
}