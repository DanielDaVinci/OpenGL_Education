#pragma once

#include <vector>
#include <string>
#include <assimp/material.h>

#include "../Engine/Runtime/Engine/StatichMesh/RStaticMesh.h"

struct aiMaterial;
struct aiMesh;
struct aiScene;
struct aiNode;
class FShader;
class RStaticMesh;

class RModel
{
public:

	std::vector<RStaticMesh> meshes;

    std::vector<Texture> textures_load;

	std::string directory;

public:
	RModel(std::string path);

	void Draw(FShader shader);

private:

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	RStaticMesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

};
