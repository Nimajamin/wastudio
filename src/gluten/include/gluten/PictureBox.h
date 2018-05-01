namespace Gluten
{
  class PictureBox;
}

#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <string>
#include <memory>

#include <gluten/Component.h>
#include <gluten/Image.h>
#include <gluten/Panel.h>

using namespace std;

namespace Gluten
{
  class PictureBox : public Component
  {
  private:

  protected:
    std::shared_ptr<Image> image;

  public:
    PictureBox(Panel* panel);
    ~PictureBox();

    void setPicture(string path);
    void draw();
  };
}

#endif

