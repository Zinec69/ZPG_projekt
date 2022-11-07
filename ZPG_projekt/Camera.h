#pragma once

#include "GLincludes.h"
#include "CallbackHandler.h"
#include "Window.h"
#include "Observer.h"

class Camera : public Subject
{
private:
	Camera() {};

	float FOV = 90;
	glm::vec3 eye{ 0.f, 0.f, 5.f };
	glm::vec3 target{ 0.f, 0.f, -1.f };
	glm::vec3 up{ 0.f, 1.f, 0.f };
	glm::mat4 perspective = glm::perspective(glm::radians(FOV), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	glm::mat4 lookAt = glm::lookAt(eye, target + eye, up);
	float yaw = -90;
	float pitch = 1;
	int mouse_last_x = WINDOW_WIDTH / 2;
	int mouse_last_y = WINDOW_HEIGHT / 2;
public:
	static Camera& getInstance()
	{
		static Camera instance;
		return instance;
	}

	glm::mat4 getCamera();
	glm::mat4 getPerspective();
	glm::vec3 getPosition();
	glm::vec3 getTarget();
	void setPerspective(float FOV, float width, float height);
	void move();

	Camera(Camera const&) = delete;
	void operator=(Camera const&) = delete;
};
