class AboutWindow;

#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <gluten.h>

using namespace Gluten;

class AboutWindow : public Gluten::Window
{
private:
  Panel* centerPanel;
  Button* closeButton;
  PictureBox* logoPicture;
  Label* studioLabel;
  Label* studioVersionLabel;
  Label* glutenVersionLabel;
  Label* wavefrontVersionLabel;

  Label* copyrightLabel;

public:
  AboutWindow(Core* core);
  ~AboutWindow();

  void onCloseButtonClicked();

};

#endif

