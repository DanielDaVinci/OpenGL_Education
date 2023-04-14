#include "Texture.h"

Texture::Texture(GLenum type, const GLchar* path, ColorFormat format)
{
	this->type = type;
	glGenTextures(1, &texture);

	Bind();

	setImage(path, format);
}

GLuint Texture::getTexture() const
{
	return texture;
}

GLenum Texture::getType() const
{
	return type;
}

string Texture::getPath() const
{
	return path;
}

int Texture::getWidth() const
{
	return width;
}

int Texture::getHeight() const
{
	return height;
}

void Texture::setImage(const GLchar* path, ColorFormat format)
{
	this->path = ((path == nullptr) ? "" : path);

	cout << this->path << endl;

	int soilFormat;
	GLint glFormat;

	switch (format)
	{
		case AUTO:
			soilFormat = SOIL_LOAD_AUTO;
			glFormat = GL_RGBA;
			break;
		case LUMIN:
			soilFormat = SOIL_LOAD_L;
			glFormat = GL_LUMINANCE;
			break;
		case LUMIN_ALPHA:
			soilFormat = SOIL_LOAD_LA;
			glFormat = GL_LUMINANCE_ALPHA;
			break;
		case RGB:
			soilFormat = SOIL_LOAD_RGB;
			glFormat = GL_RGB;
			break;
		case RGBA:
			soilFormat = SOIL_LOAD_RGBA;
			glFormat = GL_RGBA;
			break;
		default:
			soilFormat = SOIL_LOAD_AUTO;
			glFormat = GL_RGBA;
			break;
	}

	unsigned char* image = SOIL_load_image(this->path.c_str(), &width, &height, 0, soilFormat);
	glTexImage2D(type, 0, glFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(type);

	SOIL_free_image_data(image);
	UnBind();
}

void Texture::setParameter(GLenum name, GLint value)
{
	glTexParameteri(type, name, value);
}

void Texture::setParameter(GLenum name, const GLfloat* value)
{
	glTexParameterfv(type, name, value);
}

void Texture::Bind()
{
	glBindTexture(type, texture);
}

void Texture::UnBind()
{
	glBindTexture(type, 0);
}
