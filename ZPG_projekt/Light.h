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
	glm::vec3 color;

	LightType type;
	bool isFlashlight;
	LightState state;

	float ambientStrength;
	float specularStrength;

	float intensity;

	float cutOff;
	float outerCutOff;

	Light(LightType type, glm::vec3 position, glm::vec3 direction = glm::vec3(0.0), glm::vec3 color = glm::vec3(1.0), float intensity = 1.0, 
		float ambientStrength = 0.1, float specularStrength = 0.5, float cutOff = glm::cos(glm::radians(13.0)), float outerCutOff = glm::cos(glm::radians(22.0)), 
		bool isFlashlight = false, LightState state = ON);

	void onSubjectNotification(EventType eventType, void* object) override;
};
