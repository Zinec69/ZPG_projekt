#include "Light.h"

Light::Light(LightType type, glm::vec3 position)
{
	this->type = type;
	this->position = position;
}

Light::Light(LightType type, glm::vec3 position, glm::vec3 direction)
{
	this->type = type;
	this->position = position;
	this->direction = direction;
}

void Light::onSubjectNotification(EventType eventType, void* object)
{
	if (eventType == CameraMoved && this->isFlashlight)
	{
		this->direction = Camera::getInstance().getTarget();
		this->position = Camera::getInstance().getPosition();
	}
}
