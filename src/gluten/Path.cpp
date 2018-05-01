#include <gluten/Path.h>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <stdio.h>
#endif

std::string Path::path;

void Path::initialize(int argc, char* argv[])
{
#ifdef _WIN32
  char strExePath [MAX_PATH];

  GetModuleFileName (NULL, strExePath, MAX_PATH);
  path = strExePath;
  path = path.substr(0, path.find_last_of("\\"));
  path = path.substr(0, path.find_last_of("\\"));
#else
  FILE* process = NULL;
  std::string command;
  char buffer[8];

  command = "cd `dirname \\`which " + std::string(argv[0]) + "\\``; cd ..; pwd | tr -d '\n'";
  process = popen(command.c_str(), "r");

  if(process == NULL)
  {
    throw std::exception();
  }

  while(fgets(buffer, 7, process) != NULL)
  {
    path += buffer;
  }

  pclose(process);
#endif
}

std::string Path::getPath()
{
  return Path::path;
}

