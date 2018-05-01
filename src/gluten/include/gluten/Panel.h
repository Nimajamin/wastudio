namespace Gluten
{
  class Panel;
}

#ifndef PANEL_H
#define PANEL_H

#include <memory>
#include <vector>

#include <gluten/Window.h>
#include <gluten/Color.h>
#include <gluten/Rectangle.h>
#include <gluten/Component.h>
#include <gluten/Mouse.h>
#include <gluten/Color.h>

using namespace std;

namespace Gluten
{
  class Panel
  {
  private:
    Window* window;
    vector<Component*> components;
    auto_ptr<Rectangle> rectangle;
    Color backgroundColor;
    Color borderColor;
    int x;
    int y;
    bool border;

  public:
    Panel(Window* window);
    ~Panel();

    vector<Component*>* getComponents();
    Rectangle* getRectangle();
    void setPosition(int x, int y);
    void setSize(int width, int height);
    void draw();
    void update();
    void mouseButtonClick(int x, int y, int button);
    void mouseMove(int x, int y, Mouse* mouse);
    void mouseUp(int x, int y, int button, Mouse* mouse);
    void mouseDown(int x, int y, int button, Mouse* mouse);
    Color& getBackgroundColor();
    void setBorder(bool border);
    void keyTyped(char key);

  };
}

#endif

