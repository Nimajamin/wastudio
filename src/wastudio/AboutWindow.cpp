#include <wavefront.h>

#include "AboutWindow.h"

AboutWindow::AboutWindow(Core* core) : Gluten::Window(core)
{
  color.setRGBA(0, 0, 0, 175);
  centerPanel = new Panel(this);
  centerPanel->setPosition(0, 0);
  centerPanel->setSize(300, 375);

  logoPicture = new PictureBox(centerPanel);
  logoPicture->setPosition(0, 10);
  logoPicture->setSize(300, 350);
  logoPicture->setPicture(Path::getPath() + "/share/wastudio/data/wavefront_logo_small.png");

  closeButton = new Button(centerPanel);
  closeButton->setPosition(200, 255);
  closeButton->setSize(75, 25);
  closeButton->setText("Close");
  closeButton->setLeftMouseButtonClickFunction(new GenericFunction<AboutWindow>(this, &AboutWindow::onCloseButtonClicked));

  studioLabel = new Label(centerPanel);
  studioLabel->setText("Wavefront Animation Studio");
  studioLabel->setPosition(20, 100);
  studioLabel->setSize(100, 25);
  studioLabel->setTextAlignment(0);

  studioVersionLabel = new Label(centerPanel);
  studioVersionLabel->setText("Version: " + std::string(VERSION));
  studioVersionLabel->setPosition(20, 150);
  studioVersionLabel->setSize(100, 25);
  studioVersionLabel->setTextAlignment(0);

  copyrightLabel = new Label(centerPanel);
  copyrightLabel->setText("Copyright 2012 Sanguine Labs");
  copyrightLabel->setPosition(20, 125);
  copyrightLabel->setSize(100, 25);
  copyrightLabel->setTextAlignment(0);

  //glutenVersionLabel = new Label(centerPanel);
  //glutenVersionLabel->setText("Gluten Version: INTERNAL");
  //glutenVersionLabel->setPosition(20, 150);
  //glutenVersionLabel->setSize(100, 25);
  //glutenVersionLabel->setTextAlignment(0);

  wavefrontVersionLabel = new Label(centerPanel);
  wavefrontVersionLabel->setText("Wavefront Version: " + Wavefront::Model::getWavefrontVersion());
  wavefrontVersionLabel->setPosition(20, 175);
  wavefrontVersionLabel->setSize(100, 25);
  wavefrontVersionLabel->setTextAlignment(0);

  //copyrightLabel = new Label(centerPanel);
  //copyrightLabel->setPosition(10, 80);
  //copyrightLabel->setSize(100, 25);
  //copyrightLabel->setText("by Karsten Pedersen");
  //copyrightLabel->setTextAlignment(0);
}

AboutWindow::~AboutWindow()
{

}

void AboutWindow::onCloseButtonClicked()
{
  close();
}

