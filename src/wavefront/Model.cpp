#include <wavefront.h>

#include <sstream>

using namespace std;

namespace Wavefront
{

/*********************************************************************
 * The class constructor for the model.
 *
 * The top level of the model hierarchy. From the specified path, all
 * the data is read and a model is constructed in memory ready for
 * displaying. The scale can be set here which is important because
 * this size also changes the loaded in animation transforms in order
 * to work with the requested size.
 *
 * @param path The path of the model to load.
 * @param scale The visual size modifier for the model.
 *********************************************************************/
Model::Model(string path, float scale)
{
  this->scale = scale;
  _Model(path);
}

/*********************************************************************
 * The class constructor for the model.
 *
 * The top level of the model hierarchy. From the specified path, all
 * the data is read and a model is constructed in memory ready for
 * displaying.
 *
 * @param path The path of the model to load.
 *********************************************************************/
Model::Model(string path)
{
  this->scale = 1;
  _Model(path);
}

/*********************************************************************
 * The main loading routine.
 *
 * This should only ever be called by the constructors to perform the
 * main loading functionality of the model (in order to reduce the
 * amount of duplicate code). This function should prepare everything
 * needed for the model to be fully initialized. It performs the main
 * parsing of the model file.
 *
 * @param path The path of the model to load.
 *********************************************************************/
void Model::_Model(string path)
{
  Face* face = NULL;
  vector<Vertex> vertexes;
  vector<Vertex> textureVertexes;
  Material* material = NULL;
  Part* part = NULL;
  ifstream file(path.c_str());
  vector<string> strings;
  string line;
  string mtlName;

  materials.add(new Material("Default"));
  material = materials.at(0);
  mtlName = "Default";
  glewInit();

  if (file.is_open() == false)
  {
    throw WavefrontException("Failed to open '" + path + "'");
  }
  
  for(int i = 0; i < path.length(); i++)
  {
    if(path.at(i) == '\\')
    {
      path.at(i) = '/';
    }
  }

  while (file.eof() == false)
  {
    getline(file, line);
    splitString(line, ' ', &strings);

    if (strings.size() > 0)
    {
      if (strings.at(0) == "mtllib")
      {
        addMtl(path.substr(0, path.find_last_of('/')) + "/" + strings.at(1));
      }
      else if (strings.at(0) == "usemtl")
      {
        if(strings.size() < 2)
        {
          mtlName = "Default";
        }
        else
        {
          mtlName = strings.at(1);
        }

        for(int materialIndex = 0; materialIndex < materials.size(); materialIndex++)
        {
          if(materials.at(materialIndex)->getName() == mtlName)
          {
            material = materials.at(materialIndex);
          }
        }
      }
      else if (strings.at(0) == "o" || strings.at(0) == "g")
      {
        parts.add(new Part(this, strings.at(1)));
        part = parts.at(parts.size() - 1);
      }
      else if (strings.at(0) == "vt")
      {
        textureVertexes.push_back(Vertex(atof(strings.at(1).c_str())*scale, atof(strings.at(2).c_str())*scale, 0));
      }
      else if (strings.at(0) == "v")
      {
        vertexes.push_back(Vertex(atof(strings.at(1).c_str())*scale, atof(strings.at(2).c_str())*scale, atof(strings.at(3).c_str())*scale));
      }
      else if (strings.at(0) == "vn")
      {
        vertexNormals.add(new Vertex(atof(strings.at(1).c_str()), atof(strings.at(2).c_str()), atof(strings.at(3).c_str())));
      }
      else if (strings.at(0) == "f")
      {
        if(part == NULL)
        {
          parts.add(new Part(this, "Default"));
          part = parts.at(parts.size() - 1);
        }

        if (strings.size() > 4)
        {
          face = new Face(Vertex(vertexes.at(atof(getSplitString(strings.at(1), '/', 0).c_str()) - 1)),
                          Vertex(vertexes.at(atof(getSplitString(strings.at(2), '/', 0).c_str()) - 1)),
                          Vertex(vertexes.at(atof(getSplitString(strings.at(3), '/', 0).c_str()) - 1)));
          part->addFace(face);

          if(textureVertexes.size() > 0)
          {
            if(getSplitString(strings.at(1), '/', 1) != "")
            {
              face->setTextureCoords(
                Vertex(textureVertexes.at(atof(getSplitString(strings.at(1), '/', 1).c_str()) - 1)),
                Vertex(textureVertexes.at(atof(getSplitString(strings.at(2), '/', 1).c_str()) - 1)),
                Vertex(textureVertexes.at(atof(getSplitString(strings.at(3), '/', 1).c_str()) - 1)));
            }
          }

          if(vertexNormals.size() > 0)
          {
            face->setNormals(
                  Vertex(vertexNormals.at(atof(getSplitString(strings.at(1), '/', 2).c_str()) - 1)),
                  Vertex(vertexNormals.at(atof(getSplitString(strings.at(2), '/', 2).c_str()) - 1)),
                  Vertex(vertexNormals.at(atof(getSplitString(strings.at(3), '/', 2).c_str()) - 1)));
          }

          part->getFaces()->at(part->getFaces()->size() - 1)->setMaterial(material);

          face = new Face(Vertex(vertexes.at(atof(getSplitString(strings.at(3), '/', 0).c_str()) - 1)),
                          Vertex(vertexes.at(atof(getSplitString(strings.at(4), '/', 0).c_str()) - 1)),
                          Vertex(vertexes.at(atof(getSplitString(strings.at(1), '/', 0).c_str()) - 1)));
          part->addFace(face);

          if(textureVertexes.size() > 0)
          {
            if(getSplitString(strings.at(1), '/', 1) != "")
            {
              face->setTextureCoords(
                Vertex(textureVertexes.at(atof(getSplitString(strings.at(3), '/', 1).c_str()) - 1)),
                Vertex(textureVertexes.at(atof(getSplitString(strings.at(4), '/', 1).c_str()) - 1)),
                Vertex(textureVertexes.at(atof(getSplitString(strings.at(1), '/', 1).c_str()) - 1)));
            }
          }

          if(vertexNormals.size() > 0)
          {
            face->setNormals(
                  Vertex(vertexNormals.at(atof(getSplitString(strings.at(3), '/', 2).c_str()) - 1)),
                  Vertex(vertexNormals.at(atof(getSplitString(strings.at(4), '/', 2).c_str()) - 1)),
                  Vertex(vertexNormals.at(atof(getSplitString(strings.at(1), '/', 2).c_str()) - 1)));
          }

          part->getFaces()->at(part->getFaces()->size() - 1)->setMaterial(material);
        }
        else
        {
          face = new Face(new Vertex(vertexes.at(atof(getSplitString(strings.at(1), '/', 0).c_str()) - 1)),
                          new Vertex(vertexes.at(atof(getSplitString(strings.at(2), '/', 0).c_str()) - 1)),
                          new Vertex(vertexes.at(atof(getSplitString(strings.at(3), '/', 0).c_str()) - 1)));

          part->addFace(face);

          if(textureVertexes.size() > 0)
          {
            if(getSplitString(strings.at(1), '/', 1) != "")
            {
              face->setTextureCoords(
                new Vertex(textureVertexes.at(atof(getSplitString(strings.at(1), '/', 1).c_str()) - 1)),
                new Vertex(textureVertexes.at(atof(getSplitString(strings.at(2), '/', 1).c_str()) - 1)),
                new Vertex(textureVertexes.at(atof(getSplitString(strings.at(3), '/', 1).c_str()) - 1)));
            }
          }

          if(vertexNormals.size() > 0)
          {
            face->setNormals(
                  Vertex(vertexNormals.at(atof(getSplitString(strings.at(1), '/', 2).c_str()) - 1)),
                  Vertex(vertexNormals.at(atof(getSplitString(strings.at(2), '/', 2).c_str()) - 1)),
                  Vertex(vertexNormals.at(atof(getSplitString(strings.at(3), '/', 2).c_str()) - 1)));
          }

          part->getFaces()->at(part->getFaces()->size() - 1)->setMaterial(material);
        }
      }
    }
  }

  animations.add(new Animation(this));
}

void Model::addMtl(string path)
{
  Material* material = NULL;
  ifstream file(path.c_str());
  vector<string> strings;
  string line;

  if (file.is_open() == false)
  {
    throw WavefrontException("Failed to open '" + path + "'");
  }

  while (file.eof() == false)
  {
    getline(file, line);
    splitString(line, ' ', &strings);

    if (strings.size() > 0)
    {
      if (strings.at(0) == "newmtl")
      {
        if(strings.size() < 2) // Line is: newmtl
        {
          materials.add(new Material("Default"));
        }
        else // Line is: newmtl SomeName
        {
          materials.add(new Material(strings.at(1)));
        }

        material = materials.at(materials.size() - 1);
      }

      if (strings.at(0) == "map_Kd")
      {
        if(material == NULL)
        {
          materials.add(new Material("Default"));
          material = materials.at(materials.size() - 1);
        }

        material->setTexture(new Texture(path.substr(0, path.find_last_of("/")) + "/" + strings.at(1)));
      }

      if (strings.at(0) == "Kd")
      {
        if(material == NULL)
        {
          materials.add(new Material("Default"));
          material = materials.at(materials.size() - 1);
        }

        material->setR(atof(strings.at(1).c_str()));
        material->setG(atof(strings.at(2).c_str()));
        material->setB(atof(strings.at(3).c_str()));
      }
    }
  }
}

/*********************************************************************
 * Report to the animation hierarchy to iterate the frame.
 *
 * This only iterates frames. The handling of the frame limiter should
 * be implemented by the developer. Perhaps in a later version it will
 * be supported. Until then, use delta timing.
 *********************************************************************/
void Model::update()
{
  for (int animationIndex = 0; animationIndex < animations.size(); animationIndex++)
  {
    animations.at(animationIndex)->nextFrame();
  }
}
/*********************************************************************
 * Iterate through the parts list and draw each part.
 *
 * The parts are drawn but are translated to each animation just
 * before. Each part is split into material groups so that the OpenGL
 * VBO system can be used.
 *********************************************************************/
void Model::draw()
{
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  for (int partIndex = 0; partIndex < parts.size(); partIndex++)
  {
    parts.at(partIndex)->draw();
  }

  glDisable(GL_CULL_FACE);
}

/*********************************************************************
 * Draw the specified part.
 *
 * This is useful if the developer only wants to draw a certain part
 * of the model (such as a head). Rather than iterating through all
 * the parts, it will only draw the specified part.
 *
 * @param partName The name of the part to draw.
 *********************************************************************/
void Model::drawPart(std::string partName)
{
  for (int partIndex = 0; partIndex < parts.size(); partIndex++)
  {
    if(parts.at(partIndex)->getName() == partName)
    {
      parts.at(partIndex)->draw();
    }
  }
}

/*********************************************************************
 * Returns a pointer to the specified part.
 *
 * This is useful if the developer wants to modify a specific part of
 * the model. The data is exposed in this way.
 *
 * @param part The name of the part to obtain.
 * @returns A pointer to the specified part.
 *********************************************************************/
Part* Model::getPart(string part)
{
  for (int partIndex = 0; partIndex < parts.size(); partIndex++)
  {
    if(parts.at(partIndex)->getName() == part)
    {
      return parts.at(partIndex);
    }
  }

  throw WavefrontException("No part called '" + part + "' was found");
}

/*********************************************************************
 * Returns a pointer to a list containing all the parts of the model.
 *
 * This is useful if the developer wants access to the underlying
 * components of the model.
 *
 * @returns A pointer to a list containing all the parts of the model.
 *********************************************************************/
auto_vector<Part>* Model::getParts()
{
  return &parts;
}

/*********************************************************************
 * Returns a pointer to a list containing all the attached animations.
 *
 * This is useful if the developer wants access to the underlying
 * animations of the model.
 *
 * @returns A pointer to a list containing all the added animations.
 *********************************************************************/
auto_vector<Animation>* Model::getAnimations()
{
  return &animations;
}

/*********************************************************************
 * Utility function to split up a string.
 *
 * This function splits up a string and adds the parts of the string
 * to an array where they can be referenced by index. If there are
 * two or more splitter characters next to each other, the others are
 * ignored.
 *
 * @param input The string to be split.
 * @param splitter The character which splits up the string.
 * @param output The pointer to a list to add the split strings to.
 *********************************************************************/
void Model::splitString(string& input, char splitter, vector<string>* output)
{
  string current;

  output->clear();

  for (int charIndex = 0; charIndex < input.length(); charIndex++)
  {
    if (input[charIndex] != splitter)
    {
      current += input[charIndex];
    }
    else
    {
      if(current.length() > 0)
      {
        output->push_back(current);
        current = "";
      }
    }
  }

  if (current.length() > 0)
  {
    output->push_back(current);
  }
}

/*********************************************************************
 * Utility function to return a part of the split string.
 *
 * This function splits up a string and adds the parts of the string
 * to an array where they can be referenced by index. If there are
 * two or more splitter characters next to each other, the others are
 * ignored.
 *
 * @param input The string to be split.
 * @param splitter The character which splits up the string.
 * @param index The position of the part of the string to return.
 * @returns The part of a split string.
 *********************************************************************/
string Model::getSplitString(string& input, char splitter, int index)
{
  vector<string> output;
  string current;

  output.clear();
  current = "";

  for (int charIndex = 0; charIndex < input.length(); charIndex++)
  {
    if (input[charIndex] != splitter)
    {
      current += input[charIndex];
    }
    else
    {
      //if (current.length() > 0)
      //{
        output.push_back(current);
        current = "";
      //}
    }
  }

  if (current.length() > 0)
  {
    output.push_back(current);
  }

  if(index > output.size() - 1)
  {
    return "";
  }

  return output.at(index);
}

/*********************************************************************
 * Adds a new animation to the model for later use.
 *
 * This allows new animations to be stored in the model ready for
 * subsequent use. The animation is generated from the .anm file as
 * specified as a parameter.
 *
 * @param path The path of the .anm file to load.
 *********************************************************************/
void Model::addAnimation(string path)
{
  animations.add(new Animation(this, path));
}

/*********************************************************************
 * Play the specified animation once.
 *
 * Notifies the model that the specified animation should be played
 * but one it has reached the final frame, it should disable until
 * told to play again.
 *
 * @param name The name of the animation to play.
 *********************************************************************/
void Model::playAnimationOnce(string name)
{
  bool found = false;

  for(int animationIndex = 0; animationIndex < animations.size(); animationIndex++)
  {
    if(animations.at(animationIndex)->getName() == name)
    {
      animations.at(animationIndex)->setRepeating(false);
      animations.at(animationIndex)->setEnabled(true);
      found = true;
    }
  }

  if(found == false)
  {
    throw WavefrontException("No animation found with the name '" + name + "'");
  }
}

/*********************************************************************
 * Play the specified animation by name.
 *
 * Notifies the model that the specified animation should be played
 * in a loop until told to stop.
 *
 * @param name The name of the animation to play.
 *********************************************************************/
void Model::enableAnimation(string name)
{
  bool found = false;

  for(int animationIndex = 0; animationIndex < animations.size(); animationIndex++)
  {
    if(animations.at(animationIndex)->getName() == name)
    {
      animations.at(animationIndex)->setRepeating(true);
      animations.at(animationIndex)->setEnabled(true);
      found = true;
    }
  }

  if(found == false)
  {
    throw WavefrontException("No animation found with the name '" + name + "'");
  }
}

/*********************************************************************
 * Play the specified animation by index.
 *
 * Notifies the model that the specified animation should be played
 * in a loop until told to stop.
 *
 * @param index The position in the list of the animation to play.
 *********************************************************************/
void Model::enableAnimation(int index)
{
  if(animations.size() > index)
  {
    animations.at(index)->setEnabled(true);
  }
}

/*********************************************************************
 * Stop playing the specified animation.
 *
 * Notifies the model that the specified animation should be stopped.
 *
 * @param name The name of the animation to stop.
 *********************************************************************/
void Model::disableAnimation(string name)
{
  bool found = false;

  for(int animationIndex = 0; animationIndex < animations.size(); animationIndex++)
  {
    if(animations.at(animationIndex)->getName() == name)
    {
      animations.at(animationIndex)->setEnabled(false);
      found = true;
    }
  }

  if(found == false)
  {
    throw WavefrontException("No animation found with the name '" + name + "'");
  }
}

/*********************************************************************
 * Stop playing all the specified animations apart from...
 *
 * Notifies the model that all the animations should be stopped apart
 * from that with the given name.
 *
 * @param name The name of the animation to not stop.
 *********************************************************************/
void Model::disableAllAnimationsBut(string name)
{
  for(int animationIndex = 0; animationIndex < animations.size(); animationIndex++)
  {
    if(animations.at(animationIndex)->getName() == name)
    {
      animations.at(animationIndex)->setEnabled(true);
    }
    else
    {
      animations.at(animationIndex)->setEnabled(false);
    }
  }
}

/*********************************************************************
 * Stop playing all the specified animations.
 *
 * Notifies the model that all the animations should be stopped.
 *********************************************************************/
void Model::disableAllAnimations()
{
  for(int animationIndex = 0; animationIndex < animations.size(); animationIndex++)
  {
    animations.at(animationIndex)->setEnabled(false);
  }
}

/*********************************************************************
 * Highlight the part specified by name.
 *
 * This is useful for the Wavefront Animation Studio product in that
 * it allows for a visual notification to the user of which part has
 * been selected from the list.
 *
 * @param part The name of the part to highlight.
 *********************************************************************/
void Model::highlightPart(string part)
{
  for(int partIndex = 0; partIndex < parts.size(); partIndex++)
  {
    if(parts.at(partIndex)->getName() == part)
    {
      parts.at(partIndex)->setHighlighted(true);
    }
    else
    {
      parts.at(partIndex)->setHighlighted(false);
    }
  }
}

/*********************************************************************
 * Allows for specifying the current scale of the model.
 *
 * @returns The scale of the model.
 *********************************************************************/
float Model::getScale()
{
  return scale;
}

/*********************************************************************
 * Function to obtain a list of all the faces colliding with a box.
 *
 * This function allows the developer to obtain a list of all faces
 * which are colliding with the specified box. It uses the Separating
 * Axis method to obtain this information.
 *
 * @param center The center point of the box to test collising with.
 * @param halfsize The hald width of the box (from the center).
 * @param collisingFaces The pointer to a list to add the faces to.
 *********************************************************************/
void Model::getCollidingFaces(Vertex* center, Vertex* halfsize, std::vector<Face*>* collidingFaces)
{
  for(int i = 0; i < parts.size(); i++)
  {
    parts.at(i)->getCollidingFaces(center, halfsize, collidingFaces);
  }
}

std::string Model::getWavefrontVersion()
{
  return std::string(VERSION);
}

}
