#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Room.h"
#include "Shader.h"


class Building
{
public:
	~Building();
	void addRoom(Room* room);
	void Draw(Shader* shader);

private:
	std::vector<Room*> rooms;
};

