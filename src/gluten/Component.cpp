#include <gluten/Component.h>

#include <gluten/Rectangle.h>
#include <gluten/Font.h>
#include <gluten/Panel.h>
#include <gluten/Function.h>

namespace Gluten
{
  Component::Component(Panel* panel)
  {
    this->panel = panel;
    panel->getComponents()->push_back(this);
    color = Color::getDefault();
    backgroundColor = Color::getDefaultBackground();
    borderColor = Color::getDefaultBorder();
    rectangle.reset(new Rectangle());
    mouseOver = false;
    mouse1Down = false;
    mouse1DoubleClickTimeout = 0;
    textAlignment = 1;
    lastClickX = 0;
    lastClickY = 0;
  }

  Component::~Component()
  {

  }

  void Component::setLeftMouseButtonClickFunction(Function* function)
  {
    this->leftMouseButtonClickFunction.reset(function);
  }

  void Component::setLeftMouseButtonDoubleClickFunction(Function* function)
  {
    this->leftMouseButtonDoubleClickFunction.reset(function);
  }

  void Component::setPosition(int x, int y)
  {
    rectangle->setX(x);
    rectangle->setY(y);
  }

  void Component::setSize(int width, int height)
  {
    rectangle->setWidth(width);
    rectangle->setHeight(height);
  }

  void Component::setTextAlignment(int textAlignment)
  {
    this->textAlignment = textAlignment;
  }

  Rectangle* Component::getRectangle()
  {
    return rectangle.get();
  }

  Color& Component::getBackgroundColor()
  {
    return backgroundColor;
  }

  Color& Component::getColor()
  {
    return color;
  }

  void Component::setMouseOver(bool mouseOver)
  {
    this->mouseOver = mouseOver;

    if(this->mouseOver == false)
    {
      mouse1Down = false;
    }
  }

  void Component::mouseMove(int x, int y, Mouse* mouse)
  {
    setMouseOver(true);
  }

  void Component::mouseDoubleClick(int x, int y, int button, Mouse* mouse)
  {
    if(leftMouseButtonDoubleClickFunction.get() != NULL)
    {
      leftMouseButtonDoubleClickFunction->execute();
    }
  }

  void Component::mouseClick(int x, int y, int button, Mouse* mouse)
  {
    if(mouse1DoubleClickTimeout > 0 && x == lastClickX && y == lastClickY)
    {
      mouseDoubleClick(x, y, button, mouse);
      mouse1DoubleClickTimeout = 0;
    }
    else
    {
      mouse1DoubleClickTimeout = 20;
    }

    if(leftMouseButtonClickFunction.get() != NULL)
    {
      leftMouseButtonClickFunction->execute();
    }

    lastClickX = x;
    lastClickY = y;
  }

  void Component::mouseUp(int x, int y, int button, Mouse* mouse)
  {
    if(button == 1)
    {
      if(mouse1Down == true)
      {
        mouseClick(x, y, button, mouse);
      }

      mouse1Down = false;
    }
  }

  void Component::mouseDown(int x, int y, int button, Mouse* mouse)
  {
    if(button == 1)
    {
      mouse1Down = true;
    }
  }

  void Component::keyTyped(char key)
  {

  }

  void Component::draw()
  {

  }

  void Component::update()
  {
    if(mouse1DoubleClickTimeout > 0)
    {
      mouse1DoubleClickTimeout--;
    }
  }

  void Component::setText(string text)
  {
    this->text = text;
  }

  Font* Component::getFont()
  {
    return font.get();
  }

  string Component::getText()
  {
    return text;
  }
}
