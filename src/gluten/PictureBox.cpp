#include <gluten/PictureBox.h>

namespace Gluten
{
  PictureBox::PictureBox(Panel* panel) : Component(panel)
  {
    backgroundColor.setR(255);
    backgroundColor.setG(255);
    backgroundColor.setB(255);
    backgroundColor.setA(255);
  }

  PictureBox::~PictureBox()
  {

  }

  void PictureBox::setPicture(string path)
  {
    image = std::make_shared<Image>(path);
  }

  void PictureBox::draw()
  {
    /*color->enable();
    glBegin(GL_QUADS);
    glVertex2f(rectangle->getX(), rectangle->getY());
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY());
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX(), rectangle->getY() + rectangle->getHeight());
    glEnd();

    backgroundColor.enable();
    glColor4f(0, 0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(rectangle->getX() + 1, rectangle->getY() + 1);
    glVertex2f(rectangle->getX() + rectangle->getWidth() - 1, rectangle->getY() + 1);
    glVertex2f(rectangle->getX() + rectangle->getWidth() - 1, rectangle->getY() + rectangle->getHeight() - 1);
    glVertex2f(rectangle->getX() + 1, rectangle->getY() + rectangle->getHeight() - 1);
    glEnd();*/

    if(image.get() != NULL)
    {
      image->draw((rectangle->getWidth() / 2) - (image->getWidth() / 2) + rectangle->getX(), (rectangle->getHeight() / 2) - (image->getHeight() / 2) + rectangle->getY());
      //image->draw(rectangle->getX(), rectangle->getY());
    }
    //image->draw(300, 300, 40, 40, 55, 25);
  }
}

