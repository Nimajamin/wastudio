#include <wavefront.h>

namespace Wavefront
{

Face::Face(Vertex a, Vertex b, Vertex c)
{
  this->a = a;
  this->b = b;
  this->c = c;
  calcNormal(&a, &b, &c, &na);
  na.x = -na.x;
  na.y = -na.y;
  na.z = -na.z;
  nb = na;
  nc = na;
  this->material = NULL;
  hasTc = false;
  hasN = false;
  //isQuad = false;
}

/*
Face::Face(Vertex a, Vertex b, Vertex c, Vertex d)
{
  this->a = a;
  this->b = b;
  this->c = c;
  this->d = d;
  calcNormal(&a, &b, &c, &na);
  na.x = -na.x;
  na.y = -na.y;
  na.z = -na.z;
  nb = na;
  nc = na;
  this->material = NULL;
  hasTc = false;
  hasN = false;
  isQuad = true;
}
*/

Face::~Face()
{

}

/*
void Face::draw(bool highlighted)
{
  if(highlighted == true)
  {
    glColor3f(1, 0, 0);
  }
  else
  {
    if (material == NULL)
    {
      Texture::unbind();
      glColor3f(0.5, 0.5, 0.5);
    }
    else
    {
      glColor3f(material->getR(), material->getG(), material->getB());

      if(material->getTexture() != NULL)
      {
        material->getTexture()->bind();
      }
      else
      {
        Texture::unbind();
      }
    }
  }

  if(isQuad)
  {
    glBegin(GL_QUADS);
    glNormal3f(na.getX()*-1, na.getY()*-1, na.getZ()*-1);

    if(hasTc)
    {
      glTexCoord2d(ta.getX(), ta.getY());
      glVertex3f(a.getX(), a.getY(), a.getZ());
      glTexCoord2d(tb.getX(), tb.getY());
      glVertex3f(b.getX(), b.getY(), b.getZ());
      glTexCoord2d(tc.getX(), tc.getY());
      glVertex3f(c.getX(), c.getY(), c.getZ());
      glTexCoord2d(td.getX(), td.getY());
      glVertex3f(d.getX(), d.getY(), d.getZ());
    }
    else
    {
      glVertex3f(a.getX(), a.getY(), a.getZ());
      glVertex3f(b.getX(), b.getY(), b.getZ());
      glVertex3f(c.getX(), c.getY(), c.getZ());
      glVertex3f(d.getX(), d.getY(), d.getZ());
    }

    glEnd();
  }
  else
  {
    glBegin(GL_TRIANGLES);
    glNormal3f(na.getX()*-1, na.getY()*-1, na.getZ()*-1);

    if(hasTc)
    {
      glTexCoord2d(ta.getX(), ta.getY());
      glVertex3f(a.getX(), a.getY(), a.getZ());
      glTexCoord2d(tb.getX(), tb.getY());
      glVertex3f(b.getX(), b.getY(), b.getZ());
      glTexCoord2d(tc.getX(), tc.getY());
      glVertex3f(c.getX(), c.getY(), c.getZ());
    }
    else
    {
      glVertex3f(a.getX(), a.getY(), a.getZ());
      glVertex3f(b.getX(), b.getY(), b.getZ());
      glVertex3f(c.getX(), c.getY(), c.getZ());
    }

    glEnd();
  }
}
*/

Vertex* Face::getNa()
{
  return &na;
}

Vertex* Face::getNb()
{
  return &nb;
}

Vertex* Face::getNc()
{
  return &nc;
}

Vertex* Face::getTa()
{
  return &ta;
}
Vertex* Face::getTb()
{
  return &tb;
}
Vertex* Face::getTc()
{
  return &tc;
}

Vertex* Face::getA()
{
  return &a;
}

Vertex* Face::getB()
{
  return &b;
}

Vertex* Face::getC()
{
  return &c;
}

float Face::getMaxX()
{
  float maxX = a.getX();

  if(b.getX() > maxX)
  {
    maxX = b.getX();
  }

  if(c.getX() > maxX)
  {
    maxX = c.getX();
  }

  return maxX;
}

float Face::getMinX()
{
  float minX = a.getX();

  if(b.getX() < minX)
  {
    minX = b.getX();
  }

  if(c.getX() < minX)
  {
    minX = c.getX();
  }

  return minX;
}

float Face::getMaxY()
{
  float maxY = a.getY();

  if(b.getY() > maxY)
  {
    maxY = b.getY();
  }

  if(c.getX() > maxY)
  {
    maxY = c.getY();
  }

  return maxY;
}

float Face::getMinY()
{
  float minY = a.getY();

  if(b.getY() < minY)
  {
    minY = b.getY();
  }

  if(c.getY() < minY)
  {
    minY = c.getY();
  }

  return minY;
}

float Face::getMaxZ()
{
  float maxZ = a.getZ();

  if(b.getZ() > maxZ)
  {
    maxZ = b.getZ();
  }

  if(c.getZ() > maxZ)
  {
    maxZ = c.getZ();
  }

  return maxZ;
}

float Face::getMinZ()
{
  float minZ = a.getZ();

  if(b.getZ() < minZ)
  {
    minZ = b.getZ();
  }

  if(c.getZ() < minZ)
  {
    minZ = c.getZ();
  }

  return minZ;
}

void Face::setMaterial(Material* material)
{
  this->material = material;
}

void Face::ReduceToUnit(float vector[3])
{
  float length = 0;

  length = (float)sqrt((vector[0]*vector[0]) + (vector[1]*vector[1]) + (vector[2]*vector[2]));

  if(length == 0.0f)
  {
    length = 1.0f;
  }

  vector[0] /= length;
  vector[1] /= length;
  vector[2] /= length;
}

void Face::calcNormal(float v[3][3], float out[3])
{
  float v1[3],v2[3];
  static const int x = 0;
  static const int y = 1;
  static const int z = 2;

  v1[x] = v[0][x] - v[1][x];
  v1[y] = v[0][y] - v[1][y];
  v1[z] = v[0][z] - v[1][z];

  v2[x] = v[1][x] - v[2][x];
  v2[y] = v[1][y] - v[2][y];
  v2[z] = v[1][z] - v[2][z];

  out[x] = v1[y]*v2[z] - v1[z]*v2[y];
  out[y] = v1[z]*v2[x] - v1[x]*v2[z];
  out[z] = v1[x]*v2[y] - v1[y]*v2[x];

  ReduceToUnit(out);
}

void Face::calcNormal(Vertex a, Vertex b, Vertex c, Vertex* result)
{
  float v[3][3] = { 0 };
  float o[3] = { 0 };

  v[0][0] = a.getX();
  v[0][1] = a.getY();
  v[0][2] = a.getZ();

  v[1][0] = b.getX();
  v[1][1] = b.getY();
  v[1][2] = b.getZ();

  v[2][0] = c.getX();
  v[2][1] = c.getY();
  v[2][2] = c.getZ();

  calcNormal(v, o);

  result->setX(-o[0]);
  result->setY(-o[1]);
  result->setZ(-o[2]);
}

/*
void Face::setTextureCoords(Vertex ta, Vertex tb, Vertex tc, Vertex td)
{
  this->ta = ta;
  this->tb = tb;
  this->tc = tc;
  this->td = td;
  hasTc = true;
}
*/

void Face::setTextureCoords(Vertex ta, Vertex tb, Vertex tc)
{
  this->ta = ta;
  this->tb = tb;
  this->tc = tc;
  hasTc = true;
}

void Face::setNormals(Vertex a, Vertex b, Vertex c)
{
  this->na = a;
  this->nb = b;
  this->nc = c;
  hasN = true;
}

Material* Face::getMaterial()
{
  return material;
}

bool Face::isColliding(Vertex* center, Vertex* halfsize)
{
  float _center[3] = { 0, 0, 0 };
  float _half[3] = { 0, 0, 0 };
  float _tri[3][3];

  _center[0] = center->getX();
  _center[1] = center->getY();
  _center[2] = center->getZ();

  _half[0] = halfsize->getX();
  _half[1] = halfsize->getY();
  _half[2] = halfsize->getZ();

  _tri[0][0] = a.getX();
  _tri[0][1] = a.getY();
  _tri[0][2] = a.getZ();
  _tri[1][0] = b.getX();
  _tri[1][1] = b.getY();
  _tri[1][2] = b.getZ();
  _tri[2][0] = c.getX();
  _tri[2][1] = c.getY();
  _tri[2][2] = c.getZ();

  if(triBoxOverlap(_center, _half, _tri) == 1)
  {
    return true;
  }

  return false;
}

}

