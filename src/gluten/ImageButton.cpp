#include <gluten/ImageButton.h>

namespace Gluten
{
  ImageButton::ImageButton(Panel* panel, string imagePath) : Component(panel)
  {
    image.reset(new Image(imagePath));
  }

  ImageButton::~ImageButton()
  {

  }

  void ImageButton::draw()
  {
    if(mouse1Down == true)
    {
      color.enableDark();
    }
    else if(mouseOver == true)
    {
      color.enableLight();
    }
    else
    {
      color.enable();
    }

    glBegin(GL_QUADS);
    glVertex2f(rectangle->getX(), rectangle->getY());
    glVertex2f(rectangle->getX(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY());
    glEnd();

    image->draw(rectangle->getX() + (rectangle->getWidth() / 2) - (image->getWidth() / 2), rectangle->getY() + (rectangle->getHeight() / 2) - (image->getHeight() / 2));
  }
}

