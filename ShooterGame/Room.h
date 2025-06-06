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
	float h = 2.5;

	void createFloor(float x, float z);
	void createWalls(float x, float z);

public:
	Room(float x, float z);
	~Room();
	void Draw();
};

