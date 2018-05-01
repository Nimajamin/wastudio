#include "TutorialWindow.h"

TutorialWindow::TutorialWindow(Core* core) : Gluten::Window(core)
{
  current = 0;
  //color->setRGBA(0, 0, 0, 175);
  color.setRGB(255, 255, 255);
  centerPanel = new Panel(this);
  centerPanel->setPosition(0, 0);
  centerPanel->setSize(800, 600);
  centerPanel->setBorder(false);

  picture = new PictureBox(centerPanel);
  picture->setPosition(0, 0);
  picture->setSize(800, 600);
  picture->setPicture(Path::getPath() + "/share/wastudio/tutorial/tutorial_0.png");

  closeButton = new Button(centerPanel);
  closeButton->setPosition(560, 570);
  closeButton->setSize(75, 25);
  closeButton->setText("Close");
  closeButton->setLeftMouseButtonClickFunction(new GenericFunction<TutorialWindow>(this, &TutorialWindow::onCloseButtonClicked));

  nextButton = new Button(centerPanel);
  nextButton->setPosition(720, 570);
  nextButton->setSize(75, 25);
  nextButton->setText("Next");
  nextButton->setLeftMouseButtonClickFunction(new GenericFunction<TutorialWindow>(this, &TutorialWindow::onNextButtonClicked));

  backButton = new Button(centerPanel);
  backButton->setPosition(640, 570);
  backButton->setSize(75, 25);
  backButton->setText("Back");
  backButton->setLeftMouseButtonClickFunction(new GenericFunction<TutorialWindow>(this, &TutorialWindow::onBackButtonClicked));

}

TutorialWindow::~TutorialWindow()
{

}

void TutorialWindow::onCloseButtonClicked()
{
  close();
}

void TutorialWindow::onNextButtonClicked()
{
  std::stringstream ss;

  try
  {
    current++;
    ss << Path::getPath() << "/share/wastudio/tutorial/tutorial_";
    ss << current;
    ss << ".png";
    picture->setPicture(ss.str());
  }
  catch(exception& e)
  {
    current--;
  }
}

void TutorialWindow::onBackButtonClicked()
{
  std::stringstream ss;

  try
  {
    current--;
    ss << Path::getPath() << "/share/wastudio/tutorial/tutorial_";
    ss << current;
    ss << ".png";
    picture->setPicture(ss.str());
  }
  catch(exception& e)
  {
    current++;
  }
}

