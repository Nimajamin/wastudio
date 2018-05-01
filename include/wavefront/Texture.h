#ifndef WAVEFRONT_TEXTURE_H
#define WAVEFRONT_TEXTURE_H

#include <memory>

#include <GL/glew.h>
#include <GL/gl.h>

namespace Wavefront
{

class Texture
{
private:
  static void freeTexture(GLuint* texture);

  unsigned width;
  unsigned height;
  GLuint _texture;
  std::shared_ptr<GLuint> texture;

public:
  Texture(std::string path);
  ~Texture();

  void bind();
  void draw(int x, int y);
  static void unbind();

};

}

#endif

