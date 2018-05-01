#ifndef WAVEFRONT_FRAME_H
#define	WAVEFRONT_FRAME_H

#include <wavefront/auto_vector.h>

namespace Wavefront
{

class Animation;
class Translation;
class Part;

class Frame
{
private:
  Animation* animation;
  auto_vector<Translation> translations;

public:
  static void copy(Frame* source, Frame* destination);
  static void merge(Frame* source, Frame* destination, double weight = 0.5f);

  Frame(Animation* animation);

  auto_vector<Translation>* getTranslations();
  Translation* getTranslation(Part* part, bool add = false);

};

}

#endif
