#pragma once

#include "GLincludes.h"
#include "CallbackHandler.h"
#include "Window.h"
#include "Observer.h"

class Camera : public Subject, public Observer
{
private:
	Camera();

	float FOV = 90;
	float radius = 10;
	float speed = 0.03;
	float mouseSensitivity = 0.1;

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

	glm::mat4 getCamera() const;
	glm::mat4 getPerspective() const;
	glm::vec3 getPosition() const;
	glm::vec3 getTarget() const;
	int getFOV() const;

	void setPerspective(float FOV, float width, float height);
	void move();

	void onSubjectNotification(EventType eventType, void* object) override;

	Camera(Camera const&) = delete;
	void operator=(Camera const&) = delete;
};
