#ifndef HSCROLL_H
#define HSCROLL_H

#include <memory>

#include <gluten/Component.h>

using namespace std;

namespace Gluten
{
  class Panel;
  class Color;
  class Component;

  class HScroll : public Component
  {
  private:
    int max;
    int current;
    bool dragging;
    Color arrowColor;

  public:
    HScroll(Panel* panel);
    ~HScroll();

    void draw();
    void setMax(int max);
    void setCurrent(int current);
    int getCurrent();

    virtual void mouseDown(int x, int y, int button, Mouse* mouse);
    virtual void mouseUp(int x, int y, int button, Mouse* mouse);
    virtual void mouseMove(int x, int y, Mouse* mouse);

    void changeScroll(int x, int y);
  };
}

#endif

