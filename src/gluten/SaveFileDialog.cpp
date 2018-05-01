#include <gluten/SaveFileDialog.h>

namespace Gluten
{

SaveFileDialog::SaveFileDialog(Core* core) : Window(core)
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
  label->setText("Location to save...");

  upButton = new Button(centerPanel);
  upButton->setSize(50, 25);
  upButton->setPosition(240, 10);
  upButton->setText("Up");
  upButton->setLeftMouseButtonClickFunction(new GenericFunction<SaveFileDialog > (this, &SaveFileDialog::onUpButtonClicked));

  openButton = new Button(centerPanel);
  openButton->setSize(75, 25);
  openButton->setPosition(135, 365);
  openButton->setText("Save");
  openButton->setLeftMouseButtonClickFunction(new GenericFunction<SaveFileDialog > (this, &SaveFileDialog::onSaveButtonClicked));

  cancelButton = new Button(centerPanel);
  cancelButton->setSize(75, 25);
  cancelButton->setPosition(215, 365);
  cancelButton->setText("Cancel");
  cancelButton->setLeftMouseButtonClickFunction(new GenericFunction<SaveFileDialog > (this, &SaveFileDialog::onCancelButtonClicked));

  directoryListBox = new ListBox(centerPanel);
  directoryListBox->setSize(280, 250);
  directoryListBox->setPosition(10, 45);
  directoryListBox->setText("Files");

  directoryListBox->setLeftMouseButtonDoubleClickFunction(new GenericFunction<SaveFileDialog > (this, &SaveFileDialog::onListBoxDoubleClicked));

  textBox = new TextBox(centerPanel);
  textBox->setPosition(10, 300);
  textBox->setSize(225, 25);
  textBox->setTextAlignment(0);
  textBox->setText("");

  typeLabel = new Label(centerPanel);
  typeLabel->setPosition(240, 300);
  typeLabel->setSize(55, 25);
  typeLabel->setTextAlignment(0);
  typeLabel->setText(filetype);

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

SaveFileDialog::~SaveFileDialog()
{

}

void SaveFileDialog::onCancelButtonClicked()
{
  close();
}

void SaveFileDialog::onSaveButtonClicked()
{
  if(textBox->getText() == "")
  {
    cout << "Please enter a filename" << endl;
    return;
  }

  if (openButtonClickFunction.get() != NULL)
  {
    openButtonClickFunction->execute();
  }

  close();
}

void SaveFileDialog::onUpButtonClicked()
{
  setDirectory(directory + "/..");
}

void SaveFileDialog::setSaveButtonClickFunction(Function* function)
{
  openButtonClickFunction.reset(function);
}

void SaveFileDialog::setDirectory(string path)
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

void SaveFileDialog::onListBoxDoubleClicked()
{
  if (directoryListBox->getSelectedItem() == "")
  {
    return;
  }

  if (isDirectory(directory + "/" + directoryListBox->getSelectedItem()) == true)
  {
    setDirectory(directory + "/" + directoryListBox->getSelectedItem());
  }
}

bool SaveFileDialog::isDirectory(string path)
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

void SaveFileDialog::setFiletype(string filetype)
{
  this->filetype = filetype;
  setDirectory(directory);
  typeLabel->setText(filetype);
}

string SaveFileDialog::getSelectedPath()
{
  return directory + "/" + textBox->getText() + filetype;
}

PictureBox* SaveFileDialog::getPictureBox()
{
  return pictureBox;
}
}
