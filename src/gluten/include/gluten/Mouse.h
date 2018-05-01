namespace Gluten
{
  class Mouse;
}

#ifndef MOUSE_H
#define MOUSE_H

namespace Gluten
{
  class Mouse
  {
  private:
    int x;
    int y;
    int offsetX;
    int offsetY;
    bool button1;
    bool previousButton1;
    bool button2;
    bool button3;
    bool scrollUp;
    bool scrollDown;

  public:
    Mouse();
    ~Mouse();

    int getX();
    void setX(int x);

    int getY();
    void setY(int y);

    int getOffsetX();
    int getOffsetY();

    bool getButton1();
    void setButton1(bool button1);

    bool getButton2();
    void setButton2(bool button2);

    bool getButton3();
    void setButton3(bool button3);

    bool getScrollUp();
    void setScrollUp(bool scrollUp);

    bool getScrollDown();
    void setScrollDown(bool scrollDown);

    bool isMouseClicked();
    bool isMouseDown();
  };
}

#endif

