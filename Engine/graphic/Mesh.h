#pragma once

#include <vector>
#include <string>

using namespace std;

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <ASSIMP/Importer.hpp>
#include <ASSIMP/scene.h>
#include <ASSIMP/postprocess.h>

#include "Shader.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;
	string type;
	aiString path;
};


class Mesh
{
private:

	unsigned int VAO, VBO, EBO;

public:

	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

public:

	Mesh(vector<Vertex> vertices = {}, vector<unsigned int> indices = {}, vector<Texture> textures = {});

	void Draw(Shader shader);

private:

	void setupMesh();

};

