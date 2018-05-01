namespace Gluten
{
  class MessageBox;
}

#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <gluten/Window.h>

using namespace std;

namespace Gluten
{
  class Window;
  class Panel;
  class Button;
  class Label;
  class Function;

  class MessageBox : public Window
  {
  private:
    auto_ptr<Function> okButtonClickFunction;
    Panel* centerPanel;
    Button* okButton;
    Label* label;

  protected:

  public:
    MessageBox(Core* core, string message);
    virtual ~MessageBox();

    void onOkButtonClicked();

  };
}

#endif

