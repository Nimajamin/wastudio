namespace Gluten
{
  class Image;
}

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <memory>
#include <vector>
#include <fstream>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <gluten/Png.h>

using namespace std;

namespace Gluten
{
  class Image
  {
  private:
    GLuint texture;
    int width;
    int height;
    int offsetX;
    int offsetY;

  public:
    Image(string path);
    ~Image();

    void draw(int x, int y);
    void draw(int x, int y, int clipX, int clipY, int clipWidth, int clipHeight);
    int getHeight();
    int getWidth();
  };
}

#endif

