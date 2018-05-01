namespace Gluten
{
  class PopupMenu;
}

#ifndef POPUPMENU_H
#define POPUPMENU_H

#include <gluten/Window.h>
#include <gluten/Button.h>
#include <wavefront/auto_vector.h>

namespace Gluten
{
  class PopupMenu : public Window
  {
  private:
    Panel* panel;
    vector<string> names;
    Wavefront::auto_vector<Function> callbacks;
    vector<Button*> buttons;

  public:
    PopupMenu(Core* core, int x, int y);
    ~PopupMenu();

    virtual void control();

    void addItem(string name, Function* function);

    void onMenuItemClicked(void* caller);
    
  };
}

#endif
