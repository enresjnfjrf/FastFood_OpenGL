#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Wall.h"
#include "Shader.h"

class Room
{
public:
	Room(float x, float y, float z, float width, float height, float length, float thickness);
	~Room();
	void Draw(Shader* shader);
	void createWall(float x, float y, float z, float width, float height, float length, const std::string& diffuse, const std::string& normal, const std::string& roughness, float u, float v);

	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }
	float getWidth() const { return width; }
	float getHeight() const { return height; }
	float getLength() const { return length; }
	float getThickness() const { return thickness; }

private:
	Wall* floor;
	std::vector<Wall*> walls;
	float x, y, z;
	float height;
	float width;
	float length;
	float thickness;

};

