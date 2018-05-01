#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

namespace Gluten
{
  class Color
  {
  private:
    int r;
    int g;
    int b;
    int a;

  public:
    static Color getDefault();
    static Color getDefaultBackground();
    static Color getDefaultBorder();
    static Color getDefaultSelect();

    Color();
    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);
    ~Color();

    void setR(int r);
    int getR();

    void setG(int g);
    int getG();

    void setB(int b);
    int getB();

    void setA(int a);
    int getA();

    void setRGB(int r, int g, int b);
    void setRGBA(int r, int g, int b, int a);

    void enable();
    void enableLight();
    void enableDark();
  };
}

#endif

