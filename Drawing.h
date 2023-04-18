#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <vector>

using namespace std;

vector<GLfloat> getStarVertices(GLint edges, GLfloat maxR, GLfloat minR)
{
	vector<GLfloat> vertices;

	for (int i = 0; i < edges * 2; i++)
	{
		GLfloat angle1 = glm::radians(90.0f + (i * 360.0f / (edges * 2)));
		GLfloat x1 = glm::cos(angle1) * (i % 2 == 0 ? maxR : minR);
		GLfloat y1 = glm::sin(angle1) * (i % 2 == 0 ? maxR : minR);

		vertices.push_back(x1);
		vertices.push_back(y1);
		vertices.push_back(0.5f);

		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);

		vertices.push_back(x1 / (maxR * 2) + 0.5f);
		vertices.push_back(y1 / (maxR * 2) + 0.5f);


		GLfloat angle2 = glm::radians(90.0f + ((i + 1) * 360.0f / (edges * 2)));
		GLfloat x2 = glm::cos(angle2) * ((i + 1) % 2 == 0 ? maxR : minR);
		GLfloat y2 = glm::sin(angle2) * ((i + 1) % 2 == 0 ? maxR : minR);

		vertices.push_back(x2);
		vertices.push_back(y2);
		vertices.push_back(0.5f);

		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);

		vertices.push_back(x2 / (maxR * 2) + 0.5f);
		vertices.push_back(y2 / (maxR * 2) + 0.5f);


		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.5f);

		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);

		vertices.push_back(0.5f);
		vertices.push_back(0.5f);
	}

	for (int i = 0; i < edges * 2; i++)
	{
		GLfloat angle1 = glm::radians(90.0f + (i * 360.0f / (edges * 2)));
		GLfloat x1 = glm::cos(angle1) * (i % 2 == 0 ? maxR : minR);
		GLfloat y1 = glm::sin(angle1) * (i % 2 == 0 ? maxR : minR);

		vertices.push_back(x1);
		vertices.push_back(y1);
		vertices.push_back(-0.5f);

		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);

		vertices.push_back(x1 / (maxR * 2) + 0.5f);
		vertices.push_back(y1 / (maxR * 2) + 0.5f);


		GLfloat angle2 = glm::radians(90.0f + ((i + 1) * 360.0f / (edges * 2)));
		GLfloat x2 = glm::cos(angle2) * ((i + 1) % 2 == 0 ? maxR : minR);
		GLfloat y2 = glm::sin(angle2) * ((i + 1) % 2 == 0 ? maxR : minR);

		vertices.push_back(x2);
		vertices.push_back(y2);
		vertices.push_back(-0.5f);

		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);

		vertices.push_back(x2 / (maxR * 2) + 0.5f);
		vertices.push_back(y2 / (maxR * 2) + 0.5f);


		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(-0.5f);

		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);

		vertices.push_back(0.5f);
		vertices.push_back(0.5f);
	}

	for (int i = 0; i < edges * 2; i++)
	{
		GLfloat angle1 = glm::radians(90.0f + (i * 360.0f / (edges * 2)));
		GLfloat x1 = glm::cos(angle1) * (i % 2 == 0 ? maxR : minR);
		GLfloat y1 = glm::sin(angle1) * (i % 2 == 0 ? maxR : minR);

		GLfloat angle2 = glm::radians(90.0f + ((i + 1) * 360.0f / (edges * 2)));
		GLfloat x2 = glm::cos(angle2) * ((i + 1) % 2 == 0 ? maxR : minR);
		GLfloat y2 = glm::sin(angle2) * ((i + 1) % 2 == 0 ? maxR : minR);


		vertices.push_back(x1);
		vertices.push_back(y1);
		vertices.push_back(0.5f);

		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);

		vertices.push_back(0.0f);
		vertices.push_back(0.0f);

		vertices.push_back(x1);
		vertices.push_back(y1);
		vertices.push_back(-0.5f);

		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);

		vertices.push_back(0.0f);
		vertices.push_back(0.0f);

		vertices.push_back(x2);
		vertices.push_back(y2);
		vertices.push_back(0.5f);

		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);

		vertices.push_back(0.0f);
		vertices.push_back(0.0f);


		vertices.push_back(x2);
		vertices.push_back(y2);
		vertices.push_back(0.5f);

		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);

		vertices.push_back(0.0f);
		vertices.push_back(0.0f);

		vertices.push_back(x2);
		vertices.push_back(y2);
		vertices.push_back(-0.5f);

		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);

		vertices.push_back(0.0f);
		vertices.push_back(0.0f);

		vertices.push_back(x1);
		vertices.push_back(y1);
		vertices.push_back(-0.5f);

		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);

		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
	}

	return vertices;
}

vector<GLfloat> getCubeVertices()
{
	return {
		-0.5f, -0.5f,  0.5f,  -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,   0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,   0.5f,  1.5f,
		 0.5f, -0.5f,  0.5f,   0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,   0.5f,  1.5f,
		 0.5f,  0.5f,  0.5f,   1.5f,  0.5f,

		 0.5f, -0.5f,  0.5f,  -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,   0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,   0.5f,  1.5f,
		 0.5f, -0.5f, -0.5f,   0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,   0.5f,  1.5f,
		 0.5f,  0.5f, -0.5f,   1.5f,  0.5f,

		 0.5f, -0.5f, -0.5f,  -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,   0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,   0.5f,  1.5f,
		-0.5f, -0.5f, -0.5f,   0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,   0.5f,  1.5f,
		-0.5f,  0.5f, -0.5f,   1.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,  -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,   0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,   0.5f,  1.5f,
		-0.5f, -0.5f,  0.5f,   0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,   0.5f,  1.5f,
		-0.5f,  0.5f,  0.5f,   1.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,   0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,   0.5f,  1.5f,
		 0.5f,  0.5f,  0.5f,   0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,   0.5f,  1.5f,
		 0.5f,  0.5f, -0.5f,   1.5f,  0.5f,

		-0.5f, -0.5f,  0.5f,  -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,   0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,   0.5f,  1.5f,
		 0.5f, -0.5f,  0.5f,   0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,   0.5f,  1.5f,
		 0.5f, -0.5f, -0.5f,   1.5f,  0.5f,
	};
}