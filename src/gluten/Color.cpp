#include <gluten/Color.h>

namespace Gluten
{
  Color Color::getDefault()
  {
    return Color(9, 86, 155, 255);
  }

  Color Color::getDefaultBackground()
  {
    return Color(255, 255, 255, 255);
  }

  Color Color::getDefaultBorder()
  {
    return Color(9, 86, 155, 255);
  }

  Color Color::getDefaultSelect()
  {
    return Color(175, 175, 175, 255);
  }

  Color::Color()
  {
    r = 0;
    g = 0;
    b = 0;
    a = 0;
  }

  Color::Color(int r, int g, int b)
  {
    this->r = r;
    this->g = g;
    this->b = b;
    a = 0;
  }

  Color::Color(int r, int g, int b, int a)
  {
    this->r = r; 
    this->g = g;
    this->b = b;
    this->a = a;
  }

  Color::~Color()
  {

  }

  void Color::setR(int r)
  {
    this->r = r;
  }

  int Color::getR()
  {
    return r;
  }

  void Color::setG(int g) 
  {
    this->g = g;
  }

  int Color::getG() 
  {
    return g;
  }

  void Color::setB(int b) 
  {
    this->b = b;
  }

  int Color::getB() 
  {
    return b;
  }

  void Color::setA(int a) 
  {
    this->a = a;
  }

  int Color::getA() 
  {
    return a;
  }

  void Color::enable()
  {
    float r = this->r;
    float g = this->g;
    float b = this->b;
    float a = this->a;

    glColor4f(r / 255, g / 255, b / 255, a / 255);
  }

  void Color::enableLight()
  {
    float r = this->r + 25;
    float g = this->g + 25;
    float b = this->b + 25;
    float a = this->a;

    glColor4f(r / 255, g / 255, b / 255, a / 255);
  }

  void Color::enableDark()
  {
    float r = this->r - 25;
    float g = this->g - 25;
    float b = this->b - 25;
    float a = this->a;

    glColor4f(r / 255, g / 255, b / 255, a / 255);
  }

  void Color::setRGBA(int r, int g, int b, int a)
  {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }

  void Color::setRGB(int r, int g, int b)
  {
    this->r = r;
    this->g = g;
    this->b = b;
  }
}

