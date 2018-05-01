#ifndef COMPONENT_H
#define COMPONENT_H

#include "Color.h"

#include <string>
#include <memory>

using namespace std;

namespace Gluten
{
  class Panel;
  class Rectangle;
  class Function;
  class Mouse;
  class Font;

  class Component
  {
  private:

  protected:
    Panel* panel;
    Color color;
    Color backgroundColor;
    Color borderColor;
    auto_ptr<Rectangle> rectangle;
    auto_ptr<Font> font;
    string text;
    bool border;
    bool visible;
    bool mouseOver;
    bool mouse1Down;
    int mouse1DoubleClickTimeout;
    auto_ptr<Function> leftMouseButtonClickFunction;
    auto_ptr<Function> leftMouseButtonDoubleClickFunction;
    int textAlignment;
    int lastClickX;
    int lastClickY;

  public:
    Component(Panel* panel);
    virtual ~Component();

    void setPosition(int x, int y);
    void setSize(int width, int height);
    Rectangle* getRectangle();
    void setMouseOver(bool mouseOver);
    Color& getBackgroundColor();
    Color& getColor();
    void setText(string text);
    string getText();
    void setLeftMouseButtonClickFunction(Function* function);
    void setLeftMouseButtonDoubleClickFunction(Function* function);
    void setTextAlignment(int textAlignment);
    Font* getFont();

    virtual void mouseMove(int x, int y, Mouse* mouse);
    virtual void mouseClick(int x, int y, int button, Mouse* mouse);
    virtual void mouseDoubleClick(int x, int y, int button, Mouse* mouse);
    virtual void mouseUp(int x, int y, int button, Mouse* mouse);
    virtual void mouseDown(int x, int y, int button, Mouse* mouse);
    virtual void draw();
    virtual void update();
    virtual void keyTyped(char key);

  };
}

#endif

