#ifndef WAVEFRONT_MATERIAL_H
#define	WAVEFRONT_MATERIAL_H

#include <string>

namespace Wavefront
{

class Texture;
class Material
{
private:
  float r;
  float g;
  float b;
  std::string name;
  std::auto_ptr<Texture> texture;

public:
  Material(std::string name);
  ~Material();

  float getR();
  float getG();
  float getB();

  void setR(float r);
  void setG(float g);
  void setB(float b);

  void setTexture(Texture* texture);
  Texture* getTexture();

  std::string getName();
  
};

}

#endif

