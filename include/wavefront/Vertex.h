#ifndef WAVEFRONT_VERTEX_H
#define	WAVEFRONT_VERTEX_H

namespace Wavefront
{

struct Vertex
{
  float x;
  float y;
  float z;

  Vertex(float x, float y, float z);
  Vertex(Vertex* vertex);
  Vertex();
  ~Vertex();

  float getX();
  float getY();
  float getZ();

  void setX(float x);
  void setY(float y);
  void setZ(float z);

};

}

#endif

