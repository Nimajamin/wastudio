#ifndef WAVEFRONT_PART_H
#define	WAVEFRONT_PART_H

#include <string>
#include <wavefront/auto_vector.h>

namespace Wavefront
{

class MaterialGroup;
class Face;
class Model;
class Vertex;

class Part
{
private:
  Model* model;
  std::string name;
  auto_vector<Face> faces;
  auto_vector<MaterialGroup> materialGroups;
  float offsetX;
  float offsetY;
  float offsetZ;
  bool highlighted;
  float maxX;
  float minX;
  float maxY;
  float minY;
  float maxZ;
  float minZ;
  bool needsResend;
  std::auto_ptr<Model> attachedModel;

  void translate(int undo);
  void resend();

public:
  Part(Model* model, std::string name);
  ~Part();

  void setHighlighted(bool highlighted);
  std::string getName();
  auto_vector<Face>* getFaces();
  void addFace(Face* face);
  void draw();
  void getCollidingFaces(Vertex* center, Vertex* halfsize, std::vector<Face*>* collidingFaces);
  void attachModel(Model* model);
  Vertex getSize();

};

}

#endif
