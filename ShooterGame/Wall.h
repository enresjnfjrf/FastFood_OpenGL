#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class Wall
{
public:
	Wall(const float* vertices, size_t vertexSize,
		const std::string& diffusePath,
		const std::string& normalPath,
		const std::string& roughnessPath);
	~Wall();

	void Draw(unsigned int shaderProgram);

private:
	unsigned int vao, vbo;
	size_t vertexCount;
	unsigned int diffuseTex = 0;
	unsigned int normalTex	= 0;
	unsigned int roughnessTex = 0;

	unsigned int LoadTexture(const std::string& path);
};

