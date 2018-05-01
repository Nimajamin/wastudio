namespace Gluten
{
  class Rectangle;
}

#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace Gluten
{
  class Rectangle
  {
  private:
    int x;
    int y;
    int width;
    int height;

  public:
    Rectangle();
    Rectangle(int x, int y);
    Rectangle(int x, int y, int width, int height);
    virtual ~Rectangle();

    void setX(int x);
    int getX();

    void setY(int y);
    int getY();

    void setWidth(int width);
    int getWidth();

    void setHeight(int height);
    int getHeight();

    bool intersect(int x, int y);
  };
}

#endif

