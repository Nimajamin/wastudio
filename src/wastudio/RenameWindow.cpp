#include "RenameWindow.h"

RenameWindow::RenameWindow(Core* core, Model* model) : Gluten::Window(core)
{
  this->model = model;
  color.setRGBA(0, 0, 0, 175);
  centerPanel = new Panel(this);
  centerPanel->setPosition(0, 0);
  centerPanel->setSize(300, 200);

  cancelButton = new Button(centerPanel);
  cancelButton->setPosition(220, 170);
  cancelButton->setSize(75, 25);
  cancelButton->setText("Cancel");
  cancelButton->setLeftMouseButtonClickFunction(new GenericFunction<RenameWindow>(this, &RenameWindow::onCancelButtonClicked));

  renameButton = new Button(centerPanel);
  renameButton->setPosition(140, 170);
  renameButton->setSize(75, 25);
  renameButton->setText("Rename");
  renameButton->setLeftMouseButtonClickFunction(new GenericFunction<RenameWindow>(this, &RenameWindow::onRenameButtonClicked));

  aboutLabel = new Label(centerPanel);
  aboutLabel->setText("Please specify the animation's name");
  aboutLabel->setPosition(0, 25);
  aboutLabel->setSize(300, 25);
  aboutLabel->setTextAlignment(1);

  renameLabel = new Label(centerPanel);
  renameLabel->setText("Name: ");
  renameLabel->setPosition(10, 95);
  renameLabel->setSize(45, 25);
  renameLabel->setTextAlignment(0);

  nameTextBox = new TextBox(centerPanel);
  nameTextBox->setText(model->getAnimations()->at(0)->getName());
  nameTextBox->setPosition(55, 95);
  nameTextBox->setSize(230, 25);
}

RenameWindow::~RenameWindow()
{

}

void RenameWindow::onCancelButtonClicked()
{
  close();
}

void RenameWindow::onRenameButtonClicked()
{
  model->getAnimations()->at(0)->setName(nameTextBox->getText());
  close();
}

