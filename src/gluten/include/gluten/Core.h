#ifndef CORE_H
#define CORE_H

#include <vector>
#include <memory>
#include <iostream>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

using namespace std;

namespace Gluten
{
  class Window;
  class Mouse;

  class Core
  {
  private:
    static Core* core;

    static void display();
    static void idle();
    static void reshape(int width, int height);
    static void motion(int x, int y);
    static void mouseFunc(int button, int state, int x, int y);
    static void update();
    static void keyboardUp(unsigned char key, int x, int y);
    static void keyboard(unsigned char key, int x, int y);

  protected:
    std::shared_ptr<Mouse> mouse;
    vector<Window*> windows;
    int width;
    int height;
    bool keystates[512];
    bool controlPressed;
    bool shiftPressed;
    bool eventDriven;
    int eventCount;

  public:
    static Core* getCore();

    Core(int argc, char* argv[]);
    ~Core();
    void run();
    vector<Window*>* getWindows();
    Mouse* getMouse();
    int getWidth();
    void setWidth(int width);
    int getHeight();
    void setHeight(int height);
    void setTitle(string title);
    void setSize(int width, int height);
    void add(Window* window);
    bool getControlPressed();
    bool getShiftPressed();
    bool isKeyPressed(unsigned char key);
    void setEventDriven(bool eventDriven);
    void processEvent();

  };
}

#endif
