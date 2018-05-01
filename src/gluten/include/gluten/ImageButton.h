namespace Gluten
{
  class ImageButton;
}

#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <memory>
#include <string>

#include <gluten/Component.h>
#include <gluten/Image.h>
#include <gluten/Panel.h>

using namespace std;

namespace Gluten
{
  class ImageButton : public Component
  {
  private:
    auto_ptr<Image> image;

  public:
    ImageButton(Panel* panel, string imagePath);
    ~ImageButton();

    void draw();
  };
}

#endif

