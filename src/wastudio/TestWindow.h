class TestWindow;

#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <gluten.h>

#include "ModelWindow.h"
#include "AboutWindow.h"
#include "TutorialWindow.h"

#include <memory>

using namespace Gluten;

class TestWindow : public Gluten::Window
{
private:
  Panel* centerPanel;
  Button* openModelButton;
  Button* tutorialButton;
  ImageButton* closeImageButton;
  ImageButton* preferencesImageButton;
  PictureBox* pictureBox;
  Label* openModelLabel;
  Label* tutorialLabel;
  OpenFileDialog* openFileDialog;
  std::shared_ptr<Gluten::Image> background;

public:
  TestWindow(Core* core);
  ~TestWindow();

  void onCloseButtonClicked();
  void onPreferencesButtonClicked();
  void onOpenModelButtonClicked();
  void onTutorialButtonClicked();
  void onModelSelected();
  void display();

};

#endif

