#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "../graphic/Shader.h"

class Frame
{
private:

	GLuint width, height;

	GLuint frameBuffer;
	GLuint colorBuffer;

	GLuint RBO;
	GLuint VAO, VBO;

public:

	Frame(GLuint width, GLuint height);

	void Bind(GLint value = 1);
	void Draw(Shader shader);

	void Resize(GLuint width, GLuint height);

	GLuint getTextureID();

private:

	void genColorBuffer(GLuint width, GLuint height);
	void genRBO(GLuint width, GLuint height);
	void genFrameTexture();

};

