#include <wavefront.h>

namespace Wavefront
{

void MaterialGroup::draw(bool highlighted)
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glColor3f(1.0, 1.0, 1.0);

  if(material->getTexture() == NULL)
  {
    Texture::unbind();
    glEnableClientState(GL_COLOR_ARRAY);
  }
  else
  {
    material->getTexture()->bind();
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  }

  if(highlighted == true)
  {
    glDisableClientState(GL_COLOR_ARRAY);
    glColor3f(1.0, 0.0, 0.0);
  }

  glBindBufferARB(GL_ARRAY_BUFFER_ARB, _normalBuffer);
  glNormalPointer(GL_FLOAT, 0, 0);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, _colorBuffer);
  glColorPointer(3, GL_FLOAT, 0, 0);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, _coordBuffer);
  glTexCoordPointer(3, GL_FLOAT, 0, 0);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, _vertexBuffer);
  glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);

  glDrawArrays(GL_TRIANGLES, 0, faces.size() * 3);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

Material* MaterialGroup::getMaterial()
{
  return material;
}

void MaterialGroup::addFace(Face* face)
{
  faces.push_back(face);
  material = face->getMaterial();
}

void MaterialGroup::resend()
{
  std::vector<float> verts;
  std::vector<float> colors;
  std::vector<float> normals;
  std::vector<float> coords;

  for(int i = 0; i < faces.size(); i++)
  {
    verts.push_back(faces.at(i)->getA()->getX());
    verts.push_back(faces.at(i)->getA()->getY());
    verts.push_back(faces.at(i)->getA()->getZ());
    colors.push_back(material->getR());
    colors.push_back(material->getG());
    colors.push_back(material->getB());
    normals.push_back(faces.at(i)->getNa()->getX());
    normals.push_back(faces.at(i)->getNa()->getY());
    normals.push_back(faces.at(i)->getNa()->getZ());

    if(faces.at(i)->getTa() != NULL)
    {
      coords.push_back(faces.at(i)->getTa()->getX());
      coords.push_back(-faces.at(i)->getTa()->getY());
      coords.push_back(faces.at(i)->getTa()->getZ());
    }

    verts.push_back(faces.at(i)->getB()->getX());
    verts.push_back(faces.at(i)->getB()->getY());
    verts.push_back(faces.at(i)->getB()->getZ());
    colors.push_back(material->getR());
    colors.push_back(material->getG());
    colors.push_back(material->getB());
    normals.push_back(faces.at(i)->getNb()->getX());
    normals.push_back(faces.at(i)->getNb()->getY());
    normals.push_back(faces.at(i)->getNb()->getZ());

    if(faces.at(i)->getTb() != NULL)
    {
      coords.push_back(faces.at(i)->getTb()->getX());
      coords.push_back(-faces.at(i)->getTb()->getY());
      coords.push_back(faces.at(i)->getTb()->getZ());
    }

    verts.push_back(faces.at(i)->getC()->getX());
    verts.push_back(faces.at(i)->getC()->getY());
    verts.push_back(faces.at(i)->getC()->getZ());
    colors.push_back(material->getR());
    colors.push_back(material->getG());
    colors.push_back(material->getB());
    normals.push_back(faces.at(i)->getNc()->getX());
    normals.push_back(faces.at(i)->getNc()->getY());
    normals.push_back(faces.at(i)->getNc()->getZ());

    if(faces.at(i)->getTc() != NULL)
    {
      coords.push_back(faces.at(i)->getTc()->getX());
      coords.push_back(-faces.at(i)->getTc()->getY());
      coords.push_back(faces.at(i)->getTc()->getZ());
    }
  }

  glGenBuffersARB(1, &_vertexBuffer);
  vertexBuffer.reset(&_vertexBuffer, std::bind(MaterialGroup::freeBuffer, &_vertexBuffer));
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, _vertexBuffer);
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, colors.size()*sizeof(float), &verts[0], GL_STATIC_DRAW_ARB);

  glGenBuffersARB(1, &_normalBuffer);
  normalBuffer.reset(&_normalBuffer, std::bind(MaterialGroup::freeBuffer, &_normalBuffer));
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, _normalBuffer);

  if(normals.size() > 0)
  {
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, colors.size()*sizeof(float), &normals[0], GL_STATIC_DRAW_ARB);
  }

  glGenBuffersARB(1, &_colorBuffer);
  colorBuffer.reset(&_colorBuffer, std::bind(MaterialGroup::freeBuffer, &_colorBuffer));
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, _colorBuffer);

  if(colors.size() > 0)
  {
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, colors.size()*sizeof(float), &colors[0], GL_STATIC_DRAW_ARB);
  }

  glGenBuffersARB(1, &_coordBuffer);
  coordBuffer.reset(&_coordBuffer, std::bind(MaterialGroup::freeBuffer, &_coordBuffer));
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, _coordBuffer);

  if(coords.size() > 0)
  {
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, coords.size()*sizeof(float), &coords.at(0), GL_STATIC_DRAW_ARB);
  }
}

void MaterialGroup::freeBuffer(GLuint* buffer)
{
  glDeleteBuffersARB(1, buffer);
}

}
