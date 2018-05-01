#include "TestWindow.h"

TestWindow::TestWindow(Core* core) : Gluten::Window(core)
{
  openFileDialog = NULL;
  //color->setRGB(150, 150, 150);
  //color->setRGB(0, 148, 131);
  //color->setRGB(40, 58, 151);
  //color.setRGB(9, 86, 155);
  color.setA(0);
  centerPanel = new Panel(this);
  centerPanel->setPosition(0, 0);
  centerPanel->setSize(566, 404);
  centerPanel->getBackgroundColor().setA(0);
  centerPanel->setBorder(false);

  background = std::make_shared<Gluten::Image>(Path::getPath() + "/share/wastudio/data/noise.png");

  pictureBox = new PictureBox(centerPanel);
  pictureBox->getBackgroundColor().setR(255);
  pictureBox->getBackgroundColor().setG(0);
  pictureBox->getBackgroundColor().setB(0);
  pictureBox->getBackgroundColor().setA(0);
  pictureBox->setPosition(0, 0);
  pictureBox->setSize(566, 404);
  pictureBox->setPicture(Path::getPath() + "/share/wastudio/data/menu_panel.png");

  openModelButton = new Button(centerPanel);
  openModelButton->setPosition(80, 190);
  openModelButton->setSize(150, 40);
  openModelButton->setText("Open Model");
  openModelButton->setLeftMouseButtonClickFunction(new GenericFunction<TestWindow > (this, &TestWindow::onOpenModelButtonClicked));

  openModelLabel = new Label(centerPanel);
  openModelLabel->setPosition(250, 190);
  openModelLabel->setSize(150, 40);
  openModelLabel->setText("Open a model for animating");
  openModelLabel->setTextAlignment(0);

  tutorialButton = new Button(centerPanel);
  tutorialButton->setPosition(80, 240);
  tutorialButton->setSize(150, 40);
  tutorialButton->setText("Tutorial");
  tutorialButton->setLeftMouseButtonClickFunction(new GenericFunction<TestWindow > (this, &TestWindow::onTutorialButtonClicked));

  tutorialLabel = new Label(centerPanel);
  tutorialLabel->setPosition(250, 240);
  tutorialLabel->setSize(150, 40);
  tutorialLabel->setText("Learn how to use this software");
  tutorialLabel->setTextAlignment(0);

  closeImageButton = new ImageButton(centerPanel, Path::getPath() + "/share/wastudio/data/exit.png");
  closeImageButton->setPosition(450, 325);
  closeImageButton->setSize(32, 32);
  closeImageButton->setLeftMouseButtonClickFunction(new GenericFunction<TestWindow > (this, &TestWindow::onCloseButtonClicked));

  preferencesImageButton = new ImageButton(centerPanel, Path::getPath() + "/share/wastudio/data/preferences.png");
  preferencesImageButton->setPosition(410, 325);
  preferencesImageButton->setSize(32, 32);
  preferencesImageButton->setLeftMouseButtonClickFunction(new GenericFunction<TestWindow > (this, &TestWindow::onPreferencesButtonClicked));
}

TestWindow::~TestWindow()
{

}

void TestWindow::onCloseButtonClicked()
{
  close();
}

void TestWindow::onPreferencesButtonClicked()
{
  core->add(new AboutWindow(core));
}

void TestWindow::onTutorialButtonClicked()
{
  core->add(new TutorialWindow(core));
}

void TestWindow::onOpenModelButtonClicked()
{
  try
  {
    openFileDialog = new OpenFileDialog(core);
    openFileDialog->setFiletype(".obj");
    openFileDialog->getPictureBox()->setPicture(Path::getPath() + "/share/wastudio/data/fade_pattern.png");
    openFileDialog->setOpenButtonClickFunction(new GenericFunction<TestWindow > (this, &TestWindow::onModelSelected));
  }
  catch (Exception& e)
  {
    cout << "Exception: " << e.what() << endl;

    if(openFileDialog != NULL)
    {
      openFileDialog->close();
    }
  }
}

void TestWindow::onModelSelected()
{
  try
  {
    core->add(new ModelWindow(core, openFileDialog->getSelectedPath()));
    close();
  }
  catch (exception& e)
  {
    cout << "Exception: " << e.what() << endl;
  }
}

void TestWindow::display()
{
  glClearColor(0.9,0.9,0.9,1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// orth
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, core->getWidth(), core->getHeight(), 0);
    glMatrixMode(GL_MODELVIEW);

    for(size_t y = 0; y < core->getHeight(); y+= background->getHeight())
    {
      for(size_t x = 0; x < core->getWidth(); x+= background->getWidth())
      {
        background->draw(x, y);
      }
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
// endorth
}
