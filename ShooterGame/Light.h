#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "Shader.h"

enum class LightType { None = 0, Directional = 1, Point = 2, Spot = 3, Ambient = 4};

class Light
{
private:
	std::string name;
	bool active;
	LightType type;
	glm::vec3 position;
	glm::vec3 direction;
	float cutOff;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float constant;
	float linear;
	float quadratic;

public:
	Light(std::string name = "None", bool active = false);
	Light(std::string name, bool active, LightType type, glm::vec3 position, glm::vec3 direction, float cutOff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
	
	void initLikePointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
	void initLikeSpotLight(glm::vec3 position, glm::vec3 direction, float cutOff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
	void initLikeDirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	void initLikeAmbientLight(glm::vec3 ambient);

	bool isLightOn();
	void turnOn();
	void turnOff();

	int putInshader(Shader* shader, int lightNumber);

	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	glm::vec3 getDirection();
	void setDirection(glm::vec3 directional);
};

extern const Light NoneLight;