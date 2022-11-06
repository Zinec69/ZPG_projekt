#include "Light.h"

Light::Light(LightType type, glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity, float ambientStrength, float specularStrength, float cutOff, float outerCutOff, LightState state)
{
	this->type = type;
	this->position = position;
	this->direction = direction;
	this->color = color;
	this->intensity = intensity;
	this->ambientStrength = ambientStrength;
	this->specularStrength = specularStrength;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
	this->state = state;
}
