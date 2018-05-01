#include <gluten/Mouse.h>

namespace Gluten
{
Mouse::Mouse()
{
  x = 0;
  y = 0;
  offsetX = 0;
  offsetY = 0;
  button1 = false;
  previousButton1 = false;
  button2 = false;
  button3 = false;
  scrollUp = false;
  scrollDown = false;
}

Mouse::~Mouse()
{

}

int Mouse::getOffsetX()
{
  int temp = offsetX;
  offsetX = 0;

  return temp;
}

int Mouse::getOffsetY()
{
  int temp = offsetY;
  offsetY = 0;

  return temp;
}

int Mouse::getX()
{
  return x;
}

void Mouse::setX(int x)
{
  offsetX = x - this->x;
  this->x = x;
}

int Mouse::getY()
{
  return y;
}

void Mouse::setY(int y)
{
  offsetY = y - this->y;
  this->y = y;
}

bool Mouse::getButton1()
{
  return button1;
}

void Mouse::setButton1(bool button1)
{
  this->previousButton1 = this->button1;
  this->button1 = button1;
}

bool Mouse::getButton3()
{
  return button3;
}

void Mouse::setButton3(bool button3)
{
  this->button3 = button3;
}

bool Mouse::getButton2()
{
  return button2;
}

void Mouse::setButton2(bool button2)
{
  this->button2 = button2;
}

bool Mouse::getScrollUp()
{
  bool temp = scrollUp;
  scrollUp = false;

  return temp;
}

void Mouse::setScrollUp(bool scrollUp)
{
  this->scrollUp = scrollUp;
}

bool Mouse::getScrollDown()
{
  bool temp = scrollDown;
  scrollDown = false;

  return temp;
}

void Mouse::setScrollDown(bool scrollDown)
{
  this->scrollDown = scrollDown;
}

bool Mouse::isMouseDown()
{
  if(button1)
  {
    return true;
  }
  return button1;
}

bool Mouse::isMouseClicked()
{
  //if(button1 == false && previousButton1 == true)
  if(button1 == true && previousButton1 == false)
  {
    previousButton1 = button1;
    return true;
  }
  return false;
}
}

