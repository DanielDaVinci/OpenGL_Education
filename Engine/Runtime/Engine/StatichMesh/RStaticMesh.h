#pragma once

#include <vector>
#include "../MeshLibrary.h"

class FShader;

class RStaticMesh
{
private:

	unsigned int VAO, VBO, EBO;

public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

public:

	RStaticMesh(std::vector<Vertex> vertices = {}, std::vector<unsigned int> indices = {}, std::vector<Texture> textures = {});

	void Draw(FShader shader);

private:

	void setupMesh();

};

