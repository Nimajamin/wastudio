#ifndef FONT_H
#define FONT_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <gluten/Resource.h>
#include <gluten/Color.h>

using namespace std;

namespace Gluten
{
  class Png;

  class Font
  {
  private:
    Color color;
    std::shared_ptr<Png> png;
    GLuint texture;
    unsigned char* data;
    int width;
    int height;
    int characterWidth;
    int characterHeight;
    vector<string> layout;

  public:
    Font();
    ~Font();

    int getCharacterHeight();
    int getCharacterWidth();
    void setColor(Color color);
    Color getColor();
    void draw(int x, int y, string text);
    void draw(int x, int y, char character);

  };
}

#endif

