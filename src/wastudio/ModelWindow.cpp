#include "ModelWindow.h"

ModelWindow::ModelWindow(Core* core, string path) : Gluten::Window(core)
{
  modelPath = path;
  playing = false;
  color.setA(0);
  state = 0;

  watermarkImage.reset(new Image(Path::getPath() + "/share/wastudio/data/watermark.png"));
  moveXYImage.reset(new Image(Path::getPath() + "/share/wastudio/data/movexy.png"));
  moveZImage.reset(new Image(Path::getPath() + "/share/wastudio/data/movez.png"));
  rotateXYImage.reset(new Image(Path::getPath() + "/share/wastudio/data/rotatexy.png"));
  rotateZImage.reset(new Image(Path::getPath() + "/share/wastudio/data/rotatez.png"));

  framePanel = new Panel(this);
  framePanel->setPosition(0, -1);
  framePanel->setSize(640, 50);
  framePanel->getBackgroundColor().setA(0);
  //framePanel->getBackgroundColor().setRGBA(50, 50, 50, 50);
  framePanel->setBorder(false);

  //pictureBox = new PictureBox(framePanel);
  //pictureBox->getBackgroundColor().setR(255);
  //pictureBox->getBackgroundColor().setG(0);
  //pictureBox->getBackgroundColor().setB(0);
  //pictureBox->getBackgroundColor().setA(0);
  //pictureBox->setPosition(0, 0);
  //pictureBox->setSize(640, 75);
  //pictureBox->setPicture("share/wastudio/data/hscroll.png");

  frameHScroll = new HScroll(framePanel);
  frameHScroll->setPosition(0, 0);
  frameHScroll->setSize(640, 50);

  informationPanel = new Panel(this);
  informationPanel->setPosition(2, 31);
  informationPanel->setSize(200, 200);
  informationPanel->getBackgroundColor().setA(100);

  informationLabel = new Label(informationPanel);
  informationLabel->setTextAlignment(0);
  informationLabel->setPosition(0, 0);
  informationLabel->setSize(200, 25);
  informationLabel->getBackgroundColor().setRGBA(9, 86, 155, 255);
  informationLabel->getFont()->setColor(Color(255, 255, 255, 255));
  informationLabel->setText(" Information");

  modelFilenameLabel = new Label(informationPanel);
  modelFilenameLabel->setTextAlignment(0);
  modelFilenameLabel->setPosition(10, 30);
  modelFilenameLabel->setSize(75, 25);
  modelFilenameLabel->getBackgroundColor().setA(0);

  animationFilenameLabel = new Label(informationPanel);
  animationFilenameLabel->setTextAlignment(0);
  animationFilenameLabel->setPosition(10, 80);
  animationFilenameLabel->setSize(75, 25);
  animationFilenameLabel->getBackgroundColor().setA(0);

  animationNameLabel = new Label(informationPanel);
  animationNameLabel->setTextAlignment(0);
  animationNameLabel->setPosition(10, 55);
  animationNameLabel->setSize(75, 25);
  animationNameLabel->getBackgroundColor().setA(0);

  animationFrameLabel = new Label(informationPanel);
  animationFrameLabel->setTextAlignment(0);
  animationFrameLabel->setPosition(10, 105);
  animationFrameLabel->setSize(75, 25);
  animationFrameLabel->getBackgroundColor().setA(0);

#ifdef TRIAL_YES
  demoLabel = new Label(informationPanel);
  demoLabel->setTextAlignment(0);
  demoLabel->setPosition(10, 175);
  demoLabel->setSize(75, 25);
  demoLabel->getBackgroundColor().setA(0);
  demoLabel->setText("Trial Version");
  demoLabel->getFont()->setColor(Color(255, 0, 0, 255));
#endif

  partsPanel = new Panel(this);
  partsPanel->setPosition(-2, 31);
  partsPanel->setSize(200, 300);
  partsPanel->getBackgroundColor().setA(100);

  partsListBox = new ListBox(partsPanel);
  partsListBox->setPosition(0, 0);
  partsListBox->setSize(200, 300);
  partsListBox->setText("Parts");
  partsListBox->setLeftMouseButtonClickFunction(new GenericFunction<ModelWindow > (this, &ModelWindow::onPartsListBoxClicked));

  menuPanel = new Panel(this);
  menuPanel->setPosition(0, 3);
  menuPanel->setSize(400, 25);
  menuPanel->getBackgroundColor().setRGB(9, 86, 155);

  fileButton = new Button(menuPanel);
  fileButton->setPosition(0, 0);
  fileButton->setSize(75, 25);
  fileButton->setText("File");
  fileButton->setLeftMouseButtonClickFunction(new GenericFunction<ModelWindow > (this, &ModelWindow::onFileButtonClicked));

  animationButton = new Button(menuPanel);
  animationButton->setPosition(75, 0);
  animationButton->setSize(75, 25);
  animationButton->setText("Animation");
  animationButton->setLeftMouseButtonClickFunction(new GenericFunction<ModelWindow > (this, &ModelWindow::onAnimationButtonClicked));

  modelButton = new Button(menuPanel);
  modelButton->setPosition(150, 0);
  modelButton->setSize(75, 25);
  modelButton->setText("Model");
  modelButton->setLeftMouseButtonClickFunction(new GenericFunction<ModelWindow > (this, &ModelWindow::onModelButtonClicked));

  helpButton = new Button(menuPanel);
  helpButton->setPosition(225, 0);
  helpButton->setSize(75, 25);
  helpButton->setText("Help");
  helpButton->setLeftMouseButtonClickFunction(new GenericFunction<ModelWindow > (this, &ModelWindow::onHelpButtonClicked));

  xRotation = 0;
  yRotation = 0;
  zoom = -10;

  model.reset(new Model(path));
  model->enableAnimation(0);

  for(int index = 0; index < model->getParts()->size(); index++)
  {
    partsListBox->getItems()->push_back(model->getParts()->at(index)->getName());
  }

  frameAdvancePanel = new Panel(this);
  frameAdvancePanel->setPosition(5, -5);
  frameAdvancePanel->setSize(96, 50);
  frameAdvancePanel->getBackgroundColor().setA(100);

  frameModPanel = new Panel(this);
  frameModPanel->setPosition(-5, -5);
  frameModPanel->setSize(96, 50);
  frameModPanel->getBackgroundColor().setA(100);

  addButton = new ImageButton(frameModPanel, Path::getPath() + "/share/wastudio/data/add.png");
  addButton->setSize(48, 48);
  addButton->setPosition(0, 0);
  addButton->setLeftMouseButtonClickFunction(new GenericFunction<ModelWindow > (this, &ModelWindow::onAddButtonClicked));

  interpolateButton = new ImageButton(frameModPanel, Path::getPath() + "/share/wastudio/data/interpolation.png");
  interpolateButton->setSize(48, 48);
  interpolateButton->setPosition(48, 0);
  interpolateButton->setLeftMouseButtonClickFunction(new GenericFunction<ModelWindow > (this, &ModelWindow::onInterpolateButtonClicked));

  removeButton = new ImageButton(frameAdvancePanel, Path::getPath() + "/share/wastudio/data/remove.png");
  removeButton->setSize(48, 48);
  removeButton->setPosition(48, 0);
  removeButton->getColor().setRGBA(155, 0, 0, 255);
  removeButton->setLeftMouseButtonClickFunction(new GenericFunction<ModelWindow > (this, &ModelWindow::onRemoveButtonClicked));

  playButton = new ImageButton(frameAdvancePanel, Path::getPath() + "/share/wastudio/data/play.png");
  playButton->setSize(48, 48);
  playButton->setPosition(0, 0);
  playButton->getColor().setRGBA(0, 155, 0, 255);
  playButton->setLeftMouseButtonClickFunction(new GenericFunction<ModelWindow > (this, &ModelWindow::onPlayButtonClicked));

  pauseButton = new ImageButton(frameAdvancePanel, Path::getPath() + "/share/wastudio/data/pause.png");
  pauseButton->setSize(48, 48);
  pauseButton->setPosition(-100, 0);
  pauseButton->setLeftMouseButtonClickFunction(new GenericFunction<ModelWindow > (this, &ModelWindow::onPlayButtonClicked));

  // NOTE: glFrontFace(GL_CCW)
}

ModelWindow::~ModelWindow()
{

}

void ModelWindow::display()
{
  glClearColor(0.9,0.9,0.9,1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// orth
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    //gluOrtho2D(0, core->getWidth(), 0, core->getHeight());
    gluOrtho2D(0, core->getWidth(), core->getHeight(), 0);
    //glScalef(1, -1, 1);
    //glTranslatef(0, -core->getHeight(), 0);
    glMatrixMode(GL_MODELVIEW);
 
    watermarkImage->draw((core->getWidth() / 2) - (watermarkImage->getWidth() / 2), (core->getHeight() / 2) - (watermarkImage->getHeight() / 2));   

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
// endorth

  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  glPushMatrix();
  glTranslatef(0, 0, zoom);
  glRotatef(xRotation, 1, 0, 0);
  glRotatef(yRotation, 0, 1, 0);
  //glutSolidCube(0.5);
  model->draw();
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);

// orth
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, core->getWidth(), 0, core->getHeight());
    glScalef(1, -1, 1);
    glTranslatef(0, -core->getHeight(), 0);
    glMatrixMode(GL_MODELVIEW);

    if(state == 1)
    {
      moveXYImage->draw(core->getMouse()->getX(), core->getMouse()->getY());
    }

    if(state == 2)
    {
      moveZImage->draw(core->getMouse()->getX(), core->getMouse()->getY());
    }

    if(state == 3)
    {
      rotateXYImage->draw(core->getMouse()->getX(), core->getMouse()->getY());
    }

    if(state == 4)
    {
      rotateZImage->draw(core->getMouse()->getX(), core->getMouse()->getY());
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
// endorth
}

void ModelWindow::update()
{
  menuPanel->setSize(core->getWidth() - 4, 25);
  framePanel->setSize(core->getWidth() - 225, 50);
  frameHScroll->setSize(core->getWidth() - 225, 50);

  frameHScroll->setMax(model->getAnimations()->at(0)->getMaxFrames());

  if(playing == true)
  {
    model->update();
    frameHScroll->setCurrent(model->getAnimations()->at(0)->getCurrentFrame());
  }
  else
  {
    model->getAnimations()->at(0)->setCurrentFrame(frameHScroll->getCurrent());
  }

  updateInformationPanel();
}

void ModelWindow::control()
{
  Translation* translation = NULL;

  state = 0;

  if(core->getMouse()->getButton3() == true)
  {
    xRotation += core->getMouse()->getOffsetY() * 2;
    yRotation += core->getMouse()->getOffsetX() * 2;
  }

  if(core->getMouse()->getScrollUp() == true)
  {
    zoom+=0.5;
  }

  if(core->getMouse()->getScrollDown() == true)
  {
    zoom-=0.5;
  }

  while(yRotation < 0)
  {
    yRotation += 360;
  }

  while(yRotation >= 360)
  {
    yRotation -= 360;
  }

  if(core->getMouse()->getButton2() == true && partsListBox->getSelectedItem() != "")
  {
    // Front
    if((yRotation >= 0 && yRotation < 45) || (yRotation < 360 && yRotation > 360 - 45))
    {
      if(core->isKeyPressed('r') == true)
      {
        state = 4;
        translation = model->getAnimations()->at(0)->getFrame()->getTranslation(model->getPart(partsListBox->getSelectedItem()), true);
        translation->setXRotation(translation->getXRotation() + ((float)core->getMouse()->getOffsetY()));
        translation->setYRotation(translation->getYRotation() + ((float)core->getMouse()->getOffsetX()));
      }
      else
      {
        state = 2;
        translation = model->getAnimations()->at(0)->getFrame()->getTranslation(model->getPart(partsListBox->getSelectedItem()), true);
        translation->setX(translation->getX() - ((float)-core->getMouse()->getOffsetX() / (float)100));
        translation->setY(translation->getY() - ((float)core->getMouse()->getOffsetY() / (float)100));
      }
    }
    else if(yRotation > 45 && yRotation <= 45 + 90) // Left
    {
      if(core->isKeyPressed('r') == true)
      {
        state = 3;
        translation = model->getAnimations()->at(0)->getFrame()->getTranslation(model->getPart(partsListBox->getSelectedItem()), true);
        translation->setYRotation(translation->getYRotation() + ((float)core->getMouse()->getOffsetX()));
        translation->setZRotation(translation->getZRotation() + ((float)core->getMouse()->getOffsetY()));
      }
      else
      {
        state = 1;
        translation = model->getAnimations()->at(0)->getFrame()->getTranslation(model->getPart(partsListBox->getSelectedItem()), true);
        translation->setZ(translation->getZ() + ((float)core->getMouse()->getOffsetX() / (float)100));
        translation->setY(translation->getY() - ((float)core->getMouse()->getOffsetY() / (float)100));
      }
    }
    else if(yRotation > 45 + 90 && yRotation <= 45 + 180) // Back
    {
      if(core->isKeyPressed('r') == true)
      {
        state = 3;
        translation = model->getAnimations()->at(0)->getFrame()->getTranslation(model->getPart(partsListBox->getSelectedItem()), true);
        translation->setYRotation(translation->getYRotation() + ((float)core->getMouse()->getOffsetX()));
        translation->setXRotation(translation->getXRotation() - ((float)core->getMouse()->getOffsetY()));
      }
      else
      {
        state = 1;
        translation = model->getAnimations()->at(0)->getFrame()->getTranslation(model->getPart(partsListBox->getSelectedItem()), true);
        translation->setX(translation->getX() + ((float)-core->getMouse()->getOffsetX() / (float)100));
        translation->setY(translation->getY() - ((float)core->getMouse()->getOffsetY() / (float)100));
      }
    }
    else if(yRotation > 45 + 180 && yRotation <= 45 + 180 + 90) // Right
    {
      if(core->isKeyPressed('r') == true)
      {
        state = 3;
        translation = model->getAnimations()->at(0)->getFrame()->getTranslation(model->getPart(partsListBox->getSelectedItem()), true);
        translation->setYRotation(translation->getYRotation() + ((float)core->getMouse()->getOffsetX()));
        translation->setZRotation(translation->getZRotation() - ((float)core->getMouse()->getOffsetY()));
      }
      else
      {
        state = 1;
        translation = model->getAnimations()->at(0)->getFrame()->getTranslation(model->getPart(partsListBox->getSelectedItem()), true);
        translation->setZ(translation->getZ() - ((float)core->getMouse()->getOffsetX() / (float)100));
        translation->setY(translation->getY() - ((float)core->getMouse()->getOffsetY() / (float)100));
      }
    }
  }
}

void ModelWindow::onFileButtonClicked()
{
  PopupMenu* po = new PopupMenu(core, 2, 28);
  po->addItem("Open", new GenericFunction<ModelWindow>(this, &ModelWindow::onOpenButtonClicked));
  po->addItem("Close", new GenericFunction<ModelWindow>(this, &ModelWindow::onCloseButtonClicked));
}

void ModelWindow::onOpenButtonClicked()
{
  openFileDialog = new OpenFileDialog(core);
  openFileDialog->setFiletype(".obj");
  openFileDialog->getPictureBox()->setPicture(Path::getPath() + "/share/wastudio/data/fade_pattern.png");
  openFileDialog->setOpenButtonClickFunction(new GenericFunction<ModelWindow > (this, &ModelWindow::onModelSelected));
}

void ModelWindow::onCloseButtonClicked()
{
  TestWindow* testWindow = NULL;

  testWindow = new TestWindow(core);
  core->add(testWindow);
  close();
}

void ModelWindow::onAnimationButtonClicked()
{
  PopupMenu* po = new PopupMenu(core, 77, 28);
  po->addItem("Attach", new GenericFunction<ModelWindow>(this, &ModelWindow::onAttachButtonClicked));
  po->addItem("Detach", new GenericFunction<ModelWindow>(this, &ModelWindow::onDetachButtonClicked));
  po->addItem("Rename", new GenericFunction<ModelWindow>(this, &ModelWindow::onRenameButtonClicked));
  po->addItem("Save As", new GenericFunction<ModelWindow>(this, &ModelWindow::onAnimationSaveAsSelected));
  po->addItem("Save", new GenericFunction<ModelWindow>(this, &ModelWindow::onAnimationSaveSelected));
}

void ModelWindow::onRenameButtonClicked()
{
  core->add(new RenameWindow(core, model.get()));
}

void ModelWindow::onAttachButtonClicked()
{
  openFileDialog = new OpenFileDialog(core);
  openFileDialog->setFiletype(".anm");
  openFileDialog->getPictureBox()->setPicture(Path::getPath() + "/share/wastudio/data/fade_pattern.png");
  openFileDialog->setOpenButtonClickFunction(new GenericFunction<ModelWindow > (this, &ModelWindow::onAnimationSelected));
}

void ModelWindow::onDetachButtonClicked()
{
  model->getAnimations()->clear();
  model->getAnimations()->add(new Animation(model.get()));
  model->enableAnimation(0);
  animationPath = "";
}

void ModelWindow::onModelButtonClicked()
{
  PopupMenu* po = new PopupMenu(core, 152, 28);
  po->addItem("Attach", new GenericFunction<ModelWindow>(this, &ModelWindow::onAttachPartButtonClicked));
  po->addItem("Detach", new GenericFunction<ModelWindow>(this, &ModelWindow::onDetachPartButtonClicked));
}

void ModelWindow::onDetachPartButtonClicked()
{
  Part* part = NULL;

  part = model->getPart(partsListBox->getSelectedItem());

  if(part == NULL)
  {
    new Gluten::MessageBox(core, "No part was selected");
    return;
  }

  part->attachModel(NULL);
}

void ModelWindow::onAttachPartButtonClicked()
{
  Part* part = NULL;

  part = model->getPart(partsListBox->getSelectedItem());

  if(part == NULL)
  {
    new Gluten::MessageBox(core, "No part was selected");
    return;
  }

  openFileDialog = new OpenFileDialog(core);
  openFileDialog->setFiletype(".obj");
  openFileDialog->getPictureBox()->setPicture(Path::getPath() + "/share/wastudio/data/fade_pattern.png");
  openFileDialog->setOpenButtonClickFunction(new GenericFunction<ModelWindow > (this, &ModelWindow::onAttachPartSelected));
}

void ModelWindow::onAttachPartSelected()
{
  Part* part = NULL;

  part = model->getPart(partsListBox->getSelectedItem());

  if(part == NULL)
  {
    return;
  }

  part->attachModel(new Model(openFileDialog->getSelectedPath()));
}

void ModelWindow::onHelpButtonClicked()
{
  PopupMenu* po = new PopupMenu(core, 227, 28);
  po->addItem("About", new GenericFunction<ModelWindow>(this, &ModelWindow::onAboutButtonClicked));
}

void ModelWindow::onAboutButtonClicked()
{
  core->add(new AboutWindow(core));
}

void ModelWindow::onModelSelected()
{
  model.reset(new Model(openFileDialog->getSelectedPath()));

  partsListBox->getItems()->clear();
  partsListBox->reset();

  for(int index = 0; index < model->getParts()->size(); index++)
  {    
    partsListBox->getItems()->push_back(model->getParts()->at(index)->getName());
  }

  modelPath = openFileDialog->getSelectedPath();
  animationPath = "";
  model->enableAnimation(0);
}

void ModelWindow::onAnimationSelected()
{
  try
  {
    model->getAnimations()->clear();
    model->addAnimation(openFileDialog->getSelectedPath());
    model->enableAnimation(0);
    animationPath = openFileDialog->getSelectedPath();
  }
  catch(exception& e)
  {
    //cout << "Exception: " << e.what() << endl;
    //new MessageBox(core, string("Exception: ") + e.what());
    // Add default back if this fails
    model->getAnimations()->clear();
    model->getAnimations()->add(new Animation(model.get()));
    model->enableAnimation(0);
    throw;
  }
}

void ModelWindow::onPartsListBoxClicked()
{
  if(partsListBox->getSelectedItem() == "")
  {
    return;
  }

  model->highlightPart(partsListBox->getSelectedItem());
}

void ModelWindow::onAnimationSaveSelected()
{
  if(animationPath == "")
  {
    onAnimationSaveAsSelected();
    return;
  }

  model->getAnimations()->at(0)->save(animationPath);
}

void ModelWindow::onAnimationSaveAsSelected()
{
  saveFileDialog = new SaveFileDialog(core);
  saveFileDialog->setFiletype(".anm");
  saveFileDialog->getPictureBox()->setPicture(Path::getPath() + "/share/wastudio/data/fade_pattern.png");
  saveFileDialog->setSaveButtonClickFunction(new GenericFunction<ModelWindow > (this, &ModelWindow::onAnimationPathSelected));
}

void ModelWindow::onAnimationPathSelected()
{
  animationPath = saveFileDialog->getSelectedPath();
  //cout << "Path: " << animationPath << endl;
  model->getAnimations()->at(0)->save(animationPath);
}

string ModelWindow::getFilenameFromPath(string path)
{
  string filename;
  int cpos = 0;

  if(path == "")
  {
    return "";
  }

  cpos = path.find_last_of('/');

  if(cpos == 0 || cpos == -1)
  {
    cpos = path.find_last_of('\\');

    if(cpos == 0 || cpos == -1)
    {
      cpos = 0;
    }
  }

  filename = path.substr(cpos + 1);

  return filename;
}

void ModelWindow::updateInformationPanel()
{
  stringstream ss;

  modelFilenameLabel->setText("Model: " + getFilenameFromPath(modelPath));
  animationNameLabel->setText("Animation: " + model->getAnimations()->at(0)->getName());

  if(animationPath != "")
  {
    animationFilenameLabel->setText("File: " + getFilenameFromPath(animationPath));
  }
  else
  {
    animationFilenameLabel->setText("File: <null>");
  }

  ss << "Frame: ";
  ss << 1 + model->getAnimations()->at(0)->getCurrentFrame();
  ss << " / ";
  ss << model->getAnimations()->at(0)->getMaxFrames();
  animationFrameLabel->setText(ss.str());
}

void ModelWindow::onRemoveButtonClicked()
{
  if( model->getAnimations()->at(0)->getFrames()->size() > 1)
  {
    model->getAnimations()->at(0)->getFrames()->remove(model->getAnimations()->at(0)->getCurrentFrame());
  }
}

void ModelWindow::onAddButtonClicked()
{
  Frame* currentFrame = NULL;
  Frame* newFrame = NULL;

#ifdef TRIAL_YES

  if(model->getAnimations()->at(0)->getFrames()->size() > 4)
  {
    new Gluten::MessageBox(core, "Only 5 frames allowed in the trial version");
    return;
    //throw Gluten::Exception("Only 10 frames allowed in the trial version");
  }

#endif

  model->getAnimations()->at(0)->getFrames()->insert(model->getAnimations()->at(0)->getCurrentFrame()+1, new Frame(model->getAnimations()->at(0)));

  currentFrame = model->getAnimations()->at(0)->getFrames()->at(model->getAnimations()->at(0)->getCurrentFrame());
  newFrame = model->getAnimations()->at(0)->getFrames()->at(model->getAnimations()->at(0)->getCurrentFrame()+1);
  Frame::copy(currentFrame, newFrame);
  frameHScroll->setCurrent(frameHScroll->getCurrent()+1);
}

void ModelWindow::onInterpolateButtonClicked()
{
  Frame* currentFrame = NULL;
  Frame* newFrame = NULL;
  Frame* nextFrame = NULL;

#ifdef TRIAL_YES

  if(model->getAnimations()->at(0)->getFrames()->size() > 4)
  {
    new Gluten::MessageBox(core, "Only 5 frames allowed in the trial version");
    return;
    //throw Gluten::Exception("Only 10 frames allowed in the trial version");
  }

#endif

  model->getAnimations()->at(0)->getFrames()->insert(model->getAnimations()->at(0)->getCurrentFrame()+1, new Frame(model->getAnimations()->at(0)));

  currentFrame = model->getAnimations()->at(0)->getFrames()->at(model->getAnimations()->at(0)->getCurrentFrame());
  newFrame = model->getAnimations()->at(0)->getFrames()->at(model->getAnimations()->at(0)->getCurrentFrame()+1);
  Frame::copy(currentFrame, newFrame);

  if(model->getAnimations()->at(0)->getCurrentFrame()+2 < model->getAnimations()->at(0)->getFrames()->size())
  {
    nextFrame = model->getAnimations()->at(0)->getFrames()->at(model->getAnimations()->at(0)->getCurrentFrame()+2);
  }
  else
  {
    nextFrame = model->getAnimations()->at(0)->getFrames()->at(0);
  }

  Frame::merge(nextFrame, newFrame);
  frameHScroll->setCurrent(frameHScroll->getCurrent()+1);
}

void ModelWindow::onPlayButtonClicked()
{
  if(playing == true)
  {
    playButton->setPosition(0, 0);
    pauseButton->setPosition(-100, 0);
    playing = false;
    core->setEventDriven(false);
  }
  else
  {
    playButton->setPosition(-100, 0);
    pauseButton->setPosition(0, 0);
    playing = true;
    core->setEventDriven(true);
  }
}

