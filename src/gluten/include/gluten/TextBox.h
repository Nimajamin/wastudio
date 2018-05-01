namespace Gluten
{
  class TextBox;
}

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <gluten/Component.h>
#include <gluten/Panel.h>

using namespace std;

namespace Gluten
{
  class TextBox : public Component
  {
  private:

  public:
    TextBox(Panel* panel);
    ~TextBox();

    void keyTyped(char key);
    void draw();
  };
}

#endif

