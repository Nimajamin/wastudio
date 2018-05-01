#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

using namespace std;

namespace Gluten
{
  class Exception : public exception
  {
  private:
    string message;

  public:
    Exception(string message) throw()
    {
      this->message = message;
    }

    ~Exception() throw()
    {

    }

    const char* what() const throw()
    {
      return message.c_str();
    }
  };
}

#endif

