#pragma once
#include "glm/glm.hpp"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec3 texCoords; // vec3 because I'm lazy. It is truncated to xy in shader
};