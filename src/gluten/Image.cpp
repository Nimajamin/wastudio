#include <gluten/Image.h>

namespace Gluten
{
  Image::Image(string path)
  {
    std::shared_ptr<Png> png = std::make_shared<Png>(path);
    //png.reset(new Png(path));
    width = png->getWidth();
    height = png->getHeight();
    offsetX = png->getOffsetX();
    offsetY = png->getOffsetY();
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, png->getData());
  }

  Image::~Image()
  {
    glDeleteTextures(1, &texture);
  }

  void Image::draw(int x, int y)
  {
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(-offsetX / 2, -offsetY / 2, 0);
    glBegin(GL_QUADS);
    glTexCoord2d(1, 1);
    glVertex2f(x, y);
    glTexCoord2d(0, 1);
    glVertex2f(x + width, y);
    glTexCoord2d(0, 0);
    glVertex2f(x + width, y + height);
    glTexCoord2d(1, 0);
    glVertex2f(x, y + height);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
  }

  void Image::draw(int x, int y, int clipX, int clipY, int clipWidth, int clipHeight)
  {
    float scaleX = (float)1 / (float)width;
    float scaleY = (float)1 / (float)height;

    float texX = (float)1 - ((float)scaleX * (float)clipX);
    float texY = (float)1 - ((float)scaleY * (float)clipY);

    float texWidth = texX - ((float)scaleX * (float)clipWidth);
    float texHeight = texY - ((float)scaleY * (float)clipHeight);

    //cout << "X: " << texX << endl;
    //cout << "Y: " << texY << endl;
    //cout << "Width: " << texWidth << endl;
    //cout << "Height: " << texHeight << endl;

    glColor4f(1.0, 1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2d(texX, texY);
    glVertex2f(x, y);
    glTexCoord2d(texWidth, texY);
    glVertex2f(x + clipWidth, y);
    glTexCoord2d(texWidth, texHeight);
    glVertex2f(x + clipWidth, y + clipHeight);
    glTexCoord2d(texX, texHeight);
    glVertex2f(x, y + clipHeight);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }

  int Image::getWidth()
  {
    return width;
  }

  int Image::getHeight()
  {
    return height;
  }
}

