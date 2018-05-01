#include <gluten/Label.h>

#include <gluten/Font.h>

namespace Gluten
{
  Label::Label(Panel* panel) : Component(panel)
  {
    font.reset(new Font());
    font->setColor(Color(175, 175, 175, 255));
  }

  Label::~Label()
  {

  }

  void Label::draw()
  {
    backgroundColor.enable();

    glBegin(GL_QUADS);
    glVertex2f(rectangle->getX(), rectangle->getY());
    glVertex2f(rectangle->getX(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY());
    glEnd();

    if(textAlignment == 1)
    {
      font->draw(rectangle->getX() + (rectangle->getWidth() / 2) - ((font->getCharacterWidth() * text.length()) / 2), rectangle->getY() + (rectangle->getHeight() / 2) - (font->getCharacterHeight() / 2), text);
    }
    else if(textAlignment == 0)
    {
      font->draw(rectangle->getX(), rectangle->getY() + (rectangle->getHeight() / 2) - (font->getCharacterHeight() / 2), text);
    }
  }
}

