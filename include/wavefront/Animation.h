#ifndef WAVEFRONT_ANIMATION_H
#define	WAVEFRONT_ANIMATION_H

#include <string>
#include <wavefront/auto_vector.h>

namespace Wavefront
{

class Model;
class Frame;

class Animation
{
private:
  Model* model;
  std::string name;
  double frame;
  bool enabled;
  bool repeating;
  auto_vector<Frame> frames;
  std::shared_ptr<Frame> mergeFrame;

  void splitString(std::string input, char splitter, std::vector<std::string>* output);
  void generateMergeFrame(Frame* a, Frame* b, double weight);

public:
  Animation(Model* model);
  Animation(Model* model, std::string path);
  ~Animation();

  void setRepeating(bool repeating);
  void setEnabled(bool enabled);
  bool getEnabled();
  std::string getName();
  void setName(std::string name);
  Frame* getFrame();
  Frame* getMergeFrame();
  auto_vector<Frame>* getFrames();
  int getCurrentFrame();
  int getMaxFrames();
  void nextFrame();
  void setCurrentFrame(int currentFrame);
  void save(std::string path);

};

}

#endif

