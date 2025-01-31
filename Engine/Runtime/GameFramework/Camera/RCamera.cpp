#include "RCamera.h"

RCamera::RCamera(GLuint screenWidth, GLuint screenHeight, GLfloat FOV, glm::vec3 position, glm::vec3 angle)
{
	setScreenWidth(screenWidth);
	setScreenHeight(screenHeight);

	setFOV(FOV);

	setPosition(position);
	setAngle(angle);
	scale = { 1.0f, 1.0f, 1.0f};
}

void RCamera::setPosition(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 RCamera::getPosition()
{
	return position;
}

void RCamera::setX(GLfloat x)
{
	this->position.x = x;
}

GLfloat RCamera::getX()
{
	return this->position.x;
}

void RCamera::setY(GLfloat y)
{
	this->position.y = y;
}

GLfloat RCamera::getY()
{
	return this->position.y;
}

void RCamera::setZ(GLfloat z)
{
	this->position.z = z;
}

GLfloat RCamera::getZ()
{
	return this->position.z;
}

void RCamera::setAngle(glm::vec3 angle)
{
	this->angle = angle;
}

glm::vec3 RCamera::getAngle()
{
	return angle;
}

void RCamera::setPitch(GLfloat angle)
{
	this->angle.x = angle;
}

GLfloat RCamera::getPitch()
{
	return angle.x;
}

void RCamera::setYaw(GLfloat angle)
{
	this->angle.y = angle;
}

GLfloat RCamera::getYaw()
{
	return angle.y;
}

void RCamera::setRoll(GLfloat angle)
{
	this->angle.z = angle;
}

GLfloat RCamera::getRoll()
{
	return angle.z;
}

void RCamera::setScale(glm::vec3 scale)
{
	this->scale = scale;
}

glm::vec3 RCamera::getScale()
{
	return scale;
}

void RCamera::setFOV(GLfloat FOV)
{
	this->FOV = glm::max(glm::min(FOV, 179.99f), 0.001f);
}

GLfloat RCamera::getFOV()
{
	return FOV;
}

void RCamera::setScreenWidth(GLuint screenWidth)
{
	this->screenWidth = screenWidth;
}

GLuint RCamera::getScreenWidth()
{
	return screenWidth;
}

void RCamera::setScreenHeight(GLuint screenHeight)
{
	this->screenHeight = screenHeight;
}

GLuint RCamera::getScreenHeight()
{
	return screenHeight;
}

glm::mat4 RCamera::getViewMatrix()
{
	return glm::lookAt(getPosition(), getPosition() + getFrontDirection(), getUpDirection());
}

glm::mat4 RCamera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(FOV), (GLfloat)screenWidth/screenHeight, 0.01f, 100.0f);
}

glm::vec3 RCamera::getFrontDirection()
{
	glm::vec3 direction;

	direction.x = glm::cos(glm::radians(angle.x)) * glm::cos(glm::radians(angle.y));
	direction.y = glm::sin(glm::radians(angle.x));
	direction.z = glm::cos(glm::radians(angle.x)) * glm::sin(glm::radians(angle.y));

	return direction;
}

glm::vec3 RCamera::getUpDirection()
{
	return glm::cross(getRightDirection(), getFrontDirection());
}

glm::vec3 RCamera::getRightDirection()
{
	return glm::cross(getFrontDirection(), { 0.0f, 1.0f, 0.0f });
}
