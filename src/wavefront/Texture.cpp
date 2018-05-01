#include <wavefront.h>

//#define PNG_ONLY

#ifdef PNG_ONLY
  #include "lodepng.h"
#else
  #define STB_IMAGE_IMPLEMENTATION
  #include "stb_image.h"
#endif

namespace Wavefront
{

void Texture::freeTexture(GLuint* texture)
{
  glDeleteTextures(1, texture);
}

Texture::Texture(std::string path)
{
  unsigned char *data = NULL;

#ifdef PNG_ONLY
  if(lodepng_decode32_file(&data, &width, &height, path.c_str()))
  {
    throw WavefrontException("Failed to open file '" + path + "'");
  }
#else
    int n = 0;
    int x = 0;
    int y = 0;

    //std::cout << "Loading: " << path << std::endl;

    data = stbi_load(path.c_str(), &x, &y, &n, 4);

    if(!data)
    {
      throw WavefrontException("File '" + path + "' failed to load");
    }

    width = x;
    height = y;
#endif

  glGenTextures(1, &_texture);
  texture.reset(&_texture, std::bind(Texture::freeTexture, &_texture));
  glBindTexture(GL_TEXTURE_2D, *texture.get());
  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

#ifdef PNG_ONLY
  free(data);
#else
  stbi_image_free(data);
#endif
}

Texture::~Texture()
{

}

void Texture::bind()
{
  glBindTexture(GL_TEXTURE_2D, *texture.get());
}

void Texture::draw(int x, int y)
{
  // bind
  bind();

  // draw quad
  glBegin(GL_QUADS);
  glTexCoord2d(0.0,0.0); glVertex2f(x, y);
  glTexCoord2d(0.0,1.0); glVertex2f(x, y + height);
  glTexCoord2d(1.0,1.0); glVertex2f(x + width, y + height);
  glTexCoord2d(1.0,0.0); glVertex2f(x + width, y);
  glEnd();
}

void Texture::unbind()
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

}
