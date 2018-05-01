#ifndef WAVEFRONT_WAVEFRONTEXCEPTION_H
#define WAVEFRONT_WAVEFRONTEXCEPTION_H

#include <exception>
#include <string>

namespace Wavefront
{

class WavefrontException : public std::exception
{
private:
  std::string message;

public:
  WavefrontException(std::string message) throw()
  {
    this->message = message;
  }

  ~WavefrontException() throw()
  {

  }

  const char* what() const throw()
  {
    return message.c_str();
  }

};

}

#endif

