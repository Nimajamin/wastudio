#include <gluten/Core.h>

#include <gluten/Window.h>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <unistd.h>
#endif

namespace Gluten
{
  Core* Core::core = NULL;

  void Core::display()
  {
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int windowIndex = 0; windowIndex < core->getWindows()->size(); windowIndex++)
    {
      glLoadIdentity();
      core->getWindows()->at(windowIndex)->display();
    }

    //glTranslatef(0, 0, -5);
    //glutSolidCube(0.5);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, core->getWidth(), 0, core->getHeight());
    glScalef(1, -1, 1);
    glTranslatef(0, -core->getHeight(), 0);
    glMatrixMode(GL_MODELVIEW);

    for(int windowIndex = 0; windowIndex < core->getWindows()->size(); windowIndex++)
    {
      glLoadIdentity();
      core->getWindows()->at(windowIndex)->draw();
    }

    //glBegin(GL_QUADS);
    //glVertex2f(125, 125);
    //glVertex2f(125, 375);
    //glVertex2f(375, 375);
    //glVertex2f(375, 125);
    //glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    //for(int windowIndex = 0; windowIndex < core->getWindows()->size(); windowIndex++)
    //{
    //  glLoadIdentity();
    //  core->getWindows()->at(windowIndex)->display();
    //}

    glutSwapBuffers();
  }

  void Core::add(Window* window)
  {
    windows.push_back(window);
  }

  void Core::update()
  {
    for(int windowIndex = 0; windowIndex < core->getWindows()->size(); windowIndex++)
    {
      if(core->getWindows()->at(windowIndex)->isClosing() == true)
      {
        delete core->getWindows()->at(windowIndex);
        core->getWindows()->erase(core->getWindows()->begin() + windowIndex);
      }
    }

    if(core->getWindows()->size() < 1)
    {
      exit(0);
    }

    for(int windowIndex = 0; windowIndex < core->getWindows()->size(); windowIndex++)
    {
      core->getWindows()->at(windowIndex)->control();
      core->getWindows()->at(windowIndex)->updateComponents();
      core->getWindows()->at(windowIndex)->update();
    }
  }

  bool Core::isKeyPressed(unsigned char key)
  {
    return keystates[key];
  }

  void Core::keyboardUp(unsigned char key, int x, int y)
  {
    core->keystates[key] = false;
    //glutPostRedisplay();
    core->processEvent();
  }

  void Core::keyboard(unsigned char key, int x, int y)
  {
    core->keystates[key] = true;

    for(int windowIndex = 0; windowIndex < core->getWindows()->size(); windowIndex++)
    {
      core->getWindows()->at(windowIndex)->keyTyped(key);
    }
    //glutPostRedisplay();
    core->processEvent();
  }

  void Core::idle()
  {
    // FPS Limiter
  // The static variable to store the previous time snapshot
  static int last = 0;

  int current = 0;
  int difference = 0;

  // The minimum time each frame should take (in milliseconds)
  int target = 1000 / 30;

  // Used to obtain the time (in milliseconds) from the start of the application
  current = glutGet(GLUT_ELAPSED_TIME);

  // Find out how many milliseconds have passed in one game loop
  difference = current - last;

  // If this loop was faster than the minimum, sleep the rest of the time
  if(difference < target)
  {
#ifdef _WIN32
    // x 1000 because there is 1000000 microseconds in 1 second
    Sleep((target - difference));
#else
    // x 1000 because there is 1000000 microseconds in 1 second
    usleep((target - difference) * 1000);
#endif
  }

  // Set the new last time snapshot to be used next loop
  last = glutGet(GLUT_ELAPSED_TIME);
    // FPS Limiter

    update();

    if(core->eventDriven == true || core->eventCount > 0)
    {
      glutPostRedisplay();
      core->eventCount--;
    }
  }

  void Core::setEventDriven(bool eventDriven)
  {
    this->eventDriven = eventDriven;
  }

  void Core::mouseFunc(int button, int state, int x, int y)
  {
    Mouse* mouse = core->getMouse();

    if(glutGetModifiers() == GLUT_ACTIVE_CTRL)
    {
      core->controlPressed = true;
    }

    if(button == 0)
    {
      if(state == 0)
      {
        mouse->setButton1(true);
        core->getWindows()->at(core->getWindows()->size() - 1)->mouseDown(mouse->getX(), mouse->getY(), 1, mouse);
      }
      else
      {
        mouse->setButton1(false);
        core->getWindows()->at(core->getWindows()->size() - 1)->mouseUp(mouse->getX(), mouse->getY(), 1, mouse);
      }
    }

    if(button == 1)
    {
      if(state == 0)
      {
        mouse->setButton2(true);
        core->getWindows()->at(core->getWindows()->size() - 1)->mouseDown(mouse->getX(), mouse->getY(), 2, mouse);
      }
      else
      {
        mouse->setButton2(false);
        core->getWindows()->at(core->getWindows()->size() - 1)->mouseUp(mouse->getX(), mouse->getY(), 2, mouse);
      }
    }

    if(button == 2)
    {
      if(state == 0)
      {
        mouse->setButton3(true);
        core->getWindows()->at(core->getWindows()->size() - 1)->mouseDown(mouse->getX(), mouse->getY(), 3, mouse);
      }
      else
      {
        mouse->setButton3(false);
        core->getWindows()->at(core->getWindows()->size() - 1)->mouseUp(mouse->getX(), mouse->getY(), 3, mouse);
      }
    }

    if(button == 3)
    {
      if(state == 0)
      {
        mouse->setScrollUp(true);
        core->getWindows()->at(core->getWindows()->size() - 1)->mouseScroll(mouse->getX(), mouse->getY(), 0, mouse);
      }
      else
      {
        //mouse->setScrollUp(false);
      }
    }

    if(button == 4)
    {
      if(state == 0)
      {
        mouse->setScrollDown(true);
        core->getWindows()->at(core->getWindows()->size() - 1)->mouseScroll(mouse->getX(), mouse->getY(), 1, mouse);
      }
      else
      {
        //mouse->setScrollDown(false);
      }
    }

    core->controlPressed = false;
    core->shiftPressed = false;
    //glutPostRedisplay();
    core->processEvent();
  }

  void Core::motion(int x, int y)
  {
    Mouse* mouse = NULL;

    if(core->getWindows()->size() < 1)
    {
      return;
    }

    mouse = core->getMouse();
    mouse->setX(x);
    mouse->setY(y);

    core->getWindows()->at(core->getWindows()->size() - 1)->mouseMove(mouse->getX(), mouse->getY(), mouse);
    //glutPostRedisplay();
    core->processEvent();
  }

  void Core::reshape(int width, int height)
  {
    core->setWidth(width);
    core->setHeight(height);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    //glutPostRedisplay();
    core->processEvent();
  }

  void Core::processEvent()
  {
    //glutPostRedisplay();
    eventCount = 1;
  }

  Core::Core(int argc, char* argv[])
  {
    eventCount = 0;
    eventDriven = false;
    controlPressed = false;
    shiftPressed = false;
    core = this;
    mouse.reset(new Mouse());
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(320, 240);
    glutInitWindowPosition(100, 100);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutCreateWindow("Glut");

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(motion);
    glutMotionFunc(motion);
    glutMouseFunc(mouseFunc);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    //glutSpecialFunc(special);

    for(int keyIndex = 0; keyIndex < 512; keyIndex++)
    {
      keystates[keyIndex] = false;
    }
  }

  Core::~Core()
  {
    while(windows.size() > 0)
    {
      delete windows.at(0);
      windows.erase(windows.begin() + 0);
    }
  }

  void Core::run()
  {
    //glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glCullFace(GL_FRONT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutMainLoop();
  }

  bool Core::getControlPressed()
  {
    return controlPressed;
  }

  bool Core::getShiftPressed()
  {
    return shiftPressed;
  }

  vector<Window*>* Core::getWindows()
  {
    return &windows;
  }

  Mouse* Core::getMouse()
  {
    return mouse.get();
  }

  int Core::getWidth()
  {
    return width;
  }

  void Core::setWidth(int width)
  {
    this->width = width;
  }

  int Core::getHeight()
  {
    return height;
  }

  void Core::setHeight(int height)
  {
    this->height = height;
  }

  void Core::setTitle(string title)
  {
    glutSetWindowTitle(title.c_str());
  }

  void Core::setSize(int width, int height)
  {
    glutReshapeWindow(width, height);
  }

  Core* Core::getCore()
  {
    return core;
  }
}

