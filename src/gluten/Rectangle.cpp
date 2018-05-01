#include <gluten/Rectangle.h>

namespace Gluten
{
  Rectangle::Rectangle()
  {
    x = 0;
    y = 0;
    width = 0;
    height = 0;
  }

  Rectangle::Rectangle(int x, int y)
  {
    this->x = x;
    this->y = y;
    this->width = 0;
    this->height = 0;
  }

  Rectangle::Rectangle(int x, int y, int width, int height)
  {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
  }

  Rectangle::~Rectangle(){}

  void Rectangle::setX(int x)
  {
    this->x = x;
  }

  int Rectangle::getX()
  {
    return x;
  }

  void Rectangle::setY(int y) 
  {
    this->y = y;
  }

  int Rectangle::getY() 
  {
    return y;
  }

  void Rectangle::setWidth(int width) 
  {
    this->width = width;
  }

  int Rectangle::getWidth() 
  {
    return width;
  }

  void Rectangle::setHeight(int height) 
  {
    this->height = height;
  }

  int Rectangle::getHeight() 
  {
    return height;
  }

  bool Rectangle::intersect(int x, int y)
  {
    bool xIntersect = false;
    bool yIntersect = false;

    if(x >= this->x && x <= this->x + this->width)
    {
      xIntersect = true;
    }

    if(y >= this->y && y <= this->y + this->height)
    {
      yIntersect = true;
    }

    if(xIntersect == true && yIntersect == true)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

