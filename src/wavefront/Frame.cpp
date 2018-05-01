#include <wavefront.h>

namespace Wavefront
{

void Frame::copy(Frame* source, Frame* destination)
{
  Translation* translation = NULL;
  destination->getTranslations()->clear();

  for(int translationIndex = 0; translationIndex < source->getTranslations()->size(); translationIndex++)
  {
    translation = source->getTranslations()->at(translationIndex);
    destination->getTranslations()->add(new Translation(translation->getPart(), translation->getX(), translation->getY(), translation->getZ(), translation->getXRotation(), translation->getYRotation(), translation->getZRotation()));
  }
}

void Frame::merge(Frame* source, Frame* destination, double weight)
{
  Translation* translation = NULL;
  Translation* to = NULL;

  for(int translationIndex = 0; translationIndex < source->getTranslations()->size(); translationIndex++)
  {
    to = NULL;
    translation = source->getTranslations()->at(translationIndex);

    for(int toIndex = 0; toIndex < destination->getTranslations()->size(); toIndex++)
    {
      if(translation->getPart() == destination->getTranslations()->at(toIndex)->getPart())
      {
        to = destination->getTranslations()->at(toIndex);
      }
    }

    if(to == NULL)
    {
      destination->getTranslations()->add(new Translation(translation->getPart(), 0, 0, 0, 0, 0, 0));
      to = destination->getTranslations()->at(destination->getTranslations()->size() - 1);
    }

    float dX = translation->getX() - to->getX();
    float dY = translation->getY() - to->getY();
    float dZ = translation->getZ() - to->getZ();

    float dRX = translation->getXRotation() - to->getXRotation();
    float dRY = translation->getYRotation() - to->getYRotation();
    float dRZ = translation->getZRotation() - to->getZRotation();

    to->setX(to->getX() + dX * weight);
    to->setY(to->getY() + dY * weight);
    to->setZ(to->getZ() + dZ * weight);

    to->setXRotation(to->getXRotation() + dRX * weight);
    to->setYRotation(to->getYRotation() + dRY * weight);
    to->setZRotation(to->getZRotation() + dRZ * weight);
  }
}

Frame::Frame(Animation* animation)
{
  this->animation = animation;
}

auto_vector<Translation>* Frame::getTranslations()
{
  return &translations;
}

Translation* Frame::getTranslation(Part* part, bool add)
{
  for(int translationIndex = 0; translationIndex < translations.size(); translationIndex++)
  {
    if(translations.at(translationIndex)->getPart() == part)
    {
      return translations.at(translationIndex);
    }
  }

  if(add == true)
  {
    translations.add(new Translation(part, 0, 0, 0, 0, 0, 0));

    return translations.at(translations.size() - 1);
  }

  return NULL;
}
}
