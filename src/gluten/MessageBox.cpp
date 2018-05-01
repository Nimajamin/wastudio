#include <gluten/MessageBox.h>

#include <gluten/Label.h>
#include <gluten/Button.h>
#include <gluten/Function.h>

namespace Gluten
{

MessageBox::MessageBox(Core* core, string message) : Window(core)
{
  color.setRGBA(0, 0, 0, 175);

  centerPanel = new Panel(this);
  centerPanel->setSize(600, 100);

  label = new Label(centerPanel);
  label->setPosition(0, 25);
  label->setSize(600, 25);
  label->setTextAlignment(1);
  label->setText(message);

  okButton = new Button(centerPanel);
  okButton->setSize(75, 25);
  okButton->setPosition(515, 65);
  okButton->setText("OK");
  okButton->setLeftMouseButtonClickFunction(new GenericFunction<MessageBox > (this, &MessageBox::onOkButtonClicked));

  core->add(this);
}

MessageBox::~MessageBox()
{

}

void MessageBox::onOkButtonClicked()
{
  close();
}
}
