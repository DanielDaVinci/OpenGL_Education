#include "Camera.h"

Camera::Camera(GLuint screenWidth, GLuint screenHeight, GLfloat FOV, glm::vec3 position, glm::vec3 angle)
{
	setScreenWidth(screenWidth);
	setScreenHeight(screenHeight);

	setFOV(FOV);

	setPosition(position);
	setAngle(angle);
	scale = { 1.0f, 1.0f, 1.0f};
}

void Camera::setPosition(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 Camera::getPosition()
{
	return position;
}

void Camera::setX(GLfloat x)
{
	this->position.x = x;
}

GLfloat Camera::getX()
{
	return this->position.x;
}

void Camera::setY(GLfloat y)
{
	this->position.y = y;
}

GLfloat Camera::getY()
{
	return this->position.y;
}

void Camera::setZ(GLfloat z)
{
	this->position.z = z;
}

GLfloat Camera::getZ()
{
	return this->position.z;
}

void Camera::setAngle(glm::vec3 angle)
{
	this->angle = angle;
}

glm::vec3 Camera::getAngle()
{
	return angle;
}

void Camera::setPitch(GLfloat angle)
{
	this->angle.x = angle;
}

GLfloat Camera::getPitch()
{
	return angle.x;
}

void Camera::setYaw(GLfloat angle)
{
	this->angle.y = angle;
}

GLfloat Camera::getYaw()
{
	return angle.y;
}

void Camera::setRoll(GLfloat angle)
{
	this->angle.z = angle;
}

GLfloat Camera::getRoll()
{
	return angle.z;
}

void Camera::setScale(glm::vec3 scale)
{
	this->scale = scale;
}

glm::vec3 Camera::getScale()
{
	return scale;
}

void Camera::setFOV(GLfloat FOV)
{
	this->FOV = glm::max(glm::min(FOV, 179.99f), 0.001f);
}

GLfloat Camera::getFOV()
{
	return FOV;
}

void Camera::setScreenWidth(GLuint screenWidth)
{
	this->screenWidth = screenWidth;
}

GLuint Camera::getScreenWidth()
{
	return screenWidth;
}

void Camera::setScreenHeight(GLuint screenHeight)
{
	this->screenHeight = screenHeight;
}

GLuint Camera::getScreenHeight()
{
	return screenHeight;
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(getPosition(), getPosition() + getFrontDirection(), getUpDirection());
}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(FOV), (GLfloat)screenWidth/screenHeight, 0.01f, 100.0f);
}

glm::vec3 Camera::getFrontDirection()
{
	glm::vec3 direction;

	direction.x = glm::cos(glm::radians(angle.x)) * glm::cos(glm::radians(angle.y));
	direction.y = glm::sin(glm::radians(angle.x));
	direction.z = glm::cos(glm::radians(angle.x)) * glm::sin(glm::radians(angle.y));

	return direction;
}

glm::vec3 Camera::getUpDirection()
{
	return glm::cross(getRightDirection(), getFrontDirection());
}

glm::vec3 Camera::getRightDirection()
{
	return glm::cross(getFrontDirection(), { 0.0f, 1.0f, 0.0f });
}
