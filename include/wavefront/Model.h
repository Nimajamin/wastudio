#ifndef WAVEFRONT_MODEL_H
#define	WAVEFRONT_MODEL_H

#include <string>
#include <wavefront/auto_vector.h>

namespace Wavefront
{

class Vertex;
class Part;
class Animation;
class Material;
class Face;

/*
 * The root class representing a whole Wavefront Obj model.
 * Contains a hierarchy of the model data including vertices, animations and materials.
 * In general, this is the only class that the developer should be interacting with
 * unless working with specialized functionality such as collision etc...
 */
class Model
{
private:

  /*
   * The scale of the object used for drawing.
   */
  float scale;

  /*
   * RAII list to hold all the vertex normals loaded in from the object file (.obj).
   */
  auto_vector<Vertex> vertexNormals;

  /*
   * RAII list to hold all the parts loaded in from the object file (.obj).
   */
  auto_vector<Part> parts;

  /*
   * RAII list to hold all the animations loaded in from the animation file (.anm).
   */
  auto_vector<Animation> animations;

  /*
   * RAII list to hold all the materials loaded in from the material file (.mtl).
   */
  auto_vector<Material> materials;

  /*
   * The main setting up of the model from the obj file called from the constructors.
   */
  void _Model(std::string path);

  /*
   * Utility function to split a string into a std::vector.
   */
  void splitString(std::string& input, char splitter, std::vector<std::string>* output);

  /*
   * Utility function to get a specific word indexed from a split string.
   */
  std::string getSplitString(std::string& input, char splitter, int index);

  /*
   * Parse additional material files as instructed to by the object file.
   * These will need to be relative to where the .obj file is located.
   */
  void addMtl(std::string path);

public:
  static std::string getWavefrontVersion();

  /*
   * Constructor of Model to allow for the path in which to load the mesh from.
   */
  Model(std::string path);

  /*
   * Constructor of Model to allow for the path in which to load the mesh from and also
   * the scale which the model should be displayed with.
   */
  Model(std::string path, float scale);

  /*
   * Update the model with respect to the current frame for each animation. This could
   * be called during a seperate update loop so to keep animation frames at a consistant
   * speed within the game.
   */
  void update();

  /*
   * Draw the model using the current OpenGL context.
   * For example, in place of "glutSolidCube()".
   */
  void draw();

  /*
   * Draw the part of the model with the specified partName.
   */
  void drawPart(std::string partName);

  /*
   * Load an animation from the specified path and attach it to the model.
   * This can then be enabled when needed.
   */
  void addAnimation(std::string path);

  /*
   * Enable the animation with the given name, but only allow it to run through
   * one complete animation cycle.
   */
  void playAnimationOnce(std::string name);

  /*
   * Allow the animation with the specified name to effect the visual look of the
   * model.
   */
  void enableAnimation(std::string name);

  /*
   * Allow the animation with the specified index to effect the visual look of the
   * model.
   */
  void enableAnimation(int index);

  /*
   * Prevent the animation with the specified name from effecting the model.
   */
  void disableAnimation(std::string name);

  /*
   * Prevent all animations apart from the one with the specified name from
   * having an effect on the model.
   */
  void disableAllAnimationsBut(std::string name);

  /*
   * Prevent any of the loaded animations from having an effect on the model.
   */
  void disableAllAnimations();

  /*
   * Specify that the model with the given name should be drawn in a red shade.
   * This is useful for making visual selections of certain parts.
   */
  void highlightPart(std::string part);

  /*
   * Returns a pointer to all parts in the model.
   */
  auto_vector<Part>* getParts();

  /*
   * Returns a pointer to the part of the model as specified by the part's name.
   */
  Part* getPart(std::string name);

  /*
   * Returns a pointer to all the animations which have been loaded into the model.
   */
  auto_vector<Animation>* getAnimations();

  /*
   * Returns the scale of the model initially set by the constructor.
   */
  float getScale();

  /*
   * All the faces in the model which collide with the given cube will be added
   * into the specified std::vector.
   * This is a relatively expensive procedure so should ideally only be called once
   * per game loop and then the faces returned should be rechecked once position
   * adjustments have been made.
   */
  void getCollidingFaces(Vertex* center, Vertex* halfsize, std::vector<Face*>* collidingFaces);
  
};

}

#endif

