#include <gluten/ListBox.h>

namespace Gluten
{

ListBox::ListBox(Panel* panel) : Component(panel)
{
  selectedItemIndex = -1;
  font.reset(new Font());
  font->setColor(Color(255, 255, 255, 255));
  unselectedFont.reset(new Font());
  unselectedFont->setColor(Color::getDefaultSelect());
  scrollBackgroundColor = Color(255, 255, 255, 255);
  maxItems = 0;
  needsScrollBars = false;
  scrollRectangle.reset(new Rectangle(0, 0, 25, 100));
  listOffset = 0;
}

ListBox::~ListBox()
{

}

void ListBox::reset()
{
  listOffset = 0;
  scrollRectangle.reset(new Rectangle(0, 0, 25, 100));
  needsScrollBars = false;
  maxItems = 0;
  selectedItemIndex = -1;
}

void ListBox::draw()
{
  double sub = 0;

  listOffset = ((float)scrollRectangle->getY() / (float)rectangle->getHeight()) * items.size();
  maxItems = ((float)rectangle->getHeight() - 25) / (float)25;

  if (maxItems > items.size())
  {
    maxItems = items.size();
  }

  if(selectedItemIndex >= items.size())
  {
    selectedItemIndex = -1;
  }

  // Why 3? Who knows... lol
  //sub = ((double) items.size() + 3) / (double) maxItems;
  //scrollRectangle->setHeight((double) rectangle->getHeight() / sub);

  if (maxItems < items.size())
  {
    needsScrollBars = true;
    scrollRectangle->setHeight((rectangle->getHeight() * ((float)maxItems / (float)items.size())-25));
  }
  else
  {
    needsScrollBars = false;
  }

  if (mouseOver == true)
  {
    color.enableLight();
  }
  else
  {
    color.enable();
  }

  glBegin(GL_LINE_LOOP);
  glVertex2f(rectangle->getX(), rectangle->getY());
  glVertex2f(rectangle->getX(), rectangle->getY() + rectangle->getHeight());
  glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + rectangle->getHeight());
  glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY());
  glEnd();

  glBegin(GL_QUADS);
  glVertex2f(rectangle->getX(), rectangle->getY());
  glVertex2f(rectangle->getX(), rectangle->getY() + 25);
  glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + 25);
  glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY());
  glEnd();

  font->draw(rectangle->getX() + 10, rectangle->getY() + (25 / 2) - (font->getCharacterHeight() / 2), text);

  if (selectedItemIndex != -1 && (selectedItemIndex - listOffset) >= 0 && (selectedItemIndex - listOffset) < maxItems)
  {
    unselectedFont->getColor().enable();
    glBegin(GL_QUADS);
    glVertex2f(rectangle->getX() + 1, rectangle->getY() + 25 + ((selectedItemIndex - listOffset) * 25));
    glVertex2f(rectangle->getX() + 1, rectangle->getY() + 25 + ((selectedItemIndex - listOffset) * 25) + 25);
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + 25 + ((selectedItemIndex - listOffset) * 25) + 25);
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + 25 + ((selectedItemIndex - listOffset) * 25));
    glEnd();
  }

  //for (int itemIndex = 0; itemIndex < maxItems; itemIndex++)
  //cout << "Scroll: " << scrollRectangle->getY() << endl;
  //cout << "Rectangle: " << rectangle->getHeight() << endl;
  //cout << "Ans: " << ((double)scrollRectangle->getY() / (double)rectangle->getHeight()) * items.size() << endl;
  //cout << listOffset << endl;

  for (int itemIndex = listOffset; itemIndex < maxItems + listOffset; itemIndex++)
  //for (int itemIndex = listOffset; itemIndex < items.size(); itemIndex++)
  {
    if (itemIndex == selectedItemIndex)
    {
      font->draw(rectangle->getX() + 10, -2 + rectangle->getY() + ((itemIndex - listOffset) * 25) + (unselectedFont->getCharacterHeight() / 2) + 25, items.at(itemIndex));
    }
    else
    {
      unselectedFont->draw(rectangle->getX() + 10, -2 + rectangle->getY() + ((itemIndex - listOffset) * 25) + (unselectedFont->getCharacterHeight() / 2) + 25, items.at(itemIndex));
    }
  }

  if (needsScrollBars == true)
  {
    scrollBackgroundColor.enableLight();

    glBegin(GL_QUADS);
    glVertex2f(rectangle->getX() + rectangle->getWidth() - 20, rectangle->getY() + 25);
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + 25);
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth() - 20, rectangle->getY() + rectangle->getHeight());
    glEnd();

    if (mouseOver == true)
    {
      color.enableLight();
    }
    else
    {
      color.enable();
    }

    glBegin(GL_QUADS);
    glVertex2f(rectangle->getX() + rectangle->getWidth() - 19, rectangle->getY() + 26 + scrollRectangle->getY());
    glVertex2f(rectangle->getX() + rectangle->getWidth() - 2, rectangle->getY() + 26 + scrollRectangle->getY());
    glVertex2f(rectangle->getX() + rectangle->getWidth() - 2, rectangle->getY() + 23 + scrollRectangle->getY() + scrollRectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth() - 19, rectangle->getY() + 23 + scrollRectangle->getY() + scrollRectangle->getHeight());
    glEnd();

    if (mouseOver == true)
    {
      color.enableLight();
    }
    else
    {
      color.enable();
    }

    glBegin(GL_LINE_LOOP);
    glVertex2f(rectangle->getX() + rectangle->getWidth() - 20, rectangle->getY() + 25);
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + 25);
    glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + rectangle->getHeight());
    glVertex2f(rectangle->getX() + rectangle->getWidth() - 20, rectangle->getY() + rectangle->getHeight());
    glEnd();
  }

  if (mouseOver == true)
  {
    color.enableLight();
  }
  else
  {
    color.enable();
  }

  glBegin(GL_LINE_LOOP);
  glVertex2f(rectangle->getX(), rectangle->getY());
  glVertex2f(rectangle->getX(), rectangle->getY() + rectangle->getHeight());
  glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY() + rectangle->getHeight());
  glVertex2f(rectangle->getX() + rectangle->getWidth(), rectangle->getY());
  glEnd();

  Component::draw();
}

vector<string>* ListBox::getItems()
{
  return &items;
}

void ListBox::mouseDown(int x, int y, int button, Mouse* mouse)
{
  int potentialIndex = 0;

  if(mouse->getButton1() == false)
  {
    Component::mouseDown(x, y, button, mouse);
    return;
  }

  if (x > rectangle->getWidth() - 25 && needsScrollBars == true)
  {
    scrollRectangle->setY((y - 25) - (scrollRectangle->getHeight() / 2));

    if (scrollRectangle->getY() < 0)
    {
      scrollRectangle->setY(0);
    }

    if (scrollRectangle->getY() + scrollRectangle->getHeight() + 25 > rectangle->getHeight())
    {
      scrollRectangle->setY(rectangle->getHeight() - scrollRectangle->getHeight() - 25);
    }

    Component::mouseDown(x, y, button, mouse);

    return;
  }

  potentialIndex = (y / 25) - 1;

  if (potentialIndex != -1 && potentialIndex < items.size())
  {
    selectedItemIndex = potentialIndex + listOffset;
  }

  Component::mouseDown(x, y, button, mouse);
}

string ListBox::getSelectedItem()
{
  if(selectedItemIndex < 0 && selectedItemIndex >= items.size())
  {
    return "";
  }
  
  return items.at(selectedItemIndex);
}

void ListBox::mouseMove(int x, int y, Mouse* mouse)
{
  if(mouse->getButton1() == true && x > rectangle->getWidth() - 25 && needsScrollBars == true)
  {
    mouseDown(x, y, 1, mouse);
  }

  Component::mouseMove(x, y, mouse);
}
}

