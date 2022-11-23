#pragma once

#include "GLincludes.h"
#include "Camera.h"
#include "Observer.h"

enum LightType
{
	POINT = 1,
	SPOT = 2,
	DIRECTIONAL = 3,
};
enum LightState
{
	OFF = 0,
	ON = 1,
};

class Light : public Observer, public Subject
{
private:

public:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 color{ 1.f };

	LightType type;
	LightState state = ON;
	bool isFlashlight = false;

	float ambientStrength = 0.1;
	float specularStrength = 0.5;

	float intensity = 1;
	float attenuation = 1;

	float cutOff = glm::cos(glm::radians(22.0));

	Light(LightType type, glm::vec3 position);
	Light(LightType type, glm::vec3 position, glm::vec3 direction);

	void onSubjectNotification(EventType eventType, void* object) override;
};
