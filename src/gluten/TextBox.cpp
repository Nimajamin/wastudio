#include <gluten/TextBox.h>

#include <gluten/Font.h>

namespace Gluten
{
  TextBox::TextBox(Panel* panel) : Component(panel)
  {
    font.reset(new Font());
    font->setColor(Color(175, 175, 175, 255));
    border = true;
    borderColor.setRGBA(100, 100, 100, 100);
  }

  TextBox::~TextBox()
  {

  }

  void TextBox::draw()
  {
    borderColor.enable();

    glBegin(GL_QUADS);
    glVertex2f(rectangle->getX(), rectangle->getY());
    glVertex2f(rectangle->getX(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY());
    glEnd();

    backgroundColor.enable();

    glBegin(GL_QUADS);
    glVertex2f(rectangle->getX()+1, rectangle->getY()+1);
    glVertex2f(rectangle->getX()+1, rectangle->getY() + rectangle->getHeight()-1);
    glVertex2f(rectangle->getX() + rectangle->getWidth()-1, rectangle->getY() + rectangle->getHeight()-1);
    glVertex2f(rectangle->getX() + rectangle->getWidth()-1, rectangle->getY()+1);
    glEnd();

    if(textAlignment == 1)
    {
      font->draw(rectangle->getX() + (rectangle->getWidth() / 2) - ((font->getCharacterWidth() * text.length()) / 2), rectangle->getY() + (rectangle->getHeight() / 2) - (font->getCharacterHeight() / 2), text);
    }
    else if(textAlignment == 0)
    {
      font->draw(rectangle->getX()+5, rectangle->getY() + (rectangle->getHeight() / 2) - (font->getCharacterHeight() / 2), text);
    }
  }

  void TextBox::keyTyped(char key)
  {
    if((int)key == 13)
    {
      return;
    }

    if((int)key == 8)
    {
      if(text == "")
      {
        return;
      }

      text = text.substr(0, text.length() - 1);

      return;
    }

    text = text+key;
  }
}

