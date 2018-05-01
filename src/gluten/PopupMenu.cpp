#include <gluten/PopupMenu.h>

#include <gluten/Function.h>

namespace Gluten
{
PopupMenu::PopupMenu(Core* core, int x, int y) : Window(core)
{
  color.setRGBA(0, 0, 0, 100);
  panel = new Panel(this);
  panel->setPosition(x, y);
  panel->setSize(0, 0);
  core->add(this);
}

PopupMenu::~PopupMenu()
{
  
}

void PopupMenu::control()
{
  bool inX = false;
  bool inY = false;
  int mouseX = core->getMouse()->getX();
  int mouseY = core->getMouse()->getY();

  if(core->getMouse()->getButton1() == false)
  {
    return;
  }

  if(mouseX >= panel->getRectangle()->getX() && mouseX <= panel->getRectangle()->getX() + panel->getRectangle()->getWidth())
  {
    inX = true;
  }

  if(mouseY >= panel->getRectangle()->getY() && mouseY <= panel->getRectangle()->getY() + panel->getRectangle()->getHeight())
  {
    inY = true;
  }

  if(inX == true && inY == true)
  {
    return;
  }

  close();
}

void PopupMenu::addItem(string name, Function* function)
{
  buttons.push_back(new Button(panel));
  callbacks.add(function);
  buttons.at(buttons.size() - 1)->setPosition(0, (buttons.size()-1) * 25);
  buttons.at(buttons.size() - 1)->setSize(75, 25);
  buttons.at(buttons.size() - 1)->setText(name);
  buttons.at(buttons.size() - 1)->setLeftMouseButtonClickFunction(new ParameterFunction<PopupMenu>(this, &PopupMenu::onMenuItemClicked, buttons.at(buttons.size() - 1)));
  panel->setSize(75, buttons.size() * 25);
}

void PopupMenu::onMenuItemClicked(void* caller)
{
  Button* button = (Button*) caller;

  for(int buttonIndex = 0; buttonIndex < buttons.size(); buttonIndex++)
  {
    if(button == buttons.at(buttonIndex))
    {
      callbacks.at(buttonIndex)->execute();
    }
  }

  close();
}
}
