#include <wavefront.h>

#include <limits>

using namespace std;

namespace Wavefront
{

Part::Part(Model* model, string name)
{
  this->model = model;
  this->name = name;
  offsetX = 0;
  offsetY = 0;
  offsetZ = 0;
  highlighted = false;
  needsResend = false;

  maxX = 0;
  minX = 0;
  maxY = 0;
  minY = 0;
  maxZ = 0;
  minZ = 0;
}

Part::~Part()
{

}

void Part::attachModel(Model* model)
{
  attachedModel.reset(model);
}

string Part::getName()
{
  return name;
}

auto_vector<Face>* Part::getFaces()
{
  return &faces;
}

void Part::addFace(Face* face)
{
  faces.add(face);

  if(faces.size() == 1)
  {
    maxX = std::numeric_limits<float>::min();
    maxY = std::numeric_limits<float>::min();
    maxZ = std::numeric_limits<float>::min();

    minX = std::numeric_limits<float>::max();
    minY = std::numeric_limits<float>::max();
    minZ = std::numeric_limits<float>::max();

    //maxX = faces.at(0)->getMaxX();
    //maxY = faces.at(0)->getMaxY();
    //maxZ = faces.at(0)->getMaxZ();
    //minX = faces.at(0)->getMinX();
    //minY = faces.at(0)->getMinY();
    //minZ = faces.at(0)->getMinZ();
  }

  if (faces.at(faces.size() - 1)->getMaxX() > maxX)
  {
    maxX = faces.at(faces.size() - 1)->getMaxX();
  }

  if (faces.at(faces.size() - 1)->getMaxY() > maxY)
  {
    maxY = faces.at(faces.size() - 1)->getMaxY();
  }

  if (faces.at(faces.size() - 1)->getMaxZ() > maxZ)
  {
    maxZ = faces.at(faces.size() - 1)->getMaxZ();
  }

  if (faces.at(faces.size() - 1)->getMinX() < minX)
  {
    minX = faces.at(faces.size() - 1)->getMinX();
  }

  if (faces.at(faces.size() - 1)->getMinY() < minY)
  {
    minY = faces.at(faces.size() - 1)->getMinY();
  }

  if (faces.at(faces.size() - 1)->getMinZ() < minZ)
  {
    minZ = faces.at(faces.size() - 1)->getMinZ();
  }

  //std::cout << name << " " << maxY << " " << minY << std::endl;

  offsetX = (minX + maxX) / 2;
  offsetY = (minY + maxY) / 2;
  offsetZ = (minZ + maxZ) / 2;

  needsResend = true;
}

void Part::draw()
{
  if(needsResend == true)
  {
    needsResend = false;
    resend();
  }

  glTranslatef(offsetX, offsetY, offsetZ);
  // Do animation translation  
  translate(1);
  glTranslatef(-offsetX, -offsetY, -offsetZ);

  for(int mgIndex = 0; mgIndex < materialGroups.size(); mgIndex++)
  {
    materialGroups.at(mgIndex)->draw(highlighted);
  }

  glTranslatef(offsetX, offsetY, offsetZ);

  if(attachedModel.get() != NULL)
  {
    attachedModel->draw();
  }

  // Undo animation translation
  translate(-1);
  glTranslatef(-offsetX, -offsetY, -offsetZ);
}

void Part::resend()
{
  MaterialGroup* materialGroup = NULL;
  Material* material = NULL;

  materialGroups.clear();

  for (int index = 0; index < faces.size(); index++)
  {
    material = faces.at(index)->getMaterial();

    if(material == NULL)
    {
      throw WavefrontException("The specified material is NULL");
    }

    materialGroup = NULL;

    for(int mgIndex = 0; mgIndex < materialGroups.size(); mgIndex++)
    {
      if(materialGroups.at(mgIndex)->getMaterial() == material)
      {
        materialGroup = materialGroups.at(mgIndex);
        break;
      }
    }

    if(materialGroup == NULL)
    {
      materialGroups.add(new MaterialGroup());
      materialGroup = materialGroups.at(materialGroups.size() - 1);
    }

    materialGroup->addFace(faces.at(index));
  }

  for(int mgIndex = 0; mgIndex < materialGroups.size(); mgIndex++)
  {
    materialGroups.at(mgIndex)->resend();
  }
}

void Part::translate(int undo)
{
  auto_vector<Animation>* animations = model->getAnimations();
  Frame* frame = NULL;
  Translation* translation = NULL;

  for (int animationIndex = 0; animationIndex < animations->size(); animationIndex++)
  {
    if(animations->at(animationIndex)->getEnabled() == false)
    {
      continue;
    }
    
    frame = animations->at(animationIndex)->getMergeFrame();
    translation = frame->getTranslation(this);

    if (translation != NULL)
    {
      if (undo == -1)
      {
        glRotatef(undo * translation->getXRotation(), 1, 0, 0);
        glRotatef(undo * translation->getYRotation(), 0, 1, 0);
        glRotatef(undo * translation->getZRotation(), 0, 0, 1);
      }

      glTranslatef(undo * translation->getX(), undo * translation->getY(), undo * translation->getZ());

      if (undo == 1)
      {
        glRotatef(undo * translation->getZRotation(), 0, 0, 1);
        glRotatef(undo * translation->getYRotation(), 0, 1, 0);
        glRotatef(undo * translation->getXRotation(), 1, 0, 0);
      }
    }
  }
}

void Part::setHighlighted(bool highlighted)
{
  this->highlighted = highlighted;
}

void Part::getCollidingFaces(Vertex* center, Vertex* halfsize, std::vector<Face*>* collidingFaces)
{
  for(int i = 0; i < faces.size(); i++)
  {
    if(faces.at(i)->isColliding(center, halfsize) == 1)
    {
      collidingFaces->push_back(faces.at(i));
    }
  }
}

Vertex Part::getSize()
{
  return Vertex(maxX - minX, maxY - minY, maxZ - minZ);
}

}

