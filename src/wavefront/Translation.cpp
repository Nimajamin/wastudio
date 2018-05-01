#include <wavefront.h>

namespace Wavefront
{

Translation::Translation(Part* part, float x, float y, float z, float xRotation, float yRotation, float zRotation)
{
  this->part = part;
  this->x = x;
  this->y = y;
  this->z = z;
  this->xRotation = xRotation;
  this->yRotation = yRotation;
  this->zRotation = zRotation;
}

Translation::~Translation()
{

}

Part* Translation::getPart()
{
  return part;
}

float Translation::getX()
{
  return x;
}

float Translation::getY()
{
  return y;
}

float Translation::getZ()
{
  return z;
}

void Translation::setX(float x)
{
  this->x = x;
}

void Translation::setY(float y)
{
  this->y = y;
}

void Translation::setZ(float z)
{
  this->z = z;
}

float Translation::getXRotation()
{
  return xRotation;
}

float Translation::getYRotation()
{
  return yRotation;
}

float Translation::getZRotation()
{
  return zRotation;
}

void Translation::setXRotation(float xRotation)
{
  this->xRotation = xRotation;
}

void Translation::setYRotation(float yRotation)
{
  this->yRotation = yRotation;
}

void Translation::setZRotation(float zRotation)
{
  this->zRotation = zRotation;
}

float Translation::getRelativeX()
{
  return (x / part->getSize().x) * 100.0f;
  //return x / part->getSize().x;
}

float Translation::getRelativeY()
{
  return (y / part->getSize().y) * 100.0f;
  //std::cout << part->getName() << " " << y << " " << part->getSize().y << std::endl;
  //return y / part->getSize().y;
  //return y;
}

float Translation::getRelativeZ()
{
  return (z / part->getSize().z) * 100.0f;
  //return z / part->getSize().z;
}

}
