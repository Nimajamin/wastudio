#ifndef WAVEFRONT_MATERIALGROUP_H
#define WAVEFRONT_MATERIALGROUP_H

#include <memory>

#include <GL/glew.h>
#include <GL/gl.h>

namespace Wavefront
{

class Material;
class Face;
class MaterialGroup
{
private:
  static void freeBuffer(GLuint* buffer);

  Material* material;
  std::vector<Face*> faces;
  GLuint _vertexBuffer;
  std::shared_ptr<GLuint> vertexBuffer;
  GLuint _normalBuffer;
  std::shared_ptr<GLuint> normalBuffer;
  GLuint _colorBuffer;
  std::shared_ptr<GLuint> colorBuffer;
  GLuint _coordBuffer;
  std::shared_ptr<GLuint> coordBuffer;

public:
  void draw(bool highlighted);

  Material* getMaterial();
  void addFace(Face* face);
  void resend();

};

}

#endif

