#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>



class Camera
{
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;
	float speed;
	float sensitivity;
	float fov;
	float znear;
	float zfar;
	float aspectratio;

public:
	Camera(glm::vec3 position);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	void ProcessKeyboard(int key, float deltaTime);
	void ProcessMouse(float xoffset, float yoffset);
	glm::vec3 GetPosition();
	glm::vec3 GetUp();
	glm::vec3 GetFront();

};