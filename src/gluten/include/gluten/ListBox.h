namespace Gluten
{
  class ListBox;
}

#ifndef LISTBOX_H
#define LISTBOX_H

#include <memory>
#include <vector>

#include <gluten/Component.h>
#include <gluten/Panel.h>
#include <gluten/Font.h>
#include <gluten/Color.h>

using namespace std;

namespace Gluten
{
  class ListBox : public Component
  {
  private:
    auto_ptr<Font> unselectedFont;
    Color scrollBackgroundColor;
    vector<string> items;
    int selectedItemIndex;
    int maxItems;
    bool needsScrollBars;
    auto_ptr<Rectangle> scrollRectangle;
    int listOffset;

  public:
    ListBox(Panel* panel);
    ~ListBox();

    void draw();
    vector<string>* getItems();
    string getSelectedItem();
    void reset();

    virtual void mouseMove(int x, int y, Mouse* mouse);
    virtual void mouseDown(int x, int y, int button, Mouse* mouse);
  };
}

#endif

