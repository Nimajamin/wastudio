namespace Gluten
{
  class Window;
}

#ifndef WINDOW_H
#define WINDOW_H

#include <gluten/Core.h>
#include <gluten/Panel.h>
#include <gluten/Mouse.h>
#include <gluten/Color.h>

using namespace std;

namespace Gluten
{
  class Window
  {
  private:

  protected:
    Core* core;
    std::vector<std::shared_ptr<Panel> > panels;
    Color color;
    bool closing;

  public:
    Window(Core* core);
    virtual ~Window();

    Core* getCore();
    std::vector<std::shared_ptr<Panel> >* getPanels();
    void draw();
    void updateComponents();
    void close();
    bool isClosing();

    virtual void control();
    virtual void update();
    virtual void display();

    void mouseMove(int x, int y, Mouse* mouse);
    void mouseDown(int x, int y, int button, Mouse* mouse);
    void mouseUp(int x, int y, int button, Mouse* mouse);
    void mouseScroll(int x, int y, int direction, Mouse* mouse);
    void keyTyped(char key);
  };
}

#endif

