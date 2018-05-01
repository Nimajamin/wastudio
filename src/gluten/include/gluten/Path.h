#ifndef WAS_PATH_H
#define WAS_PATH_H

#include <string>

class Path
{
private:
	static std::string path;

public:
	static void initialize(int argc, char* argv[]);
	static std::string getPath();

};

#endif

