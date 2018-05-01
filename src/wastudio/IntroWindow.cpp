#include "IntroWindow.h"

IntroWindow::IntroWindow(Core* core) : Gluten::Window(core)
{
  state = 0;
  color.setRGB(255, 255, 255);
  centerPanel = new Panel(this);
  centerPanel->setPosition(0, 0);
  centerPanel->setSize(200, 200);
  centerPanel->setBorder(false);

  glutenLogo = new PictureBox(centerPanel);
  glutenLogo->setPosition(0, 0);
  glutenLogo->setSize(200, 200);
  glutenLogo->getBackgroundColor().setRGBA(200, 200, 200, 200);
  glutenLogo->setPicture(Path::getPath() + "/share/wastudio/data/gluten_logo.png");
}

IntroWindow::~IntroWindow()
{

}

void IntroWindow::control()
{
  if(core->getMouse()->isMouseClicked() == true)
  {
    if(state == 0)
    {
      glutenLogo->setPicture(Path::getPath() + "/share/wastudio/data/wavefront_logo.png");
    }
    else if(state == 1)
    {
      core->add(new TestWindow(core));
      close();
    }

    state++;
  }
}

