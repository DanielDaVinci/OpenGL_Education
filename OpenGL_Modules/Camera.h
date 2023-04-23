#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 angle;
	glm::vec3 scale;

	GLfloat FOV;

	GLuint screenWidth, screenHeight;
public:
	Camera(GLuint screenWidth, GLuint screenHeight, GLfloat FOV, glm::vec3 position = {0.0f, 0.0f, 0.0f}, glm::vec3 angle = {0.0f, 0.0f, 0.0f});

	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	void setX(GLfloat x);
	GLfloat getX();
	void setY(GLfloat y);
	GLfloat getY();
	void setZ(GLfloat z);
	GLfloat getZ();

	void setAngle(glm::vec3 angle);
	glm::vec3 getAngle();
	void setPitch(GLfloat angle);
	GLfloat getPitch();
	void setYaw(GLfloat angle);
	GLfloat getYaw();
	void setRoll(GLfloat angle);
	GLfloat getRoll();

	void setScale(glm::vec3 scale);
	glm::vec3 getScale();

	void setFOV(GLfloat FOV);
	GLfloat getFOV();

	void setScreenWidth(GLuint screenWidth);
	GLuint getScreenWidth();
	void setScreenHeight(GLuint screenHeight);
	GLuint getScreenHeight();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	glm::vec3 getFrontDirection();
	glm::vec3 getUpDirection();
	glm::vec3 getRightDirection();
};

