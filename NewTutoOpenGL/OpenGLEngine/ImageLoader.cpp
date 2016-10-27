#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"

namespace OpenGLEngine
{

	GLTexture ImageLoader::LoadPNG(string filePath)
	{
		// create a gl texture and initialize all its fields to 0
		GLTexture texture = {};

		// input data to decodePNG, which we load from a file
		vector<unsigned char> out;
		// output data from decodePNG, which is the pixel data four our texture
		vector<unsigned char> in;

		unsigned long width;
		unsigned long height;

		// read the image file contents into a buffer
		if (IOManager::readFileToBuffer(filePath, in) == false)
		{
			FatalError("Failed to load png file to buffer!");
		}

		// decode the .png format into an array of pixels
		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
		if (errorCode != 0)
		{
			FatalError("decodePNG failed with error : " + to_string(errorCode));
		}

		// generate the openGL texture object
		glGenTextures(1, &(texture.id));

		// bind the texture object
		glBindTexture(GL_TEXTURE_2D, texture.id);
		// upload the pixels to the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		// set some texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//generate the mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);

		// unbind the texture
		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		// return a copy of the texture data
		return texture;

	}

}