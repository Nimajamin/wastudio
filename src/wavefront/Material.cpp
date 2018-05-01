#include <wavefront.h>

using namespace std;

namespace Wavefront
{

Material::Material(string name)
{
  r = 0.5;
  g = 0.5;
  b = 0.5;
  this->name = name;
}

Material::~Material()
{

}

float Material::getR()
{
  return r;
}

float Material::getG()
{
  return g;
}

float Material::getB()
{
  return b;
}

void Material::setR(float r)
{
  this->r = r;
}

void Material::setG(float g)
{
  this->g = g;
}

void Material::setB(float b)
{
  this->b = b;
}

string Material::getName()
{
  return name;
}

void Material::setTexture(Texture* texture)
{
  this->texture.reset(texture);
}

Texture* Material::getTexture()
{
  return texture.get();
}

}
