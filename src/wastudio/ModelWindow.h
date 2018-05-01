class ModelWindow;

#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <sstream>

#include <gluten.h>
#include <wavefront.h>

#include "TestWindow.h"
#include "RenameWindow.h"

using namespace Gluten;
using namespace Wavefront;

class ModelWindow : public Gluten::Window
{
private:
  Panel* topPanel;
  Panel* partsPanel;
  Panel* framePanel;
  Panel* modifyFramesPanel;
  ListBox* partsListBox;
  Panel* menuPanel;
  Button* fileButton;
  Button* animationButton;
  Button* modelButton;
  Button* helpButton;
  PictureBox* pictureBox;
  OpenFileDialog* openFileDialog;
  SaveFileDialog* saveFileDialog;
  HScroll* frameHScroll;
  Panel* frameAdvancePanel;
  Panel* frameModPanel;
  ImageButton* addButton;
  ImageButton* interpolateButton;
  ImageButton* removeButton;
  ImageButton* playButton;
  ImageButton* pauseButton;
  auto_ptr<Image> watermarkImage;
  auto_ptr<Image> moveXYImage;
  auto_ptr<Image> moveZImage;
  auto_ptr<Image> rotateXYImage;
  auto_ptr<Image> rotateZImage;
  Label* demoLabel;

  Panel* informationPanel;
  Label* informationLabel;
  Label* modelFilenameLabel;
  Label* animationFilenameLabel;
  Label* animationNameLabel;
  Label* animationFrameLabel;

  auto_ptr<Model> model;
  double xRotation;
  double yRotation;
  double zoom;
  string animationPath;
  string modelPath;
  bool playing;
  int state;

public:
  ModelWindow(Core* core, string path);
  ~ModelWindow();

  void control();
  void update();
  void display();

  void onFileButtonClicked();
  void onOpenButtonClicked();
  void onCloseButtonClicked();

  void onAnimationButtonClicked();
  void onAttachButtonClicked();
  void onDetachButtonClicked();
  void onRenameButtonClicked();

  void onModelButtonClicked();
  void onAttachPartButtonClicked();
  void onAttachPartSelected();
  void onDetachPartButtonClicked();

  void onHelpButtonClicked();
  void onAboutButtonClicked();

  void onModelSelected();
  void onAnimationSelected();
  void onAnimationSaveSelected();
  void onAnimationSaveAsSelected();
  void onAnimationPathSelected();

  void onPartsListBoxClicked();
  void updateInformationPanel();

  string getFilenameFromPath(string path);

  void onPlayButtonClicked();
  void onRemoveButtonClicked();
  void onAddButtonClicked();
  void onInterpolateButtonClicked();

};

#endif
