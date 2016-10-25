#include "IOManager.h"

bool IOManager::readFileToBuffer(string filePath, vector<unsigned char>& buffer)
{
	// load the file and open it
	ifstream file(filePath, ios::binary);
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}

	// seek to the end
	file.seekg(0, ios::end);

	// get the file size
	int fileSize = file.tellg();
	// go to the beggining of the file
	file.seekg(0, ios::beg);

	// reduce the file size by any header bytes that might be present
	fileSize -= file.tellg();

	// allocate memory for the file
	buffer.resize(fileSize);
	//get the address of the first item 
	file.read((char *)&(buffer[0]), fileSize);
	file.close();

	return true;

}
