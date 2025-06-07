#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Wall.h"

class Room
{
private:
	Wall* floor;
	std::vector<Wall*> walls;
	float x, y, z;
	float height;
	float width;
	float lenght;
	float thickness;

	void createWall(float x, float y, float z, float width, float height, float lenght);

public:
	Room(float x, float y, float z, float width, float height, float lenght, float thickness);
	~Room();
	void Draw();
};

