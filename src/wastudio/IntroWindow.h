class IntroWindow;

#ifndef INTROWINDOW_H
#define INTROWINDOW_H

#include <gluten.h>

#include "TestWindow.h"

using namespace Gluten;

class IntroWindow : public Gluten::Window
{
private:
  Panel* centerPanel;
  PictureBox* glutenLogo;
  int state;

public:
  IntroWindow(Core* core);
  ~IntroWindow();

  void control();

};

#endif

