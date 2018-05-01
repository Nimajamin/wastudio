#include <gluten/Panel.h>

namespace Gluten
{
  Panel::Panel(Window* window)
  {
    x = 0;
    y = 0;
    this->window = window;
    window->getPanels()->push_back(std::shared_ptr<Panel>(this));
    backgroundColor = Color::getDefaultBackground();
    borderColor = Color::getDefaultBorder();
    rectangle.reset(new Rectangle());
    border = true;
  }

  Panel::~Panel()
  {
    while(components.size() > 0)
    {
      delete components.at(0);
      components.erase(components.begin() + 0);
    }
  }

  vector<Component*>* Panel::getComponents()
  {
    return &components;
  }

  Rectangle* Panel::getRectangle()
  {
    return rectangle.get();
  }

  void Panel::setPosition(int x, int y)
  {
    this->x = x;
    this->y = y;
    rectangle->setX(x);
    rectangle->setY(y);
  }

  void Panel::setSize(int width, int height)
  {
    rectangle->setWidth(width);
    rectangle->setHeight(height);
  }

  void Panel::draw()
  {
    rectangle->setX(x);
    rectangle->setY(y);

    if(x < 0)
    {
      rectangle->setX(window->getCore()->getWidth() - (rectangle->getX() * -1) - rectangle->getWidth());
    }

    if(y < 0)
    {
      rectangle->setY(window->getCore()->getHeight() - (rectangle->getY() * -1) - rectangle->getHeight());
    }

    if(x == 0)
    {
      rectangle->setX((window->getCore()->getWidth() / 2) - (rectangle->getWidth() / 2));
    }

    if(y == 0)
    {
      rectangle->setY((window->getCore()->getHeight() / 2) - (rectangle->getHeight() / 2));
    }

    glPushMatrix();
    glTranslatef(rectangle->getX(), rectangle->getY(), 0);
    backgroundColor.enable();

    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(0, rectangle->getHeight());
    glVertex2f(rectangle->getWidth(), rectangle->getHeight());
    glVertex2f(rectangle->getWidth(), 0);
    glEnd();

    for(int componentIndex = 0; componentIndex < components.size(); componentIndex++)
    {
      components.at(componentIndex)->draw();
    }

    if(border == true)
    {
      borderColor.enable();
      glBegin(GL_LINE_LOOP);
      glVertex2f(0, 0);
      glVertex2f(0, rectangle->getHeight());
      glVertex2f(rectangle->getWidth(), rectangle->getHeight());
      glVertex2f(rectangle->getWidth(), 0);
      glEnd();
    }

    glPopMatrix();
  }

  void Panel::update()
  {
    for(int componentIndex = 0; componentIndex < components.size(); componentIndex++)
    {
      components.at(componentIndex)->update();
    }
  }

  void Panel::mouseButtonClick(int x, int y, int button)
  {

  }

  void Panel::mouseMove(int x, int y, Mouse* mouse)
  {
    Component* component = NULL;

    for(int componentIndex = 0; componentIndex < components.size(); componentIndex++)
    {
      component = components.at(componentIndex); 

      if(component->getRectangle()->intersect(x, y) == true)
      {
        component->mouseMove(x - component->getRectangle()->getX(), y - component->getRectangle()->getY(), mouse);
      }
      else
      {
        component->setMouseOver(false);
      }
    }
  }

  void Panel::mouseDown(int x, int y, int button, Mouse* mouse)
  {
    Component* component = NULL;

    for(int componentIndex = 0; componentIndex < components.size(); componentIndex++)
    {
      component = components.at(componentIndex);

      if(component->getRectangle()->intersect(x, y) == true)
      {
        component->mouseDown(x - component->getRectangle()->getX(), y - component->getRectangle()->getY(), button,  mouse);
      }
      else
      {
        component->setMouseOver(false);
      }
    }
  }

  void Panel::mouseUp(int x, int y, int button, Mouse* mouse)
  {
    Component* component = NULL;

    for(int componentIndex = 0; componentIndex < components.size(); componentIndex++)
    {
      component = components.at(componentIndex);

      if(component->getRectangle()->intersect(x, y) == true)
      {
        component->mouseUp(x - component->getRectangle()->getX(), y - component->getRectangle()->getY(), button,  mouse);
      }
      else
      {
        component->setMouseOver(false);
      }
    }
  }

  Color& Panel::getBackgroundColor()
  {
    return backgroundColor;
  }

  void Panel::setBorder(bool border)
  {
    this->border = border;
  }

  void Panel::keyTyped(char key)
  {
    Component* component = NULL;

    for(int componentIndex = 0; componentIndex < components.size(); componentIndex++)
    {
      component = components.at(componentIndex);
      component->keyTyped(key);
    }
  }
}

