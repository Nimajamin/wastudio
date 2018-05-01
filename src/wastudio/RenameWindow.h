class RenameWindow;

#ifndef RENAMEWINDOW_H
#define RENAMEWINDOW_H

#include <gluten.h>
#include <wavefront.h>

using namespace Gluten;
using namespace Wavefront;

class RenameWindow : public Gluten::Window
{
private:
  Model* model;

  Panel* centerPanel;
  Button* renameButton;
  Button* cancelButton;
  Label* aboutLabel;
  Label* renameLabel;
  TextBox* nameTextBox;

public:
  RenameWindow(Core* core, Model* model);
  ~RenameWindow();

  void onRenameButtonClicked();
  void onCancelButtonClicked();

};

#endif

