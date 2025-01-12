#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

class FShader;

class RFrame
{
private:
	GLuint width, height;

	GLuint frameBuffer;
	GLuint colorBuffer;

	GLuint RBO;
	GLuint VAO, VBO;

public:

	RFrame(GLuint width, GLuint height);

	void Bind(GLint value = 1);
	void Draw(FShader shader);

	void Resize(GLuint width, GLuint height);

	GLuint getTextureID();

private:

	void genColorBuffer(GLuint width, GLuint height);
	void genRBO(GLuint width, GLuint height);
	void genFrameTexture();

};

