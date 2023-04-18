#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#define GLEW_STATIC
#include "GL/glew.h"

using namespace std;

class Shader
{
private:

	GLuint program = 0;

	string vertexPath;
	string fragmentPath;

	GLuint vertexShader;
	GLuint fragmentShader;

public:
	Shader(const GLchar* vertexPath = nullptr, const GLchar* fragmentPath = nullptr);
	
	GLuint getProgram() const;
	string getVertexPath() const;
	string getFragmentPath() const;

	void setVertex(const GLchar* path);
	void setFragment(const GLchar* path);
	void setProgram();

	void Use();
private:
	static string getCodeFromFile(const GLchar* path);
	static GLuint getShader(GLenum type, const GLchar* source);
};

