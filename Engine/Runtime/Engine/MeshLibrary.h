#pragma once

#include <string>
#include <assimp/types.h>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    unsigned int id;
    std::string type;
    aiString path;
};