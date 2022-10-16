#pragma once

#include "GLincludes.h"

class Camera
{
private:
	glm::mat4 camera{ 0.f };
public:
	Camera() {};
	glm::mat4 getCamera();
};
