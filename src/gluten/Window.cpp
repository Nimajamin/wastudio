#include <gluten/Window.h>

namespace Gluten
{
  Window::Window(Core* core)
  {
    this->core = core;
    //core->getWindows()->push_back(this);
    color = Color::getDefaultBackground();
    closing = false;
  }

  Window::~Window()
  {
    core->processEvent();
  }

  Core* Window::getCore()
  {
    return core;
  }

  std::vector<std::shared_ptr<Panel> >* Window::getPanels()
  {
    return &panels;
  }

  void Window::close()
  {
    closing = true;
    core->processEvent();
  }

  bool Window::isClosing()
  {
    return closing;
  }

  void Window::draw()
  {
    color.enable();
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(0, core->getHeight());
    glVertex2f(core->getWidth(), core->getHeight());
    glVertex2f(core->getWidth(), 0);
    glEnd();

    for(int panelIndex = 0; panelIndex < panels.size(); panelIndex++)
    {
      panels.at(panelIndex)->draw();
    }
  }

  void Window::updateComponents()
  {
    for(int panelIndex = 0; panelIndex < panels.size(); panelIndex++)
    {
      panels.at(panelIndex)->update();
    }
  }

  void Window::control()
  {

  }

  void Window::update()
  {

  }

  void Window::display()
  {

  }

  void Window::mouseMove(int x, int y, Mouse* mouse)
  {
    for(int panelIndex = 0; panelIndex < panels.size(); panelIndex++)
    {
      std::shared_ptr<Panel> panel = panels.at(panelIndex);

      if(panel->getRectangle()->intersect(x, y) == true)
      {
        panel->mouseMove(x - panel->getRectangle()->getX(), y - panel->getRectangle()->getY(), mouse);
      }
    }
  }

  void Window::mouseDown(int x, int y, int button, Mouse* mouse)
  {
    for(int panelIndex = 0; panelIndex < panels.size(); panelIndex++)
    {
      std::shared_ptr<Panel> panel = panels.at(panelIndex);

      if(panel->getRectangle()->intersect(x, y) == true)
      {
        panel->mouseDown(x - panel->getRectangle()->getX(), y - panel->getRectangle()->getY(), button, mouse);
      }
    }
  }

  void Window::mouseUp(int x, int y, int button, Mouse* mouse)
  {
    for(int panelIndex = 0; panelIndex < panels.size(); panelIndex++)
    {
      std::shared_ptr<Panel> panel = panels.at(panelIndex);

      if(panel->getRectangle()->intersect(x, y) == true)
      {
        panel->mouseUp(x - panel->getRectangle()->getX(), y - panel->getRectangle()->getY(), button, mouse);
      }
    }
  }

  void Window::mouseScroll(int x, int y, int direction, Mouse* mouse)
  {
    
  }

  void Window::keyTyped(char key)
  {
    for(int panelIndex = 0; panelIndex < panels.size(); panelIndex++)
    {
      panels.at(panelIndex)->keyTyped(key);
    }
  }
}

