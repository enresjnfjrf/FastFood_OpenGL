#include "Light.h"

static const Light NoneLight = {"NONE", false, LightType::None, glm::vec3(0,0,0), glm::vec3(0,0,0), 0, glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0), 0, 0, 0};

Light::Light(std::string name, bool active)
{
	*this = NoneLight;
	this->name = name;
	this->active = active;
}

Light::Light(std::string name, bool active, LightType type, glm::vec3 position, glm::vec3 direction, float cutOff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
	:name(name), active(active), type(type), position(position), direction(direction), cutOff(cutOff), ambient(ambient), diffuse(diffuse), specular(specular), constant(constant), linear(linear), quadratic(quadratic)
{
}

void Light::initLikePointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
{
	type = LightType::Point;
	this->position = position;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

void Light::initLikeSpotLight(glm::vec3 position, glm::vec3 direction, float cutOff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
{
	type = LightType::Spot;
	this->position = position;
	this->direction = direction;
	this->cutOff = cutOff;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

void Light::initLikeDirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	type = LightType::Directional;
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

void Light::initLikeAmbientLight(glm::vec3 ambient)
{
	type = LightType::Ambient;
	this->ambient = ambient;
}

bool Light::isLightOn()
{
	return type > LightType::None && active;
}

void Light::turnOn()
{
	active = true;
}

void Light::turnOff()
{
	active = false;
}

int Light::putInshader(Shader* shader, int lightNumber)
{
	if(!isLightOn()) return 0;

	std::string num = std::to_string(lightNumber);

	switch (this->type)
	{	
	case LightType::Directional:
		shader->SetInt("light[" + num + "].type", int(type));
		shader->SetVec3("light[" + num + "].direction", direction);
		shader->SetVec3("light[" + num + "].ambient", ambient);
		shader->SetVec3("light[" + num + "].diffuse", diffuse);
		shader->SetVec3("light[" + num + "].specular", specular);
		break;
	case LightType::Point:
		shader->SetInt("light[" + num + "].type", int(type));
		shader->SetVec3("light[" + num + "].position", position);
		shader->SetVec3("light[" + num + "].ambient", ambient);
		shader->SetVec3("light[" + num + "].diffuse", diffuse);
		shader->SetVec3("light[" + num + "].specular", specular);
		shader->SetFloat("light[" + num + "].constant", constant);
		shader->SetFloat("light[" + num + "].linear", linear);
		shader->SetFloat("light[" + num + "].quadratic", quadratic);
		break;
	case LightType::Spot:
		shader->SetInt("light[" + num + "].type", int(type));
		shader->SetVec3("light[" + num + "].position", position);
		shader->SetVec3("light[" + num + "].direction", direction);
		shader->SetFloat("light[" + num + "].cutOff", cutOff);
		shader->SetVec3("light[" + num + "].ambient", ambient);
		shader->SetVec3("light[" + num + "].diffuse", diffuse);
		shader->SetVec3("light[" + num + "].specular", specular);
		shader->SetFloat("light[" + num + "].constant", constant);
		shader->SetFloat("light[" + num + "].linear", linear);
		shader->SetFloat("light[" + num + "].quadratic", quadratic);
		break;
	case LightType::Ambient:
		shader->SetInt("light[" + num + "].type", int(type));
		shader->SetVec3("light[" + num + "].ambient", ambient);
	}
	return 1;
}

glm::vec3 Light::getPosition()
{
	return position;
}

void Light::setPosition(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 Light::getDirection()
{
	return direction;
}

void Light::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}
