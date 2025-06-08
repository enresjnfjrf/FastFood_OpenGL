#pragma once
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>


class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void Use();
	unsigned int ID();
	void SetMatrix4F(const std::string& name, glm::mat4& m);
	void SetVec2(const std::string& name, glm::vec2 vec);
	void SetVec3(const std::string& name, glm::vec3 vec);
	void SetVec4(const std::string& name, glm::vec4 vec);
	void SetFloat(const std::string& name, float f);
	void SetInt(const std::string& name, int value);

private:
	unsigned int programID;

};

