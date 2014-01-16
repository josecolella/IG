#include "SpecializedMallaTVT.h"

void SpecializedMallaTVT :: initializeRotationalObject(const char * filename)
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
for(int i=0, j=numInitialVertices-1;i<Vertices.size()-(numInitialVertices+2);i++){

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


void SpecializedMallaTVT :: draw(visual_t visualization)
{
  {
   if(visualization ==  ILUM_PLANO)
   {
    glShadeModel(GL_FLAT);

    //Aqui va un material

    glBegin(GL_TRIANGLES);
    for(int i=0;i<normal_caras.size();i++)
    {
      glNormal3f(normal_caras[i]._0, normal_caras[i]._1, normal_caras[i]._2);
      glVertex3f(Vertices[normal_caras[i]._0].x,Vertices[normal_caras[i]._0].y,Vertices[normal_caras[i]._0].z);
      glVertex3f(Vertices[normal_caras[i]._1].x,Vertices[normal_caras[i]._1].y,Vertices[normal_caras[i]._1].z);
      glVertex3f(Vertices[normal_caras[i]._2].x,Vertices[normal_caras[i]._2].y,Vertices[normal_caras[i]._2].z);

    }
    glEnd();
  }
  else if(visualization == ILUM_SOFT)
  {
    //Aqui va un material
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
    assert(glGetError() == GL_NO_ERROR);
  }
}
}