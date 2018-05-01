#ifndef WAVEFRONT_FACE_H
#define	WAVEFRONT_FACE_H

namespace Wavefront
{

class Vertex;
class Material;

class Face
{
private:
  Vertex a;
  Vertex b;
  Vertex c;
  //Vertex d;
  Vertex ta;
  Vertex tb;
  Vertex tc;
  //Vertex td;
  Vertex na;
  Vertex nb;
  Vertex nc;
  //Vertex nd;
  Material* material;
  bool hasTc;
  //bool isQuad;
  bool hasN;

  void calcNormal(Vertex a, Vertex b, Vertex c, Vertex* result);
  void ReduceToUnit(float vector[3]);
  void calcNormal(float v[3][3], float out[3]);

public:
  //Face(Vertex a, Vertex b, Vertex c, Vertex d);
  Face(Vertex a, Vertex b, Vertex c);
  ~Face();

  //void draw(bool highlighted = false);
  Vertex* getNa();
  Vertex* getNb();
  Vertex* getNc();

  Vertex* getA();
  Vertex* getB();
  Vertex* getC();

  Vertex* getTa();
  Vertex* getTb();
  Vertex* getTc();

  float getMaxX();
  float getMinX();

  float getMaxY();
  float getMinY();

  float getMaxZ();
  float getMinZ();

  Material* getMaterial();
  void setMaterial(Material* material);
  //void setTextureCoords(Vertex ta, Vertex tb, Vertex tc, Vertex td);
  void setTextureCoords(Vertex ta, Vertex tb, Vertex tc);
  void setNormals(Vertex a, Vertex b, Vertex c);
  bool isColliding(Vertex* center, Vertex* halfsize);

};

}

#endif

