#include <gluten/HScroll.h>

#include <gluten/Color.h>
#include <gluten/Rectangle.h>

namespace Gluten
{
  HScroll::HScroll(Panel* panel) : Component(panel)
  {
    current = 0;
    max = 10;
    dragging = false;
    arrowColor = Color(100, 100, 100, 255);
  }

  HScroll::~HScroll()
  {

  }

  void HScroll::draw()
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
    glVertex2f(rectangle->getX(), rectangle->getY() + (rectangle->getHeight() / 2) - 2);
    glVertex2f(rectangle->getX(), rectangle->getY() + (rectangle->getHeight() / 2) + 2);
    glVertex2f(rectangle->getX() + rectangle->getWidth()+1, rectangle->getY() + (rectangle->getHeight() / 2) + 2);
    glVertex2f(rectangle->getX() + rectangle->getWidth()+1, rectangle->getY() + (rectangle->getHeight() / 2) - 2);
    glEnd();

    if(max > 1)
    {
    for(int index = 0; index < max; index++)
    {
      glBegin(GL_QUADS);
      glVertex2f(rectangle->getX() + (((float)rectangle->getWidth() / ((float)max-1)) * (float)index), rectangle->getY() + (rectangle->getHeight() / 2) - 10);
      glVertex2f(rectangle->getX() + (((float)rectangle->getWidth() / ((float)max-1)) * (float)index), rectangle->getY() + (rectangle->getHeight() / 2));
      glVertex2f(rectangle->getX() + (((float)rectangle->getWidth() / ((float)max-1)) * (float)index)+1, rectangle->getY() + (rectangle->getHeight() / 2));
      glVertex2f(rectangle->getX() + (((float)rectangle->getWidth() / ((float)max-1)) * (float)index)+1, rectangle->getY() + (rectangle->getHeight() / 2) - 10);
      glEnd();
    }

    arrowColor.enable();
    glBegin(GL_TRIANGLES);
    glVertex2f(rectangle->getX() - 10 + (((float)rectangle->getWidth() / ((float)max-1)) * (float)current), rectangle->getY() + (rectangle->getHeight() / 2) - 20);
    glVertex2f(rectangle->getX() + 10 + (((float)rectangle->getWidth() / ((float)max-1)) * (float)current), rectangle->getY() + (rectangle->getHeight() / 2) - 20);
    glVertex2f(rectangle->getX() + (((float)rectangle->getWidth() / ((float)max-1)) * (float)current), rectangle->getY() + (rectangle->getHeight() / 2) - 2);
    glEnd();
    }
  }

  void HScroll::setMax(int max)
  {
    if(max <= current)
    {
      current = max - 1;
    }

    this->max = max;
  }

  void HScroll::setCurrent(int current)
  {
    this->current = current;
  }

  int HScroll::getCurrent()
  {
    return current;
  }

  void HScroll::mouseDown(int x, int y, int button, Mouse* mouse)
  {
    dragging = true;

    changeScroll(x, y);
    Component::mouseDown(x, y, button, mouse);
  }

  void HScroll::mouseUp(int x, int y, int button, Mouse* mouse)
  {
    dragging = false;

    Component::mouseUp(x, y, button, mouse);
  }

  void HScroll::mouseMove(int x, int y, Mouse* mouse)
  {
    if(dragging == true)
    {
      changeScroll(x, y);
    }

    Component::mouseMove(x, y, mouse);
  }

  void HScroll::changeScroll(int x, int y)
  {
    int halfStep = 0;

    if(max > 1)
    {
      halfStep = (rectangle->getWidth() / (max-1)) / 2;
      current = ((float)(max-1) / (float)rectangle->getWidth()) * ((float)x+(float)halfStep);
    }
  }
}

