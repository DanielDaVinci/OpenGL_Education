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

	void setPosition(glm::vec3);
	glm::vec3 getPosition();
	void setX(GLfloat);
	GLfloat getX();
	void setY(GLfloat);
	GLfloat getY();
	void setZ(GLfloat);
	GLfloat getZ();

	void setAngle(glm::vec3);
	glm::vec3 getAngle();
	void setPitch(GLfloat);
	GLfloat getPitch();
	void setYaw(GLfloat);
	GLfloat getYaw();
	void setRoll(GLfloat);
	GLfloat getRoll();

	void setScale(glm::vec3);
	glm::vec3 getScale();

	void setFOV(GLfloat);
	GLfloat getFOV();

	void setScreenWidth(GLuint);
	GLuint getScreenWidth();
	void setScreenHeight(GLuint);
	GLuint getScreenHeight();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	glm::vec3 getFrontDirection();
	glm::vec3 getUpDirection();
	glm::vec3 getRightDirection();
};

