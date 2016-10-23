#include "GLSLProgram.h"
#include "Errors.h"

GLSLProgram::GLSLProgram() : programID(0), vertexShaderID(0), fragmentShaderID(0), numAttribute(0)
{
	
}


GLSLProgram::~GLSLProgram()
{

}

void GLSLProgram::CompileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath)
{
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	programID = glCreateProgram();

	// initialize the vertex shader
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0)
	{
		FatalError("Vertex shader failed to be created !");
	}

	// initialize the fragment shader
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderID == 0)
	{
		FatalError("fragment shader failed to be created !");
	}

	CompileShader(vertexShaderFilePath, vertexShaderID);
	CompileShader(fragmentShaderFilePath, fragmentShaderID);

}

void GLSLProgram::CompileShader(const string& filePath, GLuint& theVertexShaderID)
{
	// we open the file for read
	ifstream vertexFile(filePath);
	if (vertexFile.fail())
	{
		perror(filePath.c_str());
		FatalError("failed to open " + filePath);
	}

	string fileContent = "";
	string line;

	//read the file
	while (getline(vertexFile, line))
	{
		fileContent += line + "\n";
	}

	vertexFile.close();

	// send the string we get in the vertex file to opengl
	const char* contentPtr = fileContent.c_str();
	glShaderSource(theVertexShaderID, 1, &contentPtr, nullptr);

	glCompileShader(theVertexShaderID);

	// ***** shader error handling ***** //

	GLint success = 0;
	// try compiling the shader
	glGetShaderiv(theVertexShaderID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(theVertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(theVertexShaderID, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(theVertexShaderID); // Don't leak the shader.

		printf("%s\n", &(errorLog[0]));
		FatalError("shader " + filePath + " failed to compile");
	}

	// ***** end shader error handling ***** //
}

void GLSLProgram::LinkShaders()
{
	//Attach our shaders to our program
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	//Link our program
	glLinkProgram(programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		vector<char> errorLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(programID);
		//Don't leak shaders either.
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

		printf("%s\n", &(errorLog[0]));
		FatalError("shader failed to link");
	}

	//Always detach shaders after a successful link.
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	// delete the memory of the shader
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void GLSLProgram::AddAttribute(const string& attributeName)
{
	// link the program to the shader input
	glBindAttribLocation(programID, numAttribute, attributeName.c_str());
	numAttribute++;
}

GLuint GLSLProgram::GetUniformLocation(const string& uniformName)
{
	// get the uniform variable in the shader
	GLint location = glGetUniformLocation(programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		FatalError("Uniform " + uniformName + " not found in shader");
	}
	return location;
}

void GLSLProgram::Use()
{
	// tell the opengl to use the program
	glUseProgram(programID);
	// enable the input of the shader
	for (int i=0; i < numAttribute; ++i)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::Unuse()
{
	// tell the opengl to clear the program
	glUseProgram(0);
	// disable the input of the shader
	for (int i = 0; i < numAttribute; ++i)
	{
		glDisableVertexAttribArray(i);
	}
}
