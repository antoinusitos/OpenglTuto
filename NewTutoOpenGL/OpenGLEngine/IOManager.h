#ifndef DEF_IOMANAGER
#define DEF_IOMANAGER

#include "UserIncludes.h"

class IOManager
{
public:
	static bool readFileToBuffer(string filePath, vector<unsigned char>& buffer);
};

#endif