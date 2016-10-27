#ifndef DEF_GLSLPROGRAM
#define DEF_GLSLPROGRAM

#include "UserIncludes.h"

#include "glew.h"
#include "SDL.h"

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void CompileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath);

	void LinkShaders();

	void AddAttribute(const string& attributeName);

	GLint GetUniformLocation(const string& uniformName);

	void Use();
	void Unuse();

private:

	int numAttribute;

	void CompileShader(const string& filePath, GLuint& theVertexShaderID);

	GLuint programID;

	GLuint vertexShaderID;
	GLuint fragmentShaderID;
};

#endif