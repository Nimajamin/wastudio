class TutorialWindow;

#ifndef TUTORIALWINDOW_H
#define TUTORIALWINDOW_H

#include <sstream>

#include <gluten.h>

using namespace Gluten;

class TutorialWindow : public Gluten::Window
{
private:
  Panel* centerPanel;
  Button* closeButton;
  Button* nextButton;
  Button* backButton;
  PictureBox* picture;

  int current;

public:
  TutorialWindow(Core* core);
  ~TutorialWindow();

  void onCloseButtonClicked();
  void onNextButtonClicked();
  void onBackButtonClicked();

};

#endif

