#include <gluten/CheckBox.h>

#include <gluten/Font.h>
#include <gluten/Color.h>
#include <gluten/Rectangle.h>

namespace Gluten
{
  CheckBox::CheckBox(Panel* panel) : Component(panel)
  {
    selectedColor = Color::getDefaultSelect();
    font.reset(new Font());
    font->setColor(Color::getDefault());
    checked = false;
  }

  CheckBox::~CheckBox()
  {

  }

  void CheckBox::draw()
  {
    if(mouse1Down == true)
    {
      selectedColor.enableDark();
    }
    else if(mouseOver == true)
    {
      selectedColor.enableLight();
    }
    else
    {
      selectedColor.enable();
    }

    glBegin(GL_QUADS);
    glVertex2f(rectangle->getX(), rectangle->getY());
    glVertex2f(rectangle->getX(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY());
    glEnd();

    if(mouse1Down == true)
    {
      color.enableDark();
    }
    else if(mouseOver == true)
    {
      color.enableLight();
    }
    else
    {
      color.enable();
    }

    if(checked == true)
    {
      glBegin(GL_QUADS);
      glVertex2f(rectangle->getX()+2, rectangle->getY()+2);
      glVertex2f(rectangle->getX()+2, rectangle->getY() + rectangle->getHeight()-3);
      glVertex2f(rectangle->getX() + rectangle->getWidth()-3, rectangle->getY() + rectangle->getHeight()-3);
      glVertex2f(rectangle->getX() + rectangle->getWidth()-3, rectangle->getY()+2);
      glEnd();
    }

    glBegin(GL_LINE_LOOP);
    glVertex2f(rectangle->getX(), rectangle->getY());
    glVertex2f(rectangle->getX(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY());
    glEnd();

    font->draw(rectangle->getX() + rectangle->getWidth() + 5, rectangle->getY() + (rectangle->getHeight() / 2) - (font->getCharacterHeight() / 2), text);
  }

  void CheckBox::mouseClick(int x, int y, int button, Mouse* mouse)
  {
    if(checked == true)
    {
      checked = false;
    }
    else
    {
      checked = true;
    }

    Component::mouseClick(x, y, button, mouse);
  }
}

