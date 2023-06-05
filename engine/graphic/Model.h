#pragma once

#include <vector>
#include <string>

using namespace std;

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <SOIL/SOIL.h>

#include "Mesh.h"

class Model
{
public:

	vector<Mesh> meshes;

    vector<Texture> textures_load;

	string directory;

public:

	Model(string path);

	void Draw(Shader shader);

private:

	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, string typeName);
	unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);
};
