#include <gluten/Font.h>

#include <gluten/Color.h>
#include <gluten/Png.h>
#include <gluten/Path.h>

namespace Gluten
{
  Font::Font()
  {
    png = std::make_shared<Png>(Path::getPath() + "/share/wastudio/data/font.png");
    layout.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZ      ");
    layout.push_back("abcdefghijklmnopqrstuvwxyz      ");
    layout.push_back("0123456789                      ");
    layout.push_back("!\"$$%^&*()_+-=[]{}:@#;'~|<>?\\,./");
    //width = Resource::defaultFontTextureWidth;
    width = png->getWidth();
    height = png->getHeight();
    //height = Resource::defaultFontTextureHeight;

    characterWidth = width / (512 / 8);
    characterHeight = height / (128 / 14);
    //data = new unsigned char[width*height*4];
    data = png->getData();
    color = Color(0, 0, 0, 255);
    //std::cout << "Width : " << width << std::endl;
    //std::cout << "Height : " << height << std::endl;
    for(int index = 0; index < width*height*4; index++)
    {
      //data[index] = Resource::defaultFontTextureData[index];
      data[index] = png->getData()[index];
    }

    for(int index = 0; index < width*height*4; index+=4)
    {
      data[index] = color.getR();
      data[index+1] = color.getG();
      data[index+2] = color.getB();
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  }

  Font::~Font()
  {
    //delete[] data;
    glDeleteTextures(1, &texture);
  }

  void Font::setColor(Color color)
  {
    this->color = color;
    glDeleteTextures(1, &texture);

    for(int index = 0; index < width*height*4; index+=4)
    {
      data[index] = color.getR();
      data[index+1] = color.getG();
      data[index+2] = color.getB();
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  }

  Color Font::getColor()
  {
    return color;
  }

  void Font::draw(int x, int y, string text)
  {
    /*
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2d(1, 1);
    glVertex2f(x, y);
    glTexCoord2d(0, 1);
    glVertex2f(x + Resource::defaultFontTextureWidth, y);
    glTexCoord2d(0, 0);
    glVertex2f(x + Resource::defaultFontTextureWidth, y + Resource::defaultFontTextureHeight);
    glTexCoord2d(1, 0);
    glVertex2f(x, y + Resource::defaultFontTextureHeight);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    */

    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    for(int index = 0; index < text.length(); index++)
    {
      draw(x + index * characterWidth, y, text[index]);
    }
    glDisable(GL_TEXTURE_2D);
  }

  void Font::draw(int x, int y, char character)
  {
    int clipX = -1;
    int clipY = -1;
    float scaleX = (float)1 / (float)width;
    float scaleY = (float)1 / (float)height;

    for(int ya = 0; ya < layout.size(); ya++)
    {
      for(int x = 0; x < layout.at(ya).length(); x++)
      {
        if(layout.at(ya)[x] == character)
        {
          clipX = x * characterWidth;
          clipY = ya * characterHeight;
        }
      }
    }

    if(clipX == -1 || clipY == -1)
    {
      return;
      throw exception();
    }

    float texX = (float)1 - ((float)scaleX * (float)clipX);
    float texY = (float)1 - ((float)scaleY * (float)clipY);

    float texWidth = texX - ((float)scaleX * (float)characterWidth);
    float texHeight = texY - ((float)scaleY * (float)characterHeight);

    //cout << "X: " << texX << endl;
    //cout << "Y: " << texY << endl;
    //cout << "Width: " << texWidth << endl;
    //cout << "Height: " << texHeight << endl;

    glColor4f(1.0, 1.0, 1.0, 1.0);
    //glBindTexture(GL_TEXTURE_2D, texture);
    //glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2d(texX, texY);
    glVertex2f(x, y);
    glTexCoord2d(texWidth, texY);
    glVertex2f(x + characterWidth, y);
    glTexCoord2d(texWidth, texHeight);
    glVertex2f(x + characterWidth, y + characterHeight);
    glTexCoord2d(texX, texHeight);
    glVertex2f(x, y + characterHeight);
    glEnd();
    //glDisable(GL_TEXTURE_2D);
  }

  int Font::getCharacterWidth()
  {
    return characterWidth;
  }

  int Font::getCharacterHeight()
  {
    return characterHeight;
  }
}

