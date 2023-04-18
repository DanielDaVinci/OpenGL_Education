#pragma once

#include <iostream>
#include <string>

#define GLEW_STATIC
#include "GL/glew.h"
#include "SOIL/SOIL.h"

using namespace std;

enum ColorFormat
{
	AUTO,
	LUMIN,
	LUMIN_ALPHA,
	RGB,
	RGBA
};

class Texture
{
private:

	GLuint texture;
	GLenum type;

	string path;

	int width = 0;
	int height = 0;

public:
	Texture(GLenum type, const GLchar* path = nullptr, ColorFormat format = ColorFormat::RGB);

	GLuint getTexture() const;
	GLenum getType() const;
	string getPath() const;
	int getWidth() const;
	int getHeight() const;

	void setImage(const GLchar* path, ColorFormat format = ColorFormat::RGB);

	void setParameter(GLenum name, GLint value);
	void setParameter(GLenum name, const GLfloat* value);

	void Bind();
	void UnBind();
};