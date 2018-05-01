namespace Gluten
{
  class SaveFileDialog;
}

#ifndef SAVEFILEDIALOG_H
#define SAVEFILEDIALOG_H

#include <dirent.h>

#include <gluten/Window.h>
#include <gluten/Panel.h>
#include <gluten/Button.h>
#include <gluten/ImageButton.h>
#include <gluten/PictureBox.h>
#include <gluten/ListBox.h>
#include <gluten/Label.h>
#include <gluten/Function.h>
#include <gluten/TextBox.h>

using namespace std;

namespace Gluten
{
  class SaveFileDialog : public Window
  {
  private:
    auto_ptr<Function> openButtonClickFunction;
    PictureBox* pictureBox;
    Panel* centerPanel;
    Button* cancelButton;
    Button* openButton;
    Button* upButton;
    ListBox* directoryListBox;
    Label* label;
    Label* typeLabel;
    TextBox* textBox;

    string directory;
    string filetype;

    bool isDirectory(string path);

  protected:

  public:
    SaveFileDialog(Core* core);
    virtual ~SaveFileDialog();

    void onCancelButtonClicked();
    void onSaveButtonClicked();
    void onUpButtonClicked();

    void setSaveButtonClickFunction(Function* function);
    void setDirectory(string path);

    void onListBoxDoubleClicked();
    void setFiletype(string filetype);
    string getSelectedPath();

    PictureBox* getPictureBox();

  };
}

#endif

