#include "Light.h"

Light::Light(LightType type, glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity, float ambientStrength, float specularStrength, float cutOff, float outerCutOff, bool isFlashlight, LightState state)
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
	this->isFlashlight = isFlashlight;
	this->state = state;
}

void Light::onSubjectNotification(EventType eventType, void* object)
{
	if (eventType == CameraMoved && this->isFlashlight)
	{
		Camera* camera = ((Camera*)object);
		this->direction = camera->getTarget();
		this->position = camera->getPosition();
	}
}
