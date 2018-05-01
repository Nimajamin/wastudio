#include <wavefront.h>

using namespace std;

namespace Wavefront
{

Animation::Animation(Model* model)
{
  frames.add(new Frame(this));
  name = "Default";
  frame = 0;
  enabled = false;
  repeating = true;
  mergeFrame.reset(new Frame(this));
}

Animation::Animation(Model* model, string path)
{
  ifstream file(path.c_str());
  string line;
  vector<string> parameters;
  auto_vector<Part>* parts = model->getParts();
  bool found = false;
  mergeFrame.reset(new Frame(this));

  this->model = model;
  name = "";
  frame = 0;
  enabled = false;
  repeating = true;

  if (file.is_open() == false)
  {
    throw WavefrontException("Failed to open animation file '" + path + "'");
  }

  while (file.eof() == false)
  {
    getline(file, line);
    splitString(line, ' ', &parameters);

    if (parameters.size() > 0)
    {
      if (parameters.at(0) == "n")
      {
        name = parameters.at(1);
      }

      if (parameters.at(0) == "f")
      {
        frames.add(new Frame(this));
      }

      if (parameters.at(0) == "t")
      {
        found = false;
	float scale = model->getScale();

        for(int partIndex = 0; partIndex < parts->size(); partIndex++)
        {
          Part* cp = parts->at(partIndex);
          Vertex v;
          v.x = cp->getSize().x * (atof(parameters.at(2).c_str()) / 100.0f);
          v.y = cp->getSize().y * (atof(parameters.at(3).c_str()) / 100.0f);
          v.z = cp->getSize().z * (atof(parameters.at(4).c_str()) / 100.0f);

          if(parts->at(partIndex)->getName() == parameters.at(1))
          {
            frames.at(frames.size() - 1)->getTranslations()->add(new Translation(parts->at(partIndex),
                                                                                 v.x*scale,
                                                                                 v.y*scale,
                                                                                 v.z*scale,
                                                                                 atof(parameters.at(5).c_str()),
                                                                                 atof(parameters.at(6).c_str()),
                                                                                 atof(parameters.at(7).c_str())));
            found = true;
          }
        }

        if(found == false)
        {
          throw WavefrontException("Failed to bind animation because the model does not contain '" + parameters.at(1) + "'");
        }
      }
    }
  }
}

Animation::~Animation()
{

}

void Animation::setRepeating(bool repeating)
{
  this->repeating = repeating;
}

void Animation::setEnabled(bool enabled)
{
  if (this->enabled != enabled)
  {
    frame = 0;
    this->enabled = enabled;
  }
}

bool Animation::getEnabled()
{
  return enabled;
}

string Animation::getName()
{
  return name;
}

void Animation::setName(string name)
{
  this->name = name;
}

void Animation::splitString(string input, char splitter, vector<string>* output)
{
  string current;

  output->clear();

  for (int charIndex = 0; charIndex < input.length(); charIndex++)
  {
    if (input[charIndex] != splitter)
    {
      current += input[charIndex];
    }
    else
    {
      output->push_back(current);
      current = "";
    }
  }

  if (current.length() > 0)
  {
    output->push_back(current);
  }
}

void Animation::generateMergeFrame(Frame* a, Frame* b, double weight)
{
  Frame::copy(a, mergeFrame.get());
  Frame::merge(b, mergeFrame.get(), weight);
}

Frame* Animation::getMergeFrame()
{
  double nearestFrame = (int)frame;
  double weight = frame - nearestFrame;

  if(frame >= frames.size() || frame + 1 >= frames.size())
  {
    generateMergeFrame(frames.at(frames.size() - 1), frames.at(0), weight);
  }
  else
  {
    generateMergeFrame(frames.at(frame), frames.at(frame + 1), weight);
  }

  return mergeFrame.get();
}

Frame* Animation::getFrame()
{
  if(frame < frames.size())
  {
    return frames.at(frame);
  }
  else
  {
    return frames.at(frames.size() - 1);
  }
}

void Animation::nextFrame()
{
  if(enabled == false)
  {
    return;
  }
  
  frame+= 0.1f;

  if(frame >= frames.size())
  {
    if(repeating == true)
    {
      frame = 0;
    }
    else
    {
      enabled = false;
      frame = 0;
    }
  }
}

int Animation::getCurrentFrame()
{
  return frame;
}

int Animation::getMaxFrames()
{
  return frames.size();
}

void Animation::setCurrentFrame(int currentFrame)
{
  this->frame = currentFrame;
}

void Animation::save(string path)
{
  Frame* frame = NULL;
  Translation* translation = NULL;
  ofstream file(path.c_str());

  if(file.is_open() == false)
  {
    throw WavefrontException("Failed to open '" + path + "' for saving");
  }

  file << "n " << name << endl;

  for(int frameIndex = 0; frameIndex < frames.size(); frameIndex++)
  {
    frame = frames.at(frameIndex);
    file << "f" << endl;

    for(int translationIndex = 0; translationIndex < frame->getTranslations()->size(); translationIndex++)
    {
      translation = frame->getTranslations()->at(translationIndex);
      file << "t " << translation->getPart()->getName() << " " << translation->getRelativeX() << " " << translation->getRelativeY() << " " << translation->getRelativeZ() << " " << translation->getXRotation() << " " << translation->getYRotation() << " " << translation->getZRotation() << endl;
    }
  }
}

auto_vector<Frame>* Animation::getFrames()
{
  return &frames;
}

}

