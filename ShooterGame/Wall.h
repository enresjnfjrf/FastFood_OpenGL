#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class Wall
{
private:
	unsigned int vao, vbo;
	int vertexCount;

public:
	Wall(const float* vertices, size_t vertexSize);
	~Wall();

	void Draw();


};

