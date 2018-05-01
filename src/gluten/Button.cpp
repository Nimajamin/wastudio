#include <gluten/Button.h>

#include <gluten/Rectangle.h>
#include <gluten/Font.h>
#include <gluten/Color.h>

namespace Gluten
{
  Button::Button(Panel* panel) : Component(panel)
  {
    font.reset(new Font());
    font->setColor(Color(255, 255, 255, 255));
  }

  Button::~Button()
  {

  }

  void Button::draw()
  {
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

    glBegin(GL_QUADS);
    glVertex2f(rectangle->getX(), rectangle->getY());
    glVertex2f(rectangle->getX(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY());
    glEnd();

    font->draw(rectangle->getX() + (rectangle->getWidth() / 2) - ((font->getCharacterWidth() * text.length()) / 2), rectangle->getY() + (rectangle->getHeight() / 2) - (font->getCharacterHeight() / 2), text);
  }
}

