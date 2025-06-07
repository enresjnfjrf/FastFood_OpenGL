#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Room.h"


class Building
{
public:
	~Building();
	void addRoom(float x, float y, float z, float width, float height, float lenght, float thickness);
	void Draw();

private:
	std::vector<Room*> rooms;
};

