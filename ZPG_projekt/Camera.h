#pragma once

#include "GLincludes.h"
#include "CallbackHandler.h"
#include "Window.h"

class Camera
{
private:
	static glm::mat4 perspective;
	static glm::vec3 eye;
	static glm::vec3 target;
	static glm::vec3 up;
	static float yaw;
	static float pitch;
	static int mouse_last_x;
	static int mouse_last_y;
	static float FOV;
public:
	Camera() {};
	static glm::mat4 getCamera();
	static glm::mat4 getPerspective();
	static glm::vec3 getPosition();
	static void setPerspective(float FOV, float width, float height);
	static void move();

	Camera(Camera const&) = delete;
	Camera& operator = (Camera const&) = delete;
};
