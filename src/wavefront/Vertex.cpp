#include <wavefront.h>

namespace Wavefront
{

Vertex::Vertex(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Vertex::Vertex(Vertex* vertex)
{
  this->x = vertex->x;
  this->y = vertex->y;
  this->z = vertex->z;
}

Vertex::Vertex()
{
  x = 0;
  y = 0;
  z = 0;
}

Vertex::~Vertex()
{
  
}

float Vertex::getX()
{
  return x;
}

float Vertex::getY()
{
  return y;
}

float Vertex::getZ()
{
  return z;
}

void Vertex::setX(float x)
{
  this->x = x;
}

void Vertex::setY(float y)
{
  this->y = y;
}

void Vertex::setZ(float z)
{
  this->z = z;
}

}
