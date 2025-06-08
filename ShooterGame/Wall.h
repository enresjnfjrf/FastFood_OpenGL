#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Shader.h"

class Wall
{
public:
	Wall(const float* vertices, size_t vertexSize, const std::string& diffusePath, const std::string& normalPath, const std::string& roughnessPath);
	~Wall();

	void Draw(Shader* shader);

private:
	unsigned int vao, vbo;
	float vertexCount;
	unsigned int diffuseTex = 0;
	unsigned int normalTex	= 0;
	unsigned int roughnessTex = 0;

	unsigned int LoadTexture(const std::string& path);
};

