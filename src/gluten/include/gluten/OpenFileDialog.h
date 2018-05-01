namespace Gluten
{
  class OpenFileDialog;
}

#ifndef OPENFILEDIALOG_H
#define OPENFILEDIALOG_H

#include <dirent.h>

#include <gluten/Window.h>
#include <gluten/Panel.h>
#include <gluten/Button.h>
#include <gluten/ImageButton.h>
#include <gluten/PictureBox.h>
#include <gluten/ListBox.h>
#include <gluten/Label.h>
#include <gluten/Function.h>

using namespace std;

namespace Gluten
{
  class OpenFileDialog : public Window
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
    string directory;
    string filetype;

    bool isDirectory(string path);

  protected:

  public:
    OpenFileDialog(Core* core);
    virtual ~OpenFileDialog();

    void onCancelButtonClicked();
    void onOpenButtonClicked();
    void onUpButtonClicked();

    void setOpenButtonClickFunction(Function* function);
    void setDirectory(string path);

    void onListBoxDoubleClicked();
    void setFiletype(string filetype);
    string getSelectedPath();

    PictureBox* getPictureBox();

  };
}

#endif

