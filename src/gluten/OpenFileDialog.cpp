#include <gluten/OpenFileDialog.h>

namespace Gluten
{

OpenFileDialog::OpenFileDialog(Core* core) : Window(core)
{
  color.setRGBA(0, 0, 0, 175);
  filetype = "";

  centerPanel = new Panel(this);
  centerPanel->setSize(300, 400);

  pictureBox = new PictureBox(centerPanel);
  pictureBox->setPosition(0, 0);
  pictureBox->setSize(300, 400);

  label = new Label(centerPanel);
  label->setPosition(10, 10);
  label->setSize(100, 25);
  label->setTextAlignment(0);
  label->setText("Select file to open...");

  upButton = new Button(centerPanel);
  upButton->setSize(50, 25);
  upButton->setPosition(240, 10);
  upButton->setText("Up");
  upButton->setLeftMouseButtonClickFunction(new GenericFunction<OpenFileDialog > (this, &OpenFileDialog::onUpButtonClicked));

  openButton = new Button(centerPanel);
  openButton->setSize(75, 25);
  openButton->setPosition(135, 365);
  openButton->setText("Open");
  openButton->setLeftMouseButtonClickFunction(new GenericFunction<OpenFileDialog > (this, &OpenFileDialog::onOpenButtonClicked));

  cancelButton = new Button(centerPanel);
  cancelButton->setSize(75, 25);
  cancelButton->setPosition(215, 365);
  cancelButton->setText("Cancel");
  cancelButton->setLeftMouseButtonClickFunction(new GenericFunction<OpenFileDialog > (this, &OpenFileDialog::onCancelButtonClicked));

  directoryListBox = new ListBox(centerPanel);
  directoryListBox->setSize(280, 300);
  directoryListBox->setPosition(10, 45);
  directoryListBox->setText("Files");

  directoryListBox->setLeftMouseButtonDoubleClickFunction(new GenericFunction<OpenFileDialog > (this, &OpenFileDialog::onListBoxDoubleClicked));

  char* tmp = NULL;
  std::string home;
  
  tmp = getenv("HOME");
  
  //std::string home = getenv("HOME");
  
  if(tmp == NULL)
  {
    home = getenv("USERPROFILE");
  }
  else
  {
    home = std::string(tmp);
  }

  setDirectory(home);
  core->add(this);
}

OpenFileDialog::~OpenFileDialog()
{

}

void OpenFileDialog::onCancelButtonClicked()
{
  close();
}

void OpenFileDialog::onOpenButtonClicked()
{
  onListBoxDoubleClicked();
}

void OpenFileDialog::onUpButtonClicked()
{
  setDirectory(directory + "/..");
}

void OpenFileDialog::setOpenButtonClickFunction(Function* function)
{
  openButtonClickFunction.reset(function);
}

void OpenFileDialog::setDirectory(string path)
{
  DIR* dir = NULL;
  struct dirent* file = NULL;

  directoryListBox->getItems()->clear();
  directoryListBox->reset();
  dir = opendir(path.c_str());

  if (dir == NULL)
  {
    throw Exception("Failed to open '" + path + "'");
  }

  while ((file = readdir(dir)) != NULL)
  {
    if (string(file->d_name) != "." && string(file->d_name) != ".." && string(file->d_name)[0] != '.')
    {
      if (isDirectory(path + "/" + string(file->d_name)) == true)
      {
        directoryListBox->getItems()->push_back(file->d_name);
      }
      else
      {
        if (filetype == "")
        {
          directoryListBox->getItems()->push_back(file->d_name);
        }
        else
        {
          if (string(file->d_name).find(filetype.c_str()) != -1)
          {
            directoryListBox->getItems()->push_back(file->d_name);
          }
        }
      }
    }
  }

  closedir(dir);
  this->directory = path;
}

void OpenFileDialog::onListBoxDoubleClicked()
{
  if (directoryListBox->getSelectedItem() == "")
  {
    return;
  }

  if (isDirectory(directory + "/" + directoryListBox->getSelectedItem()) == true)
  {
    setDirectory(directory + "/" + directoryListBox->getSelectedItem());
  }
  else
  {
    if (openButtonClickFunction.get() != NULL)
    {
      openButtonClickFunction->execute();
    }

    close();
  }
}

bool OpenFileDialog::isDirectory(string path)
{
  DIR* dir = NULL;

  dir = opendir(path.c_str());

  if (dir == NULL)
  {
    return false;
  }
  else
  {
    closedir(dir);
    return true;
  }
}

void OpenFileDialog::setFiletype(string filetype)
{
  this->filetype = filetype;
  setDirectory(directory);
}

string OpenFileDialog::getSelectedPath()
{
  return directory + "/" + directoryListBox->getSelectedItem();
}

PictureBox* OpenFileDialog::getPictureBox()
{
  return pictureBox;
}
}
