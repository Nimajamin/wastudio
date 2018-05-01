#ifndef WAVEFRONT_TRANSLATION_H
#define	WAVEFRONT_TRANSLATION_H

namespace Wavefront
{

class Part;

class Translation
{
private:
  Part* part;
  float x;
  float y;
  float z;
  float xRotation;
  float yRotation;
  float zRotation;

public:
  Translation(Part* part, float x, float y, float z, float xRotation, float yRotation, float zRotation);
  ~Translation();

  Part* getPart();

  float getX();
  float getY();
  float getZ();

  float getRelativeX();
  float getRelativeY();
  float getRelativeZ();

  void setX(float x);
  void setY(float y);
  void setZ(float z);

  float getXRotation();
  float getYRotation();
  float getZRotation();

  void setXRotation(float xRotation);
  void setYRotation(float yRotation);
  void setZRotation(float zRotation);
  
};

}

#endif
