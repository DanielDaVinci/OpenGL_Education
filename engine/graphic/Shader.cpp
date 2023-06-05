#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	setVertex(vertexPath);
	setFragment(fragmentPath);
	setProgram();
}

void Shader::setProgram()
{
	if (program != 0)
		glDeleteProgram(program);

	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	GLint success;
	GLchar infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}
}

GLuint Shader::getProgram() const
{
	return program;
}

string Shader::getVertexPath() const
{
	return vertexPath;
}

string Shader::getFragmentPath() const
{
	return fragmentPath;
}

void Shader::setVertex(const GLchar* path)
{
	vertexPath = (path == nullptr) ? "" : path;

	string vertexCode = getCodeFromFile(path);

	vertexShader = getShader(GL_VERTEX_SHADER, vertexCode.c_str());
}

void Shader::setFragment(const GLchar* path)
{
	fragmentPath = (path == nullptr) ? "" : path;

	string fragmentCode = getCodeFromFile(path);

	fragmentShader = getShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());
}

void Shader::Use()
{
	glUseProgram(program);
}

GLuint Shader::getUniformLocation(const GLchar* name)
{
	return glGetUniformLocation(program, name);
}

void Shader::setUniform(const GLchar* name, const GLfloat value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform(const GLchar* name, const GLint value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform(const GLchar* name, const GLuint value)
{
	glUniform1ui(getUniformLocation(name), value);
}

void Shader::setUniform(const GLchar* name, const GLfloat* value)
{	
	glUniform4fv(getUniformLocation(name), sizeof(value) / sizeof(GLfloat), value);
}

void Shader::setUniform(const GLchar* name, glm::vec3 value)
{
	glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setUniform(const GLchar* name, glm::mat4 value)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

string Shader::getCodeFromFile(const GLchar* path)
{
	string shaderCode;
	ifstream shaderFile;

	shaderFile.exceptions(ifstream::badbit);
	try
	{
		shaderFile.open((path == nullptr) ? "" : path);

		stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		shaderCode = shaderStream.str();
	}
	catch (istream::failure e)
	{
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
	}

	return shaderCode;
}

GLuint Shader::getShader(GLenum type, const GLchar* source)
{
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << endl << infoLog << endl;
	}

	return shader;
}
