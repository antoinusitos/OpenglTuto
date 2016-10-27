#ifndef DEF_IOMANAGER
#define DEF_IOMANAGER

#include <vector>
#include <string>
#include <fstream>

namespace OpenGLEngine
{

	using namespace std;

	class IOManager
	{
	public:
		static bool readFileToBuffer(string filePath, vector<unsigned char>& buffer);
	};

}

#endif