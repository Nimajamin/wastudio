#ifndef FUNCTION_H
#define FUNCTION_H

#include <gluten/MessageBox.h>
#include <gluten/Core.h>

namespace Gluten
{
  class MessageBox;
  class Core;

  class Function
  {
  private:

  public:
    virtual ~Function(){}
    virtual void execute() = 0;

  };

  template<typename T> class GenericFunction : public Function
  {
  private:
    T* instance;
    void (T::*funcPtr)();

  public:
    GenericFunction(T* instance, void (T::*funcPtr)())
    {
      this->instance = instance;
      this->funcPtr = funcPtr;
    }

    virtual void execute()
    {
      try
      {
        (instance->*funcPtr)();
      }
      catch(exception& e)
      {
        cout << "Exception: " << e.what() << endl;
        new MessageBox(Core::getCore(), string("Exception: ") + e.what());
      }
    }
  };

  template<typename T> class ParameterFunction : public Function
  {
  private:
    T* instance;
    void (T::*funcPtr)(void*);
    void* parameter;

  public:
    ParameterFunction(T* instance, void (T::*funcPtr)(void*), void* parameter)
    {
      this->instance = instance;
      this->funcPtr = funcPtr;
      this->parameter = parameter;
    }

    virtual void execute()
    {
      try
      {
        (instance->*funcPtr)(parameter);
      }
      catch(exception& e)
      {
        cout << "Exception: " << e.what() << endl;
        new MessageBox(Core::getCore(), string("Exception: ") + e.what());
      }
    }
  };
}

#endif

