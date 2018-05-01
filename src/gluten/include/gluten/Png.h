namespace Gluten
{
  class Png;
}

#ifndef GLUTPNG_H
#define GLUTPNG_H

#include <string>
#include <vector>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <gluten/Exception.h>

using namespace std;

namespace Gluten
{
  class Png
  {
  private:
    int x;
    int y;

    unsigned width;
    unsigned height;
    int powerWidth;
    int powerHeight;

    std::vector<unsigned char> powerData;

  public:
    Png(string path);

    int getWidth();
    int getHeight();
    int getOffsetX();
    int getOffsetY();

    unsigned char* getData();

  };
}

#endif

