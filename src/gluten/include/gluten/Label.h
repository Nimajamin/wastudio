namespace Gluten
{
  class Label;
}

#ifndef LABEL_H
#define LABEL_H

#include <gluten/Component.h>
#include <gluten/Panel.h>

using namespace std;

namespace Gluten
{
  class Label : public Component
  {
  private:

  public:
    Label(Panel* panel);
    ~Label();

    void draw();
  };
}

#endif

