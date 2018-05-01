#ifndef BUTTON_H
#define BUTTON_H

#include <gluten/Component.h>

using namespace std;

namespace Gluten
{
  class Panel;
  class Component;

  class Button : public Component
  {
  private:

  public:
    Button(Panel* panel);
    ~Button();

    void draw();
  };
}

#endif

