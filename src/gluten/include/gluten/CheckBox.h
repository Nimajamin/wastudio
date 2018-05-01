#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <gluten/Component.h>
#include <gluten/Color.h>

using namespace std;

namespace Gluten
{
  class Panel;
  class Component;

  class CheckBox : public Component
  {
  private:
    bool checked;
    Color selectedColor;

  public:
    CheckBox(Panel* panel);
    ~CheckBox();

    void draw();
    void mouseClick(int x, int y, int button, Mouse* mouse);
  };
}

#endif

